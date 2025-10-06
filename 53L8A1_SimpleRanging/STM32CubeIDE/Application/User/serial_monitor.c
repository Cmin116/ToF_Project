/*
 * serial_monitor.c
 *
 *  Created on: Sep 13, 2025
 *      Author: SCSM11
 */

/**
  ******************************************************************************
  * @file          : serial_monitor.c
  * @brief         : Minimal 8x8 continuous ranging -> compact UART print
  *                  Format: 8 lines per frame, each line has 8 "distance:status"
  *                  pairs separated by a single space. Press 'c' to clear screen.
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "serial_monitor.h"
#include "main.h"

#include <stdio.h>
#include <stdint.h>

#include "53l8a1_ranging_sensor.h"
#include "app_tof_pin_conf.h"
#include "stm32l4xx_nucleo.h"
#include "ROI.h"
__weak void ROI_OnUpdate(const ROI_Result_t *roi) { (void)roi; }

/* Private defines -----------------------------------------------------------*/
/* Kept distinct from app_tof.* to avoid collisions */
#define SM_TIMING_BUDGET_MS     (30U)   /* Valid range: ~5..100 ms */
#define SM_RANGING_FREQ_HZ      (10U)   /* Must be consistent with budget */
#define SM_POLLING_DELAY_MS     (1U)

#define SM_ESC_CLEAR            "\033[2J\033[H"

/* Private variables ---------------------------------------------------------*/
static RANGING_SENSOR_ProfileConfig_t smProfile;
static RANGING_SENSOR_Result_t        smResult;
static int32_t                        smStatus = 0;

/* Private function prototypes -----------------------------------------------*/
static void SM_SensorResetSequence(void);
static void SM_ConfigAndStart(void);
static void SM_PrintFrame(const RANGING_SENSOR_Result_t *res);
static uint8_t SM_GetKeyNonBlocking(uint8_t *out);
static void SM_ClearScreen(void);

/* Public functions -----------------------------------------------------------*/
void MX_SERIALMON_Init(void)
{
  /* Init VCOM (UART over STLink) */
  BSP_COM_Init(COM1);

  /* Optional: clear screen once at startup */
  printf(SM_ESC_CLEAR);

  /* Power-cycle / bring up the sensor as in the reference example */
  SM_SensorResetSequence();

  /* Init driver */
  smStatus = VL53L8A1_RANGING_SENSOR_Init(VL53L8A1_DEV_CENTER);
  if (smStatus != BSP_ERROR_NONE)
  {
    printf("ERR:init\n");
    while (1) { /* Trap */ }
  }

  /* Configure 8x8 continuous profile and start */
  SM_ConfigAndStart();

  ROI_Init();
}

void MX_SERIALMON_Process(void)
{
  /* Blocking continuous read (polling) + optional key handler */
  while (1)
  {
    /* Handle single-key command (non-blocking) */
    uint8_t key;
    if (SM_GetKeyNonBlocking(&key))
    {
      if (key == 'c' || key == 'C')
      {
        SM_ClearScreen();
      }
    }

    /* Fetch distances (blocking call in continuous mode) */
    smStatus = VL53L8A1_RANGING_SENSOR_GetDistance(VL53L8A1_DEV_CENTER, &smResult);
    if (smStatus == BSP_ERROR_NONE)
    {
      SM_PrintFrame(&smResult);
      ROI_Result_t roi = ROI_Compute(&smResult);
      ROI_OnUpdate(&roi); // delegates to main.c
    }

    HAL_Delay(SM_POLLING_DELAY_MS);
  }
}

/* Private helpers ------------------------------------------------------------*/
static void SM_SensorResetSequence(void)
{
  /* Match pin names from app_tof_pin_conf.h */
  HAL_GPIO_WritePin(VL53L8A1_PWR_EN_C_PORT, VL53L8A1_PWR_EN_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L8A1_PWR_EN_C_PORT, VL53L8A1_PWR_EN_C_PIN, GPIO_PIN_SET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L8A1_LPn_C_PORT, VL53L8A1_LPn_C_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(VL53L8A1_LPn_C_PORT, VL53L8A1_LPn_C_PIN, GPIO_PIN_SET);
  HAL_Delay(2);
}

static void SM_ConfigAndStart(void)
{
  /* 8x8 CONTINUOUS only; no signal/ambient to keep output compact */
  smProfile.RangingProfile = RS_PROFILE_8x8_CONTINUOUS;
  smProfile.TimingBudget   = SM_TIMING_BUDGET_MS;
  smProfile.Frequency      = SM_RANGING_FREQ_HZ;
  smProfile.EnableAmbient  = 0U;
  smProfile.EnableSignal   = 0U;

  smStatus = VL53L8A1_RANGING_SENSOR_ConfigProfile(VL53L8A1_DEV_CENTER, &smProfile);
  if (smStatus != BSP_ERROR_NONE)
  {
    printf("ERR:cfg\n");
    while (1) { /* Trap */ }
  }

  smStatus = VL53L8A1_RANGING_SENSOR_Start(VL53L8A1_DEV_CENTER, RS_MODE_BLOCKING_CONTINUOUS);
  if (smStatus != BSP_ERROR_NONE)
  {
    printf("ERR:start\n");
    while (1) { /* Trap */ }
  }
}

static void SM_PrintFrame(const RANGING_SENSOR_Result_t *res)
{
  /* Expect 64 zones in 8x8 mode. We print 8 lines; each has 8 "distance:status" pairs.
     Order matches ST demo's left/right orientation (k from 7 -> 0). */
  const uint8_t zones_per_line = 8;
  const uint8_t targets_per_zone = RANGING_SENSOR_NB_TARGET_PER_ZONE; /* usually 1 */

  uint32_t zone_index = 0;

  for (uint8_t row = 0; row < 8; row++)
  {
    /* Build one row */
    for (int8_t k = zones_per_line - 1; k >= 0; k--)
    {
      uint32_t z = zone_index + (uint32_t)k;

      if (res->ZoneResult[z].NumberOfTargets > 0)
      {
        /* Use first target (l = 0) */
        long dist   = (long)res->ZoneResult[z].Distance[0];
        long status = (long)res->ZoneResult[z].Status[0];
        /* Space-separated, compact, machine-friendly */
        /* Width on distance helps visual alignment, still easy to parse */
        printf("%5ld:%ld", dist, status);
      }
      else
      {
        /* If no target, print X:X (parser can skip non-numeric if desired) */
        printf("    X:X");
      }

      if (k > 0) putchar(' ');
    }

    putchar('\n');
    zone_index += zones_per_line;
  }

  /* Blank line separates frames (easy to detect frame boundaries) */
  putchar('\n');
}

static uint8_t SM_GetKeyNonBlocking(uint8_t *out)
{
  /* Non-blocking check for a single byte on COM1 */
  if (__HAL_UART_GET_FLAG(&hcom_uart[COM1], UART_FLAG_RXNE))
  {
    HAL_UART_Receive(&hcom_uart[COM1], out, 1, 0);
    return 1U;
  }
  return 0U;
}

static void SM_ClearScreen(void)
{
  /* No banners/instructions — just clear */
  printf(SM_ESC_CLEAR);
}

#ifdef __cplusplus
}
#endif

