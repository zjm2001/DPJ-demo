#include "ioCC2530.h"
#define SW1 P1_2
#define SW2 P0_1
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}

//端口函数
void Init_Prot(){
  P1SEL &=~0x1B;   //0001 1011
  P1DIR |=0x1B;   //0001 1011
  P1 &=~0x1b;     //把P1端口的0 1 3 4 置零
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
 
//跑马灯函数
void LED_Running(unsigned int j){
  unsigned char i;
  //unsigned stat[4]={0x01,0x02 ,0x08,0x10};    //0000 0001     0000 0010   0000 1000  0001 0000  
  unsigned stat[7]={0x01,0x03 ,0x0b,0x1b,0x0b,0x03,0x01,};    //0000 0001     0000 0011   0000 1011  0001 1011   
   for(i=0;i<j;i++)
    {
      P1=stat[i];
      Delay(60000);
      Delay(60000);
      Delay(60000);
      Delay(60000);
    }
  
}
//设置按键控制
void Scan_Keys()
{
  //按键SW1的扫描处理程序
  if(SW1 == 0)                
  {
    Delay(200);               
    if(SW1 == 0)             
    {
      while(SW1 == 0); 
      P1 =0x1b; 
      Delay(60000);
      Delay(60000);
      P1 &=~0x1b; 
     LED_Running(4);            
    }
  }
  //按键SW2的扫描处理程序
  if(SW2 == 0)
  {
    Delay(200);
    if(SW2 == 0)            
    {
      while(SW2 == 0);  
      P1 =0x1b; 
      Delay(60000);
      Delay(60000);
      P1 &=~0x1b;
      LED_Running(7);        
    }
  }
}

void main(void){

  //端口初始化
  Init_Prot();
  while(1)
  {
    Scan_Keys();
  }

}