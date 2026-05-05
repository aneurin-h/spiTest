/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for SPI */
osThreadId_t SPIHandle;
const osThreadAttr_t SPI_attributes = {
  .name = "SPI",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DebugLED */
osThreadId_t DebugLEDHandle;
const osThreadAttr_t DebugLED_attributes = {
  .name = "DebugLED",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartSPIDebug(void *argument);
void StartLED(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationDaemonTaskStartupHook(void);

/* USER CODE BEGIN DAEMON_TASK_STARTUP_HOOK */
void vApplicationDaemonTaskStartupHook(void)
{
}
/* USER CODE END DAEMON_TASK_STARTUP_HOOK */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of SPI */
  SPIHandle = osThreadNew(StartSPIDebug, NULL, &SPI_attributes);

  /* creation of DebugLED */
  DebugLEDHandle = osThreadNew(StartLED, NULL, &DebugLED_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartSPIDebug */
/**
  * @brief  Function implementing the SPI thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartSPIDebug */
void StartSPIDebug(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartSPIDebug */
  /* Infinite loop */
  for(;;)
  {
	uint16_t data = 85; // Random non-zero number
	HAL_SPI_Transmit(&hspi2, data, sizeof(data), 1000); //Sends the number 85 over SPI2 (radios SPI bus), with a 1s timeout
    osDelay(500); // Repeats every half second
  }
  /* USER CODE END StartSPIDebug */
}

/* USER CODE BEGIN Header_StartLED */
/**
* @brief Function implementing the DebugLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED */
void StartLED(void *argument)
{
  /* USER CODE BEGIN StartLED */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, GPIO_PIN_RESET);
	osDelay(500);
    HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, GPIO_PIN_SET);
    osDelay(500);
  }
  /* USER CODE END StartLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

