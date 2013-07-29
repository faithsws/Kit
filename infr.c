#include "stm8s.h"
#include "main.h"
uint16_t infr_buf[INFR_BUF_SIZE] = {0};
char infr_cnt = 0;
char infr_flag = 0;
void infr_init()
{
  //use timer1 channel1 to capture
  TIM1_ICInit( TIM1_CHANNEL_1, TIM1_ICPOLARITY_FALLING, TIM1_ICSELECTION_DIRECTTI,
               TIM1_ICPSC_DIV1, 0x0);
  
  /* Enable TIM1 */
  TIM1_Cmd(ENABLE);

  /* Clear CC1 Flag*/
  TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  TIM1_ITConfig(TIM1_IT_CC1,ENABLE);
}

char get_infr_code()
{
  char i;
  short opcode = 0;
  
  if(infr_cnt > infr_flag +32)
  {
   
      TIM1_ITConfig(TIM1_IT_CC1,DISABLE);
      
      for(i = infr_flag +17;i<infr_flag +33;i++)
      {
        if(infr_buf[i] > 25000)
          opcode |= (0x01 << (infr_flag +32 - i));
      }
      
      
      for(i = 0;i<INFR_BUF_SIZE;i++)
        infr_buf[i] = 0;
      infr_cnt = 0;
      TIM1_ITConfig(TIM1_IT_CC1,ENABLE);
      
      infr_flag = 0;
      if(((opcode >> 8)&0xff) != (~opcode&0xff))
        return 0;
      return (char)(opcode >> 8)&0xff;
    
    
  }

  return 0;
}