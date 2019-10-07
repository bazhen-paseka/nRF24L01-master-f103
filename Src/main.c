/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
	#include <string.h>
	#include <stdio.h>
	#include "NRF24L01_sm.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define MY_CHANNEL 106
/* My address */
uint8_t MyAddress[] = { 0x56, 0x56, 0x56, 0x56, 0x56 };
/* Other end address */
uint8_t TxAddress[] = { 0x65, 0x65, 0x65, 0x65, 0x65 };
/* Data received and data for send */
// uint8_t dataOut[32];
uint8_t dataIn[32];
/* NRF transmission status */
NRF24L01_Transmit_Status_t transmissionStatus;

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
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	char DataChar[100];
	sprintf(DataChar,"\r\n nRF24L01 v1.0.0\r\nUART1 for debug started on speed 115200\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);

	NRF24L01_Init(&hspi2, MY_CHANNEL, 32);
	/* Set 250kBps data rate and -6dBm output power */
	NRF24L01_SetRF(NRF24L01_DataRate_250k, NRF24L01_OutputPower_M6dBm);
	/* Set my address, 5 bytes */
	NRF24L01_SetMyAddress(MyAddress);
	/* Set TX address, 5 bytes */
	NRF24L01_SetTxAddress(TxAddress);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//
//#ifdef MASTER
//		/* Every 2 seconds */
//		if (HAL_GetTick() - lastTime > 2000) {
//
//			/* Fill data with something */
//			sprintf((char *) dataOut, "Good news everyone! #%d", i++);
//			//LCD_Printf("Sending data: \n");
//			sprintf(DataChar,"Sending data: \r\n");
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//
//			//LCD_Printf("%s\n", dataOut);
//			sprintf(DataChar,"%s\n", dataOut);
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//
//			/* Transmit data, goes automatically to TX mode */
//			NRF24L01_Transmit(dataOut);
//			/* Wait for data to be sent */
//			do {
//				/* Get transmission status */
//				transmissionStatus = NRF24L01_GetTransmissionStatus();
//			} while (transmissionStatus == NRF24L01_Transmit_Status_Sending);
//			sendTime = HAL_GetTick();
//
//			/* Go back to RX mode */
//			NRF24L01_PowerUpRx();
//			/* Wait received data, wait max 100ms, if time is larger, then data were probably lost */
//			while (!NRF24L01_DataReady() && (HAL_GetTick() - sendTime) < 100);
//
//			/* Show ping time */
//			//LCD_Printf("%d ms\n", HAL_GetTick() - sendTime);
//			sprintf(DataChar,"%d ms\r\n", HAL_GetTick() - sendTime);
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			//LCD_Printf("Receiving back: \n");
//			sprintf(DataChar,"Receiving back: \r\n");
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			/* Get data from NRF2L01+ */
//			NRF24L01_GetData(dataIn);
//			//LCD_Printf("%s\n", dataIn);
//			sprintf(DataChar,"%s\r\n", dataIn);
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			/* Check transmit status */
//			//LCD_Printf("Status: ");
//		sprintf(DataChar,"Status: ");
//		HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			if (transmissionStatus == NRF24L01_Transmit_Status_Ok) {
//				/* Transmit went OK */
//				//LCD_Printf("OK\n");
//				sprintf(DataChar,"OK\r\n");
//				HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			} else if (transmissionStatus == NRF24L01_Transmit_Status_Lost) {
//				/* Message was LOST */
//				//LCD_Printf("LOST\n");
//				sprintf(DataChar,"LOST\r\n");
//				HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			} else {
//				/* This should never happen */
//			//LCD_Printf("SENDING\n");
//				sprintf(DataChar,"Sending data: \r\n");
//				HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			}
//
//			errors = 0;
//			for (int k = 0; k < sizeof(dataIn) / sizeof(dataIn[0]); k++) {
//				errors += (dataIn[k]!=dataOut[k]);
//			}
//			//LCD_Printf("Errors: %d\n", errors);
//			sprintf(DataChar,"Errors: %d\r\n", errors);
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			//LCD_Printf("\n");
//			sprintf(DataChar,"\r\n");
//			HAL_UART_Transmit(&huart1, (uint8_t *)DataChar, strlen(DataChar), 100);
//			lastTime = HAL_GetTick();
//		}
//#else
//		/* If data is ready on NRF24L01+ */
//		if (NRF24L01_DataReady()) {
//			/* Get data from NRF24L01+ */
//			NRF24L01_GetData(dataIn);
//			HAL_Delay(1);
//			/* Send it back, automatically goes to TX mode */
//			NRF24L01_Transmit(dataIn);
//
//			/* Wait for data to be sent */
//			do {
//				/* Wait till sending */
//				transmissionStatus = NRF24L01_GetTransmissionStatus();
//			} while (transmissionStatus == NRF24L01_Transmit_Status_Sending);
//			/* Send done */
//
//			/* Check data & transmit status */
//			LCD_Printf("\n");
//			LCD_Printf("Data received:\n");
//			LCD_Printf("%s\n", dataIn);
//			LCD_Printf("Sending it back\n");
//			LCD_Printf("Status: ");
//			if (transmissionStatus == NRF24L01_Transmit_Status_Ok) {
//				/* Transmit went OK */
//				LCD_Printf("OK\n");
//			} else {
//				/* Message was LOST */
//				LCD_Printf("ERROR\n");
//			}
//
//			/* Go back to RX mode */
//			NRF24L01_PowerUpRx();
//			i = 0;
//		} else {
//			if (HAL_GetTick() - lastTime > 250) {
//			    if (i == 0) {
//			        LCD_Printf("Waiting for data");
//			        i++;
//			    } else if (i > 17) {
//			        LCD_Printf("\r");
//			        i = 0;
//			    } else {
//			        LCD_Printf(".");
//			        i++;
//			    }
//			    lastTime = HAL_GetTick();
//			}
//		}
//#endif

	  if (NRF24L01_DataReady()) {
	  			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	  			/* Get data from NRF24L01+ */
	  			NRF24L01_GetData(dataIn);
	  			/* Send it back, automatically goes to TX mode */
	  			NRF24L01_Transmit(dataIn);
	  			/* Wait for data to be sent */
	  			do {
	  				/* Wait till sending */
	  				transmissionStatus = NRF24L01_GetTransmissionStatus();
	  			} while (transmissionStatus == NRF24L01_Transmit_Status_Sending);
	  			/* Send done */
	  			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	  			/* Go back to RX mode */
	  			NRF24L01_PowerUpRx();
	  		}
	  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	 // HAL_Delay(200);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
