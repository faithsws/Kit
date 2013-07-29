#include "main.h"
#include "stm8s.h"
void relay_init()
{
  GPIO_Init(RELAY_GPIO_PORT, (GPIO_Pin_TypeDef)RELAY_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}
void relay(char on)
{
  if(on)
    GPIO_WriteLow(RELAY_GPIO_PORT,RELAY_PIN);
  else
    GPIO_WriteHigh(RELAY_GPIO_PORT,RELAY_PIN);
}