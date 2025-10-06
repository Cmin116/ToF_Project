#!/usr/bin/env python3
"""
Async, event-driven live heatmap for VL53L8CX (distance:status pairs).
MCU prints one row per line, e.g.:
  "193:0  298:0  296:0 ..."  (8 pairs per row)

We parse only the left value (distance) from each "dist:status" pair.
Requires: pyserial, pyserial-asyncio, numpy, matplotlib
"""

import argparse
import asyncio
import numpy as np
import matplotlib.pyplot as plt
import serial_asyncio


def parse_row(line: str, expected_cols: int):
    """Parse a single line 'd:s d:s ...' -> list[float] of distances."""
    line = line.strip()
    if ":" not in line:
        return None
    vals = []
    # tolerate multiple spaces, pipes, tabs
    for cell in line.replace("|", " ").split():
        if ":" in cell:
            left = cell.split(":", 1)[0]
            try:
                vals.append(float(left))
            except ValueError:
                pass
    return vals if len(vals) == expected_cols else None


class ToFLineClient(asyncio.Protocol):
    """Reads newline-delimited rows, assembles frames, pushes to callback."""
    def __init__(self, rows, cols, on_frame):
        self.rows = rows
        self.cols = cols
        self.on_frame = on_frame
        self._buf = bytearray()
        self._block = []  # accumulating list of row lists

    def connection_made(self, transport):
        self.transport = transport

    def data_received(self, data: bytes):
        self._buf.extend(data)

        while True:
            # Look for double newline as frame delimiter
            sep = self._buf.find(b"\n\n")
            if sep < 0:
                break

            block = self._buf[:sep].decode("utf-8", errors="ignore")
            del self._buf[:sep+2]  # remove block + delimiter

            rows = []
            for line in block.strip().splitlines():
                row = parse_row(line, self.cols)
                if row:
                    rows.append(row)

        # Only push frame if we got exactly self.rows rows
            # if len(rows) == self.rows:
            frame = np.array(rows, dtype=np.float32)
            self.on_frame(frame)


    def connection_lost(self, exc):
        # No special handling; main loop will exit if needed
        pass


async def run(port, baud, rows, cols, vmin, vmax):
    latest_frame = {"data": None}

    # Matplotlib interactive figure
    plt.ion()
    fig, ax = plt.subplots()
    im = ax.imshow(np.zeros((rows, cols), dtype=np.float32),
                   origin="upper",
                   interpolation="nearest",
                   vmin=vmin, vmax=vmax)
    fig.colorbar(im, ax=ax, label="Distance (mm)")
    ax.set_title("Live ToF Heatmap (async)")

    def on_frame(frame: np.ndarray):
        # store latest frame; UI loop will render it
        latest_frame["data"] = frame

    loop = asyncio.get_running_loop()
    transport, protocol = await serial_asyncio.create_serial_connection(
        loop, lambda: ToFLineClient(rows, cols, on_frame), port, baud
    )

    try:
        # UI refresh loop (driven by event loop, no sleeps needed)
        while plt.fignum_exists(fig.number):
            frame = latest_frame["data"]
            if frame is not None:
                im.set_data(frame)
                fig.canvas.draw_idle()
                fig.canvas.flush_events()
                latest_frame["data"] = None
            # Yield control so serial callbacks can run
            await asyncio.sleep(0.01)
    finally:
        transport.close()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", required=True)
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--rows", type=int, default=8)
    ap.add_argument("--cols", type=int, default=8)
    ap.add_argument("--vmin", type=float, default=50)
    ap.add_argument("--vmax", type=float, default=2000)
    args = ap.parse_args()

    try:
        asyncio.run(run(args.port, args.baud, args.rows, args.cols, args.vmin, args.vmax))
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
