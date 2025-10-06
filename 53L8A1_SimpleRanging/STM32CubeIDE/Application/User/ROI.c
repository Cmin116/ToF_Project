/*
 * ROI.c
 *
 * Implements sliding 2x2 ROI selection:
 * - Slide a 2x2 window across 8x8 zones
 * - All 4 zones must be valid and close to frame minimum
 * - Pick window with lowest mean + spread penalty
 * - Return average distance for LED/OLED/buzzer
 */

#include "ROI.h"
#include <limits.h>
#include <stdio.h>

/* ---- Tunables ----------------------------------------------------------- */
/* Accept zones only if status is "good".*/
#define ROI_STATUS_GOOD(s)   ((s) == 0)   /* most frames print :0 -> good */

/* Relaxed gating */
#define ROI_DELTA_MM         180          /* window cells must be within global_min + Δ */
#define ROI_SPREAD_MAX_MM    120          /* additionally require (max-min) <= 120 mm */
#define ROI_MIN_GOOD_CELLS   3            /* 3 of 4 cells passing the Δ gate is enough */

#define ROI_LAMBDA           0.5f         /* tie-break score: mean + λ·spread */

/* ---- Bottom-row surface guard (affects ONLY how we pick global_min) ----- */
#define BR_MIN_GOOD_CELLS    6            /* row7 must have at least this many good cells */
#define BR_SPREAD_MAX_MM     100          /* row7 must be very uniform to be treated as surface */
#define BR_NEARER_GAP_MM     180          /* row7 mean must be this much nearer than row6 mean */

/* ------------------------------------------------------------------------ */

void ROI_Init(void)
{
    // nothing yet; placeholder if you want state
}

ROI_Result_t ROI_Compute(const RANGING_SENSOR_Result_t *res)
{
    ROI_Result_t out = (ROI_Result_t){ .valid = 0, .row = 0, .col = 0, .avg_distance = -1 };
    if (!res) return out;

    const uint8_t rows = 8, cols = 8;

    /* --- Analyze bottom row (row 7) and row 6 to decide if row 7 is a flat surface --- */
    int br_good = 0, r6_good = 0;
    int32_t br_min = INT_MAX, br_max = INT_MIN, br_sum = 0;
    int32_t r6_min = INT_MAX, r6_max = INT_MIN, r6_sum = 0;

    /* row 7 indices: 56..63; row 6 indices: 48..55 */
    for (uint8_t z = 56; z <= 63; z++) {
        if (res->ZoneResult[z].NumberOfTargets > 0 && ROI_STATUS_GOOD(res->ZoneResult[z].Status[0])) {
            int32_t d = (int32_t)res->ZoneResult[z].Distance[0];
            if (d < br_min) br_min = d;
            if (d > br_max) br_max = d;
            br_sum += d;
            br_good++;
        }
    }
    for (uint8_t z = 48; z <= 55; z++) {
        if (res->ZoneResult[z].NumberOfTargets > 0 && ROI_STATUS_GOOD(res->ZoneResult[z].Status[0])) {
            int32_t d = (int32_t)res->ZoneResult[z].Distance[0];
            if (d < r6_min) r6_min = d;
            if (d > r6_max) r6_max = d;
            r6_sum += d;
            r6_good++;
        }
    }

    int skip_bottom_in_min = 0;
    if (br_good >= BR_MIN_GOOD_CELLS) {
        int32_t br_spread = (br_max > br_min) ? (br_max - br_min) : 0;
        int32_t br_mean   = (br_good > 0) ? (br_sum / br_good) : INT_MAX;
        int32_t r6_mean   = (r6_good > 0) ? (r6_sum / r6_good) : INT_MAX;

        /* Treat row7 as a flat surface only if:
           - many good cells,
           - very uniform,
           - clearly nearer than the next row (edge strip effect). */
        if (br_spread <= BR_SPREAD_MAX_MM &&
            r6_mean != INT_MAX &&
            (r6_mean - br_mean) >= BR_NEARER_GAP_MM) {
            skip_bottom_in_min = 1;
        }
    }

    /* --- Find global minimum among "good" cells only (optionally skipping flat bottom row) --- */
    int32_t global_min = INT_MAX;
    uint8_t start_z = 0;
    uint8_t end_z   = rows*cols - 1;

    for (uint8_t z = start_z; z <= end_z; z++) {
        /* If we flagged a flat bottom surface, exclude row7 (z 56..63) from *min* calculation only */
        if (skip_bottom_in_min && z >= 56 && z <= 63) continue;

        if (res->ZoneResult[z].NumberOfTargets > 0) {
            int32_t st = (int32_t)res->ZoneResult[z].Status[0];
            if (ROI_STATUS_GOOD(st)) {
                int32_t d = (int32_t)res->ZoneResult[z].Distance[0];
                if (d < global_min) global_min = d;
            }
        }
    }
    if (global_min == INT_MAX) return out; /* no good cells at all */

    float bestJ = 1e9f;

    /* --- Slide 2x2 window across 8x8 --- */
    for (uint8_t r = 0; r < rows - 1; r++) {
        for (uint8_t c = 0; c < cols - 1; c++) {

            uint8_t idxs[4] = {
                (uint8_t)(r*cols + c),
                (uint8_t)(r*cols + (c+1)),
                (uint8_t)((r+1)*cols + c),
                (uint8_t)((r+1)*cols + (c+1))
            };

            /* Collect only the cells that are "good" AND within Δ of global min */
            int32_t gd[4];
            int good_count = 0;

            for (int k = 0; k < 4; k++) {
                const uint32_t z = idxs[k];
                if (res->ZoneResult[z].NumberOfTargets == 0) continue;

                int32_t st = (int32_t)res->ZoneResult[z].Status[0];
                if (!ROI_STATUS_GOOD(st)) continue;

                int32_t d = (int32_t)res->ZoneResult[z].Distance[0];
                if (d <= global_min + ROI_DELTA_MM) {
                    gd[good_count++] = d;
                }
            }

            /* Relaxed rule: require at least 3 cells passing; enforce spread cap */
            if (good_count < ROI_MIN_GOOD_CELLS) continue;

            /* Compute mean & spread on the accepted cells */
            int32_t minv = gd[0], maxv = gd[0], sum = gd[0];
            for (int i = 1; i < good_count; i++) {
                if (gd[i] < minv) minv = gd[i];
                if (gd[i] > maxv) maxv = gd[i];
                sum += gd[i];
            }
            int32_t spread = maxv - minv;
            if (spread > ROI_SPREAD_MAX_MM) continue;

            float mean = (float)sum / (float)good_count;
            float J = mean + ROI_LAMBDA * (float)spread;

            if (J < bestJ) {
                bestJ = J;
                out.valid = 1;
                out.row = r;
                out.col = c;
                out.avg_distance = sum / good_count;  /* average of the good cells */
            }
        }
    }

    return out;
}
