#include <ioCC2530.h>
#include "DHT11.h"
#include "stdio.h"
#include "LCD.h"
unsigned char str[64];
unsigned int adc_value,one=0,two=99;

//延时
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // 空循环，用于延时
        }
    }
}
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
//ad函数
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
   uchar temp[3]; 
   uchar humidity[3];
    LCD_Init();                      //oled 初始化  
    LCD_CLS();                      //屏全亮 
    LCD_welcome();
  Set_Click(32);  //设置32
  Init_uart0(); //串口初始化
  while(1){

   DHT11();//获取温湿度
//将温湿度的转换成字符串 
   temp[0]=wendu_shi+0x30; 
   temp[1]=wendu_ge+0x30; 
   humidity[0]=shidu_shi+0x30; 
   humidity[1]=shidu_ge+0x30;
    int number,number2;
    int tens = temp[0] - '0';  // 将十位的 ASCII 码转换为整数
    int ones = temp[1] - '0';  // 将个位的 ASCII 码转换为整数
    number = (tens * 10) + ones;  // 计算得到最终的数值
    int tens2 = humidity[0] - '0';  // 将十位的 ASCII 码转换为整数
    int ones2 = humidity[1] - '0';  // 将个位的 ASCII 码转换为整数
    number2 = (tens2 * 10) + ones2;  // 计算得到最终的数值
    //第一个一个ad采集
        APCFG  |= 0x04;   //定义p0_2位口子//0000 0100
        one = start_adc(0x02);
        one=one%4000/10;
       delay_ms(100);
     //第二个采集
       APCFG  |= 0x01;   //定义p0_1位口子
       two= start_adc(0x01);
       two=10000-two;
       two=two/100;
       delay_ms(100);
    //LCD_bl(40, 3, number);
   // LCD_P8x16Str(95, 3, "81");
    //LCD_P8x16Str(40, 5, "30");
    //LCD_P8x16Str(95, 5, "14");
   sprintf((char *)str,"%d  %d  %d  %d \r\n",number,number2,one,two);
   UR0_SendString(str);
   delay_ms(100);


  }
  
}