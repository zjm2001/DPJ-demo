#include <ioCC2530.h>
#include "stdio.h"

//延时
void Delay(unsigned int n)
{
	unsigned int i;
	for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
}
//切换时钟的选择函数
void Set_Click(unsigned int clk){
  if(clk==16){
    //切换到16HMz
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    //切换到32HMz
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}

  void Init_uart0(){
  PERCFG &= ~0X01;    //初始化定时器1通道0的外设映射备用位置1
  P0SEL |= 0X0C;   // 0000 1100
  U0BAUD = 216;
  U0GCR = 11;
  U0UCR |= 0X80;
  U0CSR |=  0XC0;
}

//发送函数
void UR0_SendByte(unsigned char dat){
   U0DBUF = dat;
   while(UTX0IF == 0);  //等待TX中断标志，即数据发送完成 
   UTX0IF = 0;           //清除TX中断标志，准备下一次发送
}

void UR0_SendString(unsigned char * str)
{
  while(*str != '\0')       //发送一个字符串
  {
    UR0_SendByte(*str++);    //逐个发送字符串中的字节
  }
}

//主函数
void main(){
  Set_Click(32);  //设置32
  Init_uart0(); //串口初始化
  Delay(60000);
  UR0_SendString("AT+CWMODE=3\r\n");   
  Delay(60000);
  UR0_SendString("AT+CWJAP=\"zjm\",\"zjm555555\"\r\n");   //连接wifi
  Delay(60000);
  Delay(60000);
  Delay(60000); 
  Delay(60000);  //用户信息配置
  UR0_SendString("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"); 
  Delay(60000);
  Delay(60000); 
  UR0_SendString("AT+CIPSEND\r\n");  
  Delay(60000);
  Delay(60000); 
  
  

  while(1){
    UR0_SendString("POST /devices/1152311362/datapoints HTTP/1.1/r/n api-key:KX94Vgh9DdXpgEg9w=GHSLCjLJ0=/r/n Host:api.heclouds.com/r/n Connection:close/r/n Content-Length:63/r/n {\"Temp\":14}/r/n");
    Delay(60000);
    Delay(60000);
    Delay(60000); 
   UR0_SendString("POST /devices/1152311362/datapoints HTTP/1.1/r/n api-key:KX94Vgh9DdXpgEg9w=GHSLCjLJ0=/r/n Host:api.heclouds.com/r/n Connection:close/r/n Content-Length:63/r/n {\"Temp\":50}/r/n");
   Delay(60000);
   Delay(60000);
   Delay(60000); 
  }
  
}