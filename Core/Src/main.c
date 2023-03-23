/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "switches.h"
#include "MB1040.h"
#include "motor_functions.h"
#include "logging.h"

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
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  swtiches_config_t rightLimitSwitch;
  swtiches_config_t leftLimitSwitch;
  swtiches_config_t upTiltSwitch;
  swtiches_config_t downTiltSwitch;

  SWITCHES_initialize_switch_config(&rightLimitSwitch, Right_Limit_Switch_Pin, Right_Limit_Switch_GPIO_Port);
  SWITCHES_initialize_switch_config(&leftLimitSwitch, Left_Limit_Switch_Pin, Left_Limit_Switch_GPIO_Port);
  SWITCHES_initialize_switch_config(&upTiltSwitch, Up_Tilt_Switch_Pin, Up_Tilt_Switch_GPIO_Port);
  SWITCHES_initialize_switch_config(&downTiltSwitch, Down_Tilt_Switch_Pin, Down_Tilt_Switch_GPIO_Port);

  switches_instance_t switchesInstance;

  SWITCHES_initiallize_switch_instance(&switchesInstance, &rightLimitSwitch, &leftLimitSwitch, &upTiltSwitch, &downTiltSwitch);

  motor_config_t rightMotor;
  motor_config_t leftMotor;

  MOTOR_initialize_motor_config(&rightMotor, Right_Motor_Driver_DIR_Pin_GPIO_Port, Right_Motor_Driver_DIR_Pin_Pin);
  MOTOR_initialize_motor_config(&leftMotor, Left_Motor_Driver_DIR_Pin_GPIO_Port, Left_Motor_Driver_DIR_Pin_Pin);

  motor_instance_t motorInstance;

  MOTOR_initialize_motor_instance(&motorInstance, &htim3, rightMotor, leftMotor); 

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); 

  uint8_t upStatus;
  uint8_t downStatus;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Recognize Up
    while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {
      upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
      downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

      logging(&huart2, 0, &switchesInstance, &motorInstance);
    }

    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

    MOTOR_move_speed_forward(25000, &motorInstance);

    upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

    logging(&huart2, 0, &switchesInstance, &motorInstance);   
    
    while((upStatus == 0) && (downStatus == 0)) {
      upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
      downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

      logging(&huart2, 0, &switchesInstance, &motorInstance);      
    }

    if(upStatus == 1) {
      HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
    }

    MOTOR_move_speed_forward(40000, &motorInstance);

    // Recognize Top
    while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {
      upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
      downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

      logging(&huart2, 0, &switchesInstance, &motorInstance);
    }

    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

    MOTOR_move_speed_forward(25000, &motorInstance);

    upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);
    
    while((upStatus == 1) && (downStatus == 0)) {
      upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
      downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

      logging(&huart2, 0, &switchesInstance, &motorInstance);      
    }

    if((upStatus == 0) && (downStatus == 0)) {
      HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
    }

    MOTOR_stop_both(&motorInstance);

    // // Recognize Down
    // while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {
    //   upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    //   downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

    //   logging(&huart2, 0, &switchesInstance, &motorInstance);
    // }

    // HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

    // MOTOR_move_speed_forward(25000, &motorInstance);

    // upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    // downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);
    
    // while((upStatus == 0) && (downStatus == 0)) {
    //   upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    //   downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

    //   logging(&huart2, 0, &switchesInstance, &motorInstance);      
    // }

    // if((upStatus == 0) && (downStatus == 1)) {
    //   HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
    // }

    // MOTOR_stop_both(&motorInstance);

    // // Recognize Bottom
    // while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {
    //   upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    //   downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

    //   logging(&huart2, 0, &switchesInstance, &motorInstance);
    // }

    // HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

    // MOTOR_move_speed_forward(25000, &motorInstance);

    // upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    // downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);
    
    // while((upStatus == 0) && (downStatus == 1)) {
    //   upStatus = SWITCHES_get_up_tilt_switch(&switchesInstance);
    //   downStatus = SWITCHES_get_down_tilt_switch(&switchesInstance);

    //   logging(&huart2, 0, &switchesInstance, &motorInstance);      
    // }

    // if((upStatus == 0) && (downStatus == 0)) {
    //   HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
    // }

    // MOTOR_stop_both(&motorInstance);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 16;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|Left_Motor_Driver_DIR_Pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Right_Motor_Driver_DIR_Pin_GPIO_Port, Right_Motor_Driver_DIR_Pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin Left_Motor_Driver_DIR_Pin_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|Left_Motor_Driver_DIR_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Up_Tilt_Switch_Pin */
  GPIO_InitStruct.Pin = Up_Tilt_Switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Up_Tilt_Switch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Left_Limit_Switch_Pin Right_Limit_Switch_Pin */
  GPIO_InitStruct.Pin = Left_Limit_Switch_Pin|Right_Limit_Switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Down_Tilt_Switch_Pin */
  GPIO_InitStruct.Pin = Down_Tilt_Switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Down_Tilt_Switch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Right_Motor_Driver_DIR_Pin_Pin */
  GPIO_InitStruct.Pin = Right_Motor_Driver_DIR_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Right_Motor_Driver_DIR_Pin_GPIO_Port, &GPIO_InitStruct);

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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
