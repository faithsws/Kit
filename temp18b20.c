#include "main.h"
#include "stm8s.h"
void temp18b20_init()
{

}
void OUT_CLR_DQ()
{
  GPIO_Init(TEMP_18B20_PORT, (GPIO_Pin_TypeDef)TEMP_18B20_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}
void OUT_SET_DQ()
{
  GPIO_Init(TEMP_18B20_PORT, (GPIO_Pin_TypeDef)TEMP_18B20_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}

void IN_DQ()
{
  GPIO_Init(TEMP_18B20_PORT, (GPIO_Pin_TypeDef)TEMP_18B20_PIN, GPIO_MODE_IN_FL_NO_IT);
}
BitStatus GET_DQ()
{
  return GPIO_ReadInputPin(TEMP_18B20_PORT, (GPIO_Pin_TypeDef)TEMP_18B20_PIN);
}
void _delay_us(short us)
{
	while(--us);
}

//-----复位-----
void resetOnewire(void) 
{
	OUT_CLR_DQ();
	_delay_us(1500);
	OUT_SET_DQ();
	_delay_us(120);
	IN_DQ(); 
	//while(GET_DQ());
	while(!(GET_DQ()));
	OUT_SET_DQ();
}

//-----读数据-----
unsigned char rOnewire(void)
{
	unsigned char data=0,i=0;
	 for(i=0;i<8;i++)
	{
		data=data>>1;
		OUT_CLR_DQ();
		IN_DQ();
		if(GET_DQ()) data|=0x80;
		else while(!(GET_DQ()));
		_delay_us(200);
	}
	return(data);
}
//-----写数据-----
void wOnewire(unsigned char data)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		OUT_CLR_DQ();
		if(data&0x01)
		{
		OUT_SET_DQ();
		}
		else
		{
		OUT_CLR_DQ();
		}
		data=data>>1;
		_delay_us(200);  //65
		OUT_SET_DQ();
	}
}

//-----DS18B20转换温度-----
void convertDs18b20(void) 
{ 
	resetOnewire(); 
	wOnewire(0xcc); 
	wOnewire(0x44); 
}
//------------DS18BB0读温度----------
//return  temperature * 10

short readTemp(void) 
{ 
	unsigned char temp1,temp2;
        short temp;
	convertDs18b20();
	resetOnewire(); 
	wOnewire(0xcc); 
	wOnewire(0xbe); 	
	temp1=rOnewire(); 
	temp2=rOnewire(); 
        temp = (unsigned short)temp1 | (((unsigned short)temp2 & 0x0f) << 8) ;
        if(temp2 & 0xf0)return (short)(-temp*0.625);
        return (short)(temp*0.625);
        
}
void test_time()
{
  while(1)
  {
  _delay_us(150);
  OUT_CLR_DQ();
   _delay_us(150);
  OUT_SET_DQ();
  }
}