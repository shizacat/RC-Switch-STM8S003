/**
  ******************************************************************************
  * @file     TIM1_Input_Capture\main.c
  * @author   MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief    This file contains the main function for TIM1 Input Capture example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/**
  * @addtogroup TIM1_Input_Capture
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// uint32_t TIM1ClockFreq = 2000000;
// __IO uint32_t LSIClockFreq = 0;
uint16_t ICValue1 =0, ICValue2 =0;
uint8_t state =0;
/* Private function prototypes -----------------------------------------------*/
static void TIM1_Config(void);
static void GPIO_Config(void);
static void CLK_Config(void);
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{

  /* GPIO CONFIG ----------------------------------------------- */
  GPIO_Config();
  // GPIO_Init(GPIOE, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);

  CLK_Config();
  /* TIM1 configuration -----------------------------------------*/
  TIM1_Config();
    
  /* Compute LSI clock frequency */
  // LSIClockFreq = (8 * TIM1ClockFreq) / (ICValue2 - ICValue1);
  
  //Test
  // GPIO_WriteLow(GPIOC, GPIO_PIN_3);

  /* Insert a break point here */
  while (1)
  {
    if (TIM1_GetFlagStatus(TIM1_FLAG_CC1) == SET) {
      // GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
      if(state == FALSE)          {
          ICValue1 = TIM1_GetCapture1();
          TIM1_ICInit(
            TIM1_CHANNEL_1, TIM1_ICPOLARITY_FALLING, TIM1_ICSELECTION_DIRECTTI,
            TIM1_ICPSC_DIV1, 0x0
          );
      }
      else {
          ICValue2 = TIM1_GetCapture1();
          TIM1_ICInit(
            TIM1_CHANNEL_1, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI,
            TIM1_ICPSC_DIV1, 0x0
          );
          if ((ICValue2 - ICValue1) >= 80) {
            GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
          } else {
            GPIO_WriteLow(GPIOC, GPIO_PIN_3);
          };
      }
      state = ~state;
      TIM1_ClearFlag(TIM1_FLAG_CC1);
    }
  }
}

/**
  * @brief  Configure ports
  * @param  None
  * @retval None
  */
static void GPIO_Config(void){
  /* Connect LSI to COO pin*/
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  CLK_CCOConfig(CLK_OUTPUT_LSI);
  CLK_CCOCmd(ENABLE);

  // Pin to transistor key
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
  // Pin input signal
  // GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);
}

/**
  * @brief  Switch to LSI as system clock source.
            System clock prescaler: 1
  * @param  None
  * @retval None
  */
static void CLK_Config(void){
  // CLK_DeInit();

  CLK_LSICmd(ENABLE);
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_ClockSwitchConfig(
    CLK_SWITCHMODE_AUTO,
    CLK_SOURCE_LSI, 
    DISABLE,
    CLK_CURRENTCLOCKSTATE_DISABLE
  );

  // Настраиваем переферию
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART2, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_CAN, DISABLE);

  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);
}

/**
  * @brief  Configure TIM1 to to capture the internal clock source (LSI)
  * @param  None
  * @retval None
  */
static void TIM1_Config(void)
{
  TIM1_DeInit();

  TIM1_TimeBaseInit(27, TIM1_COUNTERMODE_UP, 0xFFFF, 0);
  TIM1_ICInit(
    TIM1_CHANNEL_1, TIM1_ICPOLARITY_FALLING, TIM1_ICSELECTION_DIRECTTI,
    TIM1_ICPSC_DIV1, 0x0
  );
  
  // /* Enable TIM1 */
  TIM1_Cmd(ENABLE);

  // TIM1_ClearFlag(TIM1_FLAG_CC1);
  // // while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  // while(TIM1_GetFlagStatus(TIM1_FLAG_CC1) == SET);
  // GPIO_WriteHigh(GPIOC, GPIO_PIN_3);


  // /* Clear CC1 Flag*/
  // TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  // /* wait a capture on CC1 */
  // while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  // /* Get CCR1 value*/
  // ICValue1 = TIM1_GetCapture1();
  // TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  // /* wait a capture on cc1 */
  // while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  // /* Get CCR1 value*/
  // ICValue2 = TIM1_GetCapture1();
  // TIM1_ClearFlag(TIM1_FLAG_CC1);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
