#include "main.h"
#include "stm8s.h"
void buzzer_init()
{
  GPIO_Init(BUZZER_GPIO_PORT, (GPIO_Pin_TypeDef)BUZZER_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}
void buzzer(char on)
{
  if(on)
    GPIO_WriteLow(BUZZER_GPIO_PORT,BUZZER_PIN);
  else
    GPIO_WriteHigh(BUZZER_GPIO_PORT,BUZZER_PIN);
}