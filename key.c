#include "main.h"
#include "stm8s.h"


void key_init()
{
  GPIO_Init(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY1_PIN, GPIO_MODE_IN_PU_NO_IT);

  
  //GPIO_Init(AD_KEY_PORT, (GPIO_Pin_TypeDef)AD_KEY_PIN, GPIO_MODE_IN_FL_NO_IT);
  
  ADC1_DeInit();

  /* Init ADC2 peripheral */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_0, ADC1_PRESSEL_FCPU_D2, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL0,\
            DISABLE);
  ADC1_Cmd(ENABLE);
  
}



uint16_t abs(int val)
{
  return val > 0?val:-val;
}
uint16_t get_adc_key1()
{
  uint16_t val1,val2;
  Delay(5000);
  ADC1_StartConversion();
  while(RESET == ADC1_GetFlagStatus(ADC1_FLAG_EOC));
  ADC1_ClearFlag(ADC1_FLAG_EOC);
  val1 = ADC1_GetConversionValue();
  if(val1 > 1000)return val1;
  do
  {
    Delay(5000);
    ADC1_StartConversion();
    while(RESET == ADC1_GetFlagStatus(ADC1_FLAG_EOC));
    ADC1_ClearFlag(ADC1_FLAG_EOC);
    val2 = ADC1_GetConversionValue();
  }while(abs(val2-val1) < 50);
  
  Delay(35000);
  return val1;
}
KEY_CODE  get_gpio_key()
{
  if(GPIO_ReadInputPin(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY1_PIN))
    return KEY_NONE;
  Delay(30000);
  if(GPIO_ReadInputPin(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY1_PIN))
    return KEY_NONE;
  while(RESET == GPIO_ReadInputPin(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY1_PIN));
  return KEY_CENTER;
}
KEY_CODE get_adc_key()
{
  uint16_t val =get_adc_key1();

  if(val < 100)
    return KEY_RIGHT;
  else if(val < 600)
    return KEY_LEFT;
  else if(val < 710)
    return KEY_BOTTOM;
  else if(val < 800)
    return KEY_TOP;
  else 
    return KEY_NONE;
}
#define USE_ADC_KEY
KEY_CODE get_key()
{
  if(get_gpio_key() != KEY_NONE)
    return KEY_CENTER;
#ifdef USE_ADC_KEY
  return get_adc_key();
#else
  return KEY_NONE;
#endif
}