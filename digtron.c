#include "main.h"
#include "stm8s.h"
char dig_mod[] = {0x7b,0x60,0x37,0x75,0x6c,0x5d,0x5f,0x70,0x7f,0x7d};

void digtron_init()
{
  GPIO_Init(DIGTRON_PORT, (GPIO_Pin_TypeDef)DIGTRON_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
}
void digtron_mod(short l)
{
  int i = 0;
  short tmp = ((l >> 8)&0xff) | ((l & 0xff) << 8);
  //short tmp = l;
  GPIO_WriteLow(DIGTRON_PORT,RCK);
  for(i = 0;i < 16;i++)
  {
    GPIO_WriteLow(DIGTRON_PORT,SCK);
    if(tmp & 0x01)
      GPIO_WriteHigh(DIGTRON_PORT,SI);
    else
      GPIO_WriteLow(DIGTRON_PORT,SI);
    GPIO_WriteHigh(DIGTRON_PORT,SCK);
    tmp >>= 1;
  }
  
  
  GPIO_WriteHigh(DIGTRON_PORT,RCK);
}
void digtron_display(char l)
{
  
  char a = l/10;
  char b = l%10;
  a = a> 9?9:a;
  short mod = ~((dig_mod[a] << 8) | dig_mod[b]);
  digtron_mod(mod);
}
void digtron_display_none()
{
  digtron_mod(~0x0404);
}