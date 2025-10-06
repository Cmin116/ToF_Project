/*
 * oled_ssd1306.h
 *
 *  Created on: Sep 13, 2025
 *      Author: SCSM11
 */

#ifndef APPLICATION_USER_OLED_SSD1306_H_
#define APPLICATION_USER_OLED_SSD1306_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration so we don't depend on i2c.h */
typedef struct __I2C_HandleTypeDef I2C_HandleTypeDef;

typedef struct {
  I2C_HandleTypeDef *hi2c;  /* e.g., &hi2c1 from BSP */
  uint8_t addr;             /* 8-bit HAL address: (0x3C<<1) or (0x3D<<1) */
  uint8_t x_offset;         /* 0 for SSD1306; 2 for many SH1106 boards */
} OLED_t;

/* Public API */
void OLED_Init(OLED_t *d);
void OLED_Clear(OLED_t *d);
void OLED_SetWindow(OLED_t *d, uint8_t x0, uint8_t x1, uint8_t page0, uint8_t page1);
void OLED_DrawString(OLED_t *d, uint8_t x, uint8_t page, const char *s);
void OLED_DrawCentered(OLED_t *d, uint8_t page, const char *s);

/* Handy splash for your POST */
void OLED_Splash(OLED_t *d);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_USER_OLED_SSD1306_H_ */
