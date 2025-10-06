/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "app_tof.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "serial_monitor.h"
#include "stm32l4xx_nucleo_bus.h"   // BSP I2C (hi2c1, BSP_I2C1_Init)
#include "oled_ssd1306.h"           // our OLED driver
#include "serial_monitor.h"
#include "ROI.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// ---- Tunable thresholds with hysteresis (mm) ----
#define NEAR_ON_MM    300
#define NEAR_OFF_MM   350   // leave NEAR only when >350
#define MID_ON_MM     750
#define MID_OFF_MM    800   // leave MID to FAR only when >800

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static OLED_t oled;                 // OLED context
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE BEGIN 0 */
static void PowerOnSelfTest(void)
{
  // LEDs off first
  HAL_GPIO_WritePin(Red_LED_GPIO_Port,    Red_LED_Pin,    GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Yellow_LED_GPIO_Port, Yellow_LED_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Green_LED_GPIO_Port,  Green_LED_Pin,  GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Buzzer_GPIO_Port,     Buzzer_Pin,     GPIO_PIN_RESET);
  HAL_Delay(50);

  // Blink R -> Y -> G
  HAL_GPIO_WritePin(Red_LED_GPIO_Port,   Red_LED_Pin,   GPIO_PIN_SET); HAL_Delay(200);
  HAL_GPIO_WritePin(Red_LED_GPIO_Port,   Red_LED_Pin,   GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Yellow_LED_GPIO_Port,Yellow_LED_Pin,GPIO_PIN_SET); HAL_Delay(200);
  HAL_GPIO_WritePin(Yellow_LED_GPIO_Port,Yellow_LED_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, GPIO_PIN_SET); HAL_Delay(200);
  HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, GPIO_PIN_RESET);

  // Short beep
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);  HAL_Delay(120);
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);

  // === OLED splash ===
  OLED_Init(&oled);
  OLED_Splash(&oled);
  HAL_Delay(800); // visible pause; tune as you like
}

// zone: 0=NEAR, 1=MID, 2=FAR
void ROI_OnUpdate(const ROI_Result_t *roi)
{
  static uint8_t zone = 2; // 0=NEAR, 1=MID, 2=FAR

  if (!roi || !roi->valid) {
    /* No target -> treat as FAR */
    zone = 2;
    HAL_GPIO_WritePin(Buzzer_GPIO_Port,     Buzzer_Pin,     GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Red_LED_GPIO_Port,    Red_LED_Pin,    GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Yellow_LED_GPIO_Port, Yellow_LED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Green_LED_GPIO_Port,  Green_LED_Pin,  GPIO_PIN_SET);

    OLED_Clear(&oled);
    OLED_DrawCentered(&oled, 3, "No target");
    return;
  }

  int d = roi->avg_distance;

  /* --- hysteresis state machine --- */
  switch (zone) {
    case 0: /* NEAR */
      if (d > NEAR_OFF_MM) zone = (d > MID_OFF_MM) ? 2 : 1;
      break;

    case 1: /* MID */
      if (d < NEAR_ON_MM) zone = 0;
      else if (d > MID_OFF_MM) zone = 2;
      break;

    case 2: /* FAR */
      if (d < MID_ON_MM) zone = (d < NEAR_ON_MM) ? 0 : 1;
      break;
  }

  /* --- Drive outputs according to zone --- */
  HAL_GPIO_WritePin(Buzzer_GPIO_Port,     Buzzer_Pin,     (zone==0)?GPIO_PIN_SET:GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Red_LED_GPIO_Port,    Red_LED_Pin,    (zone==0)?GPIO_PIN_SET:GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Yellow_LED_GPIO_Port, Yellow_LED_Pin, (zone==1)?GPIO_PIN_SET:GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Green_LED_GPIO_Port,  Green_LED_Pin,  (zone==2)?GPIO_PIN_SET:GPIO_PIN_RESET);

  /* --- OLED text --- */
  char line1[22], line2[22];
  OLED_Clear(&oled);
  snprintf(line1, sizeof line1, "ROI(%u,%u) %dmm", roi->row, roi->col, d);
  snprintf(line2, sizeof line2, "Zone: %s", (zone==0)?"NEAR":(zone==1)?"MID":"FAR");
  OLED_DrawString(&oled, 0, 2, line1);
  OLED_DrawString(&oled, 0, 4, line2);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_TOF_Init();
  /* USER CODE BEGIN 2 */
  /* BSP I2C for VL53L8CX + OLED (make sure BUS_I2C1_FREQUENCY = 400000U) */
  BSP_I2C1_Init();

  /* OLED context */
  extern I2C_HandleTypeDef hi2c1;   // provided by stm32l4xx_nucleo_bus.h/.c
  oled.hi2c     = &hi2c1;
  oled.addr     = (0x3C << 1);      // 0x3C typical SSD1306, use 0x3D<<1 if needed
  oled.x_offset = 0;                // set 2 if your module is SH1106 with 2-col shift

  PowerOnSelfTest();                // will show splash on OLED
  /*to print my version of serial monitor*/
  MX_SERIALMON_Init();
  ROI_Init();

  while (1)
  {
	  MX_SERIALMON_Process();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //while (1)
  //{
    /* USER CODE END WHILE */

 // MX_TOF_Process();
    /* USER CODE BEGIN 3 */
  //}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
