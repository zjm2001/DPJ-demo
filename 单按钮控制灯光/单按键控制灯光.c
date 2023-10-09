#include "ioCC2530.h"
#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4
//设置按键的
#define SW1 P1_2
#define SW2 P0_1

// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//端口初始化函数
void Init_Prot(){
  //LED初始化
  P1SEL &=~0x1b;              //0001 1011 清零是
  P1DIR |= 0x1b;              //置一
  P1   &=~0x1b;                //把P1端口的0 1 3 4 置零
  //sw1 按键一设置  P1_2
  P1SEL &= ~0x04;               //把第二位置0设置通用i/o口
  P1DIR &= ~0x04;             //第二位设置端口方向寄存器为输入0
  P1INP &= ~0x04;            //配置上拉/下拉
  P2INP &= ~0x40;           //0100 0000 高三位p2 p1  p0上拉
  //sw2 按键二设置  P0_1
   P0SEL &= ~0x02;     //将P0_1设为通用I/O端口
   P0DIR &= ~0x02;     //将P0_1设为输入方向
   P0INP &= ~0x02;     //将P0_1配置为：上拉/下拉
   P2INP &= ~0x20;     //将P0_1配置为：上拉
  
}
//led效果
void LED_Check()
{
  P1 |= 0x1B;                 //同时点亮4个LED灯
  Delay(60000);               //延时
  Delay(60000);
  P1 &= ~0x1B;                //同时熄灭4个LED灯
  Delay(60000);               //延时
  Delay(60000);
}

void Scan_Keys()
{
  //按键SW1的扫描处理程序
  if(SW1 == 0)                //扫描是否有低电平产生
  {
    Delay(200);               //延时，去抖动处理
    if(SW1 == 0)              //确认按键触发信号
    {
      while(SW1 == 0);        //等待按键SW1松开
      D4 = ~D4;               //切换D4灯的开关状态
    }
  }
  //按键SW2的扫描处理程序
  if(SW2 == 0)
  {
    Delay(200);
    if(SW2 == 0)            
    {
      while(SW2 == 0);        //等待按键SW2松开
      D6 = ~D6;               //切换D6灯的开关状态
    }
  }
}
void main(void){

  Init_Prot();                //端口初始化
  LED_Check();                //灯光检测
  while(1)
  {
   Scan_Keys();              //循环扫描处理程序
  }

}