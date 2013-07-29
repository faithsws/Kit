#include "main.h"
#include "stm8s.h"

void ds1302_init()
{
  GPIO_Init(DS1302_DATA_PORT, (GPIO_Pin_TypeDef)(DS1302_DATA), GPIO_MODE_OUT_PP_HIGH_FAST); 
  GPIO_Init(DS1302_RST_PORT, (GPIO_Pin_TypeDef)(DS1302_RST ), GPIO_MODE_OUT_PP_HIGH_FAST); 
  GPIO_Init(DS1302_SCLK_PORT, (GPIO_Pin_TypeDef)(DS1302_SCLK), GPIO_MODE_OUT_PP_HIGH_FAST); 
}
static void sclk(char h)
{
  if(h)
    GPIO_WriteHigh(DS1302_SCLK_PORT,DS1302_SCLK);
  else
    GPIO_WriteLow(DS1302_SCLK_PORT,DS1302_SCLK);
}
static void data_out(char h)
{
  GPIO_Init(DS1302_DATA_PORT,(GPIO_Pin_TypeDef)DS1302_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
  if(h)
    GPIO_WriteHigh(DS1302_DATA_PORT,DS1302_DATA);
  else
    GPIO_WriteLow(DS1302_DATA_PORT,DS1302_DATA);
}
static BitStatus data_in()
{
  GPIO_Init(DS1302_DATA_PORT, (GPIO_Pin_TypeDef)(DS1302_DATA ), GPIO_MODE_IN_FL_NO_IT);
  return GPIO_ReadInputPin(DS1302_DATA_PORT,(GPIO_Pin_TypeDef)(DS1302_DATA ));
}
static void rst(char h)
{
  if(h)
    GPIO_WriteHigh(DS1302_RST_PORT,DS1302_RST);
  else
    GPIO_WriteLow(DS1302_RST_PORT,DS1302_RST);
}
static void write_byte(unsigned char data)
{
  unsigned char i;
  for(i = 0;i< 8;i++)
  {
    sclk(0);
    if(data & 0x01)
      data_out(1);
    else
      data_out(0);
    data >>= 1;
    sclk(1);
  }
}
static unsigned char read_byte()
{
  unsigned char i,temp = 0;
  BitStatus bit;
  for(i = 0;i< 8;i ++)
  {
    temp = temp>>1;
    sclk(0);
    bit = data_in();
    if(bit == RESET)
    {
      
    }
    else
    {
      temp = temp | 0x80;
    }
    sclk(1);
  }
  return temp;
}
static void write(unsigned char  addr,unsigned char data)
{
  rst(0);
  sclk(0);
  rst(1);
  write_byte(addr);
  write_byte(data);
  rst(0);
  sclk(1);
  data_out(1);
}
static unsigned char read(unsigned char addr)
{
  unsigned char temp = 0;
  rst(0);
  sclk(0);
  rst(1);
  write_byte(addr);
  temp = read_byte();
  rst(0);
  sclk(1);
  data_out(1);
  return temp;
}
void set_time(unsigned char time[])
{
  unsigned char i,add,temp;
  write(0x8e,0);
  for(i = 0,add = 0x80;i<7;i++,add+=2)
  {
    temp = time[i]/10;
    time[i] = time[i]%10 + temp*16;
    write(add,time[i]);
  }
  write(0x8e,0x80);
}
void read_time(unsigned char time[7])
{
  unsigned char i , add,temp;
  for(i = 0,add = 0x81;i<7;i++,add+=2)
  {
    temp = read(add);
    time[i] = (temp>>4)*10+temp%16;
  }
}