#include <ioCC2530.h>
#include "stdio.h"
//#define ADC_CHANNEL_1 0x04
//#define ADC_CHANNEL_2 0x00
unsigned int adc_value,one=0,two=99;
unsigned char count = 0;
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



//-------------------------
//初始化定时器
void Init_Timer1(){
  
   T1CC0L = 0Xd4;
   T1CC0H = 0X30;
   T1CCTL0 |=0X04;
     T1IE = 1; //开启定时器一中断
     EA=1;     //开启总中断
     T1CTL = 0X0E; //128 分频作为定时器的时钟源，工作模式为模模式
}


#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
    count++;
  
  }
int start_adc(unsigned char channel){
   ADCCON3 = (0X80 | 0X20 |channel);
   while((ADCCON1 &0x80) != 0x80);
  //读出数据
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   return adc_value;
}

//主函数
void main(){
  Set_Click(32);  //设置32
  Init_uart0(); //串口初始化
  Init_Timer1();
  Init_Port();
  while(1){
    if(count==10){
      APCFG  |= 0x40;   //定义p0_7位口子//0100 0000
      one = start_adc(0x07);
    }else if(count==20){
     APCFG  |= 0x01;   //定义p0_1位口子
     two= start_adc(0x01);
     
    }else if(count == 30){
     sprintf((char *)str,"采样结果是:%d 和%d\r\n",one,two);
     UR0_SendString(str);
     count=0;
    }
    
    //灯光函数
    if(two<30){
     P1_0=0;
    }else{
    P1_0=1;
    }
        
  }
  
}