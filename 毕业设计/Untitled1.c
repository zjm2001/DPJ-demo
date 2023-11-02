#include <ioCC2530.h>
#include "DHT11.h"
#include "stdio.h"
#include "LCD.h"
int adc_value,one=0,two=99;
int number,number2;
unsigned char str[64];
//延时
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // 空循环，用于延时
        }
    }
}
//-----------------------串口相关-------------------------------------------------------
//切换时钟的选择函数
void Set_Click(unsigned char clk){
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
  //使能中断类型控制位
  UTX0IF = 0;  //清除除TX发送中断标志
  URX0IF = 0;  //清除除TX接收中断标志
  URX0IE = 1;  //接收中断使能标志位  IEN0的第2位(可位寻址)
  EA = 1;      //总中断
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
//--------------------------------------------------------------------------------------
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
   LCD_Init();                      //oled 初始化  
    LCD_CLS();                      //屏全亮 
    LCD_welcome();
   uchar temp[3]; 
   uchar humidity[3];
   Set_Click(32);  //设置32
   Init_uart0(); //串口初始化
  while(1){
   DHT11();//获取温湿度
   temp[0]=wendu_shi+0x30; 
   temp[1]=wendu_ge+0x30; 
   humidity[0]=shidu_shi+0x30; 
   humidity[1]=shidu_ge+0x30;
    int tens = temp[0] - '0';  // 将十位的 ASCII 码转换为整数
    int ones = temp[1] - '0';  // 将个位的 ASCII 码转换为整数
    number = (tens * 10) + ones;  // 计算得到最终的数值
    int tens2 = humidity[0] - '0';  // 将十位的 ASCII 码转换为整数
    int ones2 = humidity[1] - '0';  // 将个位的 ASCII 码转换为整数
    number2 = (tens2 * 10) + ones2;  // 计算得到最终的数值
     APCFG  |= 0x40;   //定义p0_7位口子//0100 0000
     one = start_adc(0x07);
     one=(10000-one)/100;
     delay_ms(30);
     APCFG  |= 0x02;   //定义p0_0位口子
     two= start_adc(0x01);
     two=two/100;
     sprintf((char *)str,"采样结果是:%d  %d  %d %d\r\n",number,number2,one,two);
     UR0_SendString(str);
     LCD_bl(40, 3, number);
     LCD_bl(95, 3, number2);
     LCD_bl(40, 5, two);
     LCD_bl(95, 5, one);
     delay_ms(30);

  }
  
}