#include "main.h"
#include "stm8s.h"

void uart_init()
{
   CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  UART1_DeInit();
  UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  UART1_Cmd(ENABLE);
}

void uart_send_byte(char c)
{
  UART1_SendData8(c);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}
void uart_send_string(char * str)
{
  while(*str != '\0')
  {
    uart_send_byte(*str);
    str ++;
  }
}

char *hex_str = "0123456789abcdef";
void uart_send_16hex(short hex)
{
  unsigned char ll = 0;
  int i = 0;
  for(i = 0;i<4;i++)
  {
    ll = ((hex & 0xf000) >> 12) & 0x0f;
    hex = hex << 4;
    uart_send_byte(hex_str[ll]);
  }
}