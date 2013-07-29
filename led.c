#include "main.h"
#include "stm8s.h"

void led_init()
{
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}
void led_y(char on)
{
  if(!on)
    GPIO_WriteLow(LED_GPIO_PORT,LED_PIN);
  else
    GPIO_WriteHigh(LED_GPIO_PORT,LED_PIN);
}
void led_y_blink()
{
  GPIO_WriteReverse(LED_GPIO_PORT,LED_PIN);
}