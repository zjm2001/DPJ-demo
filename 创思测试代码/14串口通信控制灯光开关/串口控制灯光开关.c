#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
unsigned char dat;
unsigned char key=0;
//初始化灯光和按键的函数
void Init_con(){
   // P1SEL默认都是通用io
    P1SEL &=~0X03;
    P1DIR |= 0x03; //P10、P11定义为输出  0000 0011
    D1 = 1;
    D2 = 1;  
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
//接收中断函数
#pragma vector = URX0_VECTOR
__interrupt void se_URX0() {
  dat =U0DBUF;
  key=1;
 
}
//led 显示函数
void led_run(){
  switch(dat){
  case 0XA1:
    D1=0;
    UR0_SendString("D1开");
    break;
  case 0XA2:
    D1=1;
    UR0_SendString("D1关");
    break;
  case 0XB1:
    D2=0;
    UR0_SendString("D2开");
    break;
  case 0XB2:
    D2=1;
    UR0_SendString("D2关");
    break;
  default:
     UR0_SendString("错误");
     break;
  }
}
//主函数
void main(){
  Set_Click(32);  //设置32
  Init_con();
  Init_uart0(); //串口初始化
  while(1){
    if(key==1){
      key=0;
      led_run();
    }
  }
  
}