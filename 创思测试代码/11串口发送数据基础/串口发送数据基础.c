#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制

//灯光初始化
void led_con(){
   P1SEL &=~0X03;   //设置为通用io口
   P1DIR |= 0x03; //P10、P11定义为输出  0000 0011
   D1=1;
   D2=1;  //灭灯状态 
}
//看门狗
void Init_WDT(){
  WDCTL = 0X0C;   //0000 1100
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
//===================================
void Init_uart0(){
   //1. io和引脚到备用位置
  PERCFG &= ~0X01;    //初始化定时器1通道0的外设映射备用位置1
  P0SEL |= 0X0C;   // 0000 1100
  // 2.波特率设置
  U0BAUD = 216;
  U0GCR = 11;
  // 3. UART控制
  U0UCR |= 0X80;
  //4. 控制与状态寄存器
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
//===================================
//主函数
void main(){
  Set_Click(32);  //设置32
  led_con();  //灯光初始化
  Init_uart0(); //串口初始化
  Init_WDT();  //看门狗初始化
  while(1){
    if(WDTIF == 1){
     D1=0;
     WDTIF = 0;
     UR0_SendString("发送成功 ddd!!! \r\n");
     D1=1;
     
    }
  }
}