#include <ioCC2530.h>
#include "stdio.h"
unsigned int adc_value;
unsigned char str[64];
void Init_Port(){
 P1SEL &= ~0X03;   //设置通用i/o口      
 P1DIR |= 0X03;    //作为通用i/o时的输出端口
 P1 |=0x03;       //灯关关闭状态
}
void Set_Click(unsigned char clk){
  if(clk==16){
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}
void Init_uart0(){
  PERCFG &= ~0X01;    
  P0SEL |= 0X0C;   
  U0BAUD = 216;
  U0GCR = 11;
  U0UCR |= 0X80;
  U0CSR |=  0XC0;
  UTX0IF = 0;  //清除除TX发送中断标志
  URX0IF = 0;  //清除除TX接收中断标志
  URX0IE = 1;  //接收中断使能标志位  IEN0的第2位(可位寻址)
  EA = 1;      //总中断
}
void UR0_SendByte(unsigned char dat){
   U0DBUF = dat;
   while(UTX0IF == 0);  //等待TX中断标志，即数据发送完成 
   UTX0IF = 0;           //清除TX中断标志，准备下一次发送
}
void UR0_SendString(unsigned char * str){
  while(*str != '\0')       //发送一个字符串
  {
    UR0_SendByte(*str++);    //逐个发送字符串中的字节
  }
}
void init_adc(){
   APCFG  |= 0x10;   //定义p0_4位口子//0001 0000
   
}
void init_wdt(){
   WDCTL = 0X0C; 
}
void  start_adc(){
   ADCCON3 = (0X80 | 0X20 |0X04);
   while((ADCCON1 &0x80) != 0x80);
  //读出数据
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   // adc_value=10000-adc_value;
  // adc_value=adc_value/100;
   sprintf((char *)str,"ain4采样结果是:%d\r\n",adc_value);
   UR0_SendString(str);
}
//主函数
void main(){
  Init_Port();
  Set_Click(32);  //设置32
  Init_uart0(); //串口初始化
  init_adc();
  init_wdt();
  while(1){
    
    if(WDTIF == 1){
     WDTIF = 0;
     start_adc();
    }
    if(adc_value<30){
    P1_0=0;  //开灯
    }else{
     P1_0=1;
    }
    
   
  }
  
}