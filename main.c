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
#include "main.h"
#include "eep.h"
#include "spi_sd.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */



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
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE (countof(TxBuffer)-1)

/* Private variables ---------------------------------------------------------*/
__IO uint16_t Status = 0;
uint8_t TxBuffer[] = "STM8S SPI Firmware Library Example: communication with a microSD card";
uint8_t RxBuffer[BUFFER_SIZE] = {0};


extern char started;
extern unsigned short ms;
void main(void)
{
  int flag = 0;
  unsigned short led = 0x8000;
  char i = 1;
  BitStatus bs = SET;
  unsigned short cnt = 0; 
   KEY_CODE key;
  uint16_t status;
  
 // CLK_Config();
    /* Initialize I/Os in Output Mode */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  disableInterrupts();  

#if 1
  buzzer_init();
  digtron_init();
   
  led_init();
 
  //temp18b20_init();
  uart_init();
  key_init();
  
  lcddig_init();
  relay_init();
  //sEE_Init();
  infr_init();
  enableInterrupts(); 

  ds1302_init();
 #endif
  status = SD_Init();

   /* Write block of 512 bytes on address 0 */
  SD_WriteBlock(TxBuffer, 0, BUFFER_SIZE);

  /* Read block of 512 bytes from address 0 */
  SD_ReadBlock(RxBuffer, 0, BUFFER_SIZE);
  
  char buf[7] = {0};
  //  char readbuf[10];
  //lcddig_poweron(1);
  //lcddig_display_int(12345);
  char last_second;
  char last_minute;
  unsigned char time_buf[7] = {55,55,11,27,7,5,13};
  //set_time(time_buf);
  read_time(buf);
  lcddig_display_time(buf);
  last_second= buf[0];
  last_minute = buf[1];
  while (1)
  {
    //bs = GPIO_ReadInputPin(LED_GPIO_PORT,HALL);
    //if(RESET == GPIO_ReadInputPin(LED_GPIO_PORT,HALL))
    //{
   //   ms = 0;
 
   // }
    //test_time();
#if 0
     read_time(buf);
     if(buf[0] != last_second)
     {
        led_y_blink();
     }
     last_second = buf[0];
     if(buf[1] != last_minute)
     {
        lcddig_display_time(buf);
     }
     last_minute = buf[1];
     
    //sEE_WriteBuffer(buf,10,10);
    
    //sEE_ReadBuffer(readbuf,10,10);
     flag = get_infr_code();
     if(flag != 0)
     {
        lcddig_display_hex(flag);
     }
 
      uint16_t temp;
      //digtron_display(89);

      key = get_key();
#if 1   
      if(KEY_TOP == key)
      {
    
      
      }
      else if(KEY_RIGHT == key)
      {
      digtron_display(2);
      
      }
      else if(KEY_LEFT == key)
      {
      digtron_display(3);
      }
      else if(KEY_BOTTOM == key)
      {
      digtron_display(4);
      }
      else 
#endif
      if(KEY_CENTER == key)
      {
      digtron_display(99);
      }
   
      
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
