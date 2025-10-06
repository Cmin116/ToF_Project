/*
 * oled_ssd1306.c
 *
 *  Created on: Sep 13, 2025
 *      Author: SCSM11
 */
#include "oled_ssd1306.h"
#include "oled_font5x8.h"

#include "main.h"                    /* for HAL headers */
#include "string.h"

/* ---- Low-level helpers -------------------------------------------------- */
static void wr_cmd (OLED_t *d, uint8_t c)
{
  uint8_t buf[2] = {0x00, c};        /* 0x00 = control byte for command */
  HAL_I2C_Master_Transmit(d->hi2c, d->addr, buf, 2, HAL_MAX_DELAY);
}

static void wr_cmd2(OLED_t *d, uint8_t a, uint8_t b)
{
  uint8_t buf[3] = {0x00, a, b};
  HAL_I2C_Master_Transmit(d->hi2c, d->addr, buf, 3, HAL_MAX_DELAY);
}

static void wr_data(OLED_t *d, const uint8_t *data, uint16_t len)
{
  while (len) {
    uint16_t chunk = (len > 16) ? 16 : len;     // small, safe stack buffer
    uint8_t  buf[1 + 16];
    buf[0] = 0x40;                              // data control byte
    for (uint16_t i = 0; i < chunk; ++i) buf[1 + i] = data[i];
    HAL_I2C_Master_Transmit(d->hi2c, d->addr, buf, 1 + chunk, HAL_MAX_DELAY);
    data += chunk;
    len  -= chunk;
  }
}

/* ---- Public API --------------------------------------------------------- */
void OLED_Init(OLED_t *d)
{
  HAL_Delay(10);
  wr_cmd (d, 0xAE);                /* display off */
  wr_cmd2(d, 0xD5, 0x80);          /* clock */
  wr_cmd2(d, 0xA8, 0x3F);          /* multiplex (64) */
  wr_cmd2(d, 0xD3, 0x00);          /* offset */
  wr_cmd (d, 0x40);                /* start line = 0 */
  wr_cmd2(d, 0x8D, 0x14);          /* charge pump on */
  wr_cmd2(d, 0x20, 0x00);          /* horizontal addressing */
  wr_cmd (d, 0xA1);                /* seg remap */
  wr_cmd (d, 0xC8);                /* com scan dec */
  wr_cmd2(d, 0xDA, 0x12);          /* com pins */
  wr_cmd2(d, 0x81, 0x7F);          /* contrast */
  wr_cmd2(d, 0xD9, 0xF1);          /* precharge */
  wr_cmd2(d, 0xDB, 0x40);          /* VCOMH */
  wr_cmd (d, 0xA4);                /* resume RAM */
  wr_cmd (d, 0xA6);                /* normal display */
  wr_cmd (d, 0x2E);                /* stop scroll */
  wr_cmd (d, 0xAF);                /* display on */
}

void OLED_SetWindow(OLED_t *d, uint8_t x0, uint8_t x1, uint8_t page0, uint8_t page1)
{
  x0 += d->x_offset; x1 += d->x_offset;
  wr_cmd (d, 0x21); wr_cmd(d, x0); wr_cmd(d, x1);         /* columns */
  wr_cmd (d, 0x22); wr_cmd(d, page0); wr_cmd(d, page1);   /* pages   */
}

void OLED_Clear(OLED_t *d)
{
  OLED_SetWindow(d, 0, 127, 0, 7);
  uint8_t zeros[128] = {0};
  for (int p = 0; p < 8; ++p) wr_data(d, zeros, sizeof(zeros));
}

void OLED_DrawString(OLED_t *d, uint8_t x, uint8_t page, const char *s)
{
  uint8_t line[128] = {0};                       /* up to 21 chars (21*6=126) */
  size_t n = strlen(s);
  if (n > 21) n = 21;

  for (size_t i = 0; i < n; ++i) {
    uint8_t c = (uint8_t)s[i];
    if (c < 32 || c > 127) c = 32;               /* replace with space */
    const uint8_t *g = Font5x8[c - 32];
    size_t off = i * 6;
    line[off + 0] = g[0];
    line[off + 1] = g[1];
    line[off + 2] = g[2];
    line[off + 3] = g[3];
    line[off + 4] = g[4];
    line[off + 5] = 0x00;                         /* spacing column */
  }

  uint8_t width = (uint8_t)(n * 6);
  if (width == 0) return;

  OLED_SetWindow(d, x, (uint8_t)(x + width - 1), page, page);
  wr_data(d, line, width);
}

void OLED_DrawCentered(OLED_t *d, uint8_t page, const char *s)
{
  size_t n = strlen(s); if (n > 21) n = 21;
  uint8_t width = (uint8_t)(n * 6);
  uint8_t x = (uint8_t)((128 - width) / 2);
  OLED_DrawString(d, x, page, s);
}

void OLED_Splash(OLED_t *d)
{
  OLED_Clear(d);
  OLED_DrawCentered(d, 2, "real-time");
  OLED_DrawCentered(d, 3, "monitoring");
  OLED_DrawCentered(d, 4, "start");
}


