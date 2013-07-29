/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */

#define LED_GPIO_PORT  (GPIOD)


#define HALL GPIO_PIN_3
#define SI  GPIO_PIN_4
#define SCK GPIO_PIN_7
#define RCK GPIO_PIN_6
#define EN  GPIO_PIN_5
#define LED_GPIO_PINS (SI | SCK | RCK | EN)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void enable_out()
{
  GPIO_WriteLow(LED_GPIO_PORT,EN);
}

void display(short l)
{
  int i = 0;
  short tmp = ((l >> 8)&0xff) | ((l & 0xff) << 8);
  
  GPIO_WriteLow(LED_GPIO_PORT,RCK);
  for(i = 0;i < 16;i++)
  {
    GPIO_WriteLow(LED_GPIO_PORT,SCK);
    if(tmp & 0x01)
      GPIO_WriteHigh(LED_GPIO_PORT,SI);
    else
      GPIO_WriteLow(LED_GPIO_PORT,SI);
    GPIO_WriteHigh(LED_GPIO_PORT,SCK);
    tmp >>= 1;
  }
  
  
  GPIO_WriteHigh(LED_GPIO_PORT,RCK);
}

static void CLK_Config(void)
{
    ErrorStatus status = FALSE;

    CLK_DeInit();

    /* Configure the Fcpu to DIV1*/
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    
    /* Configure the HSI prescaler to the optimal value */
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

      
    /* Configure the system clock to use HSE clock source and to run at 24Mhz */
    status = CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
    
  
}
static void TIM2_Config(void)
{
  TIM2_DeInit();
  TIM2_ICInit( TIM2_CHANNEL_2, TIM2_ICPOLARITY_RISING, TIM2_ICSELECTION_DIRECTTI,
               TIM2_ICPSC_DIV8, 0x0);
  
  TIM2_ITConfig(TIM2_IT_CC2,ENABLE);
  TIM2_ClearFlag(TIM2_FLAG_CC2);
   /* Enable TIM1 */
  TIM2_Cmd(ENABLE);

  
}
static void TIM4_Config(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  
  /* enable interrupts */
  enableInterrupts();

  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}

extern char started;
extern unsigned char s;
void main(void)
{
  int flag = 0;
  unsigned short led = 0x8000;
  char i = 1;
  BitStatus bs;
  unsigned short cnt = 0; 
  
  CLK_Config();
    /* Initialize I/Os in Output Mode */
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)HALL,GPIO_MODE_IN_FL_IT);
  
  TIM4_Config();
  
  
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
  
  enableInterrupts();
  enable_out();
   //60000 = 180
  //15000 = 45 
  #define test_timer 15000
  
  while (1)
  {
#if 0
    display(0);
    if(started ==0)continue;
    started = 0;

    display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     Delay(10000);
     display(0xffff);
    Delay(133);
    display(0);
     //Delay(10000);
#endif
#if 0   
   
    display(1);
    Delay(test_timer);
    display(2);
    Delay(test_timer);
    display(4);
    Delay(test_timer);
    display(8);
    Delay(test_timer);
    display(16);
    Delay(test_timer);
    display(32);
    Delay(test_timer);
    display(64);
    Delay(test_timer);
    display(128);
    Delay(test_timer);
    display(0);
#endif
    //bs = GPIO_ReadInputPin(LED_GPIO_PORT,HALL);
    //display(bs);
    //Delay(0xffff);
#if 0
    /* Toggles LEDs */
    if(flag ==0)
      led >>= 1;
    else
      led <<= 1;
    display(led);
    Delay(test_timer);
    display(0);
    Delay(test_timer/2);
    if(led == 0x0001)
    {
      flag = 1;
    }
    if(led == 0x8000)
      flag = 0;
#endif
    
    
  }

  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
