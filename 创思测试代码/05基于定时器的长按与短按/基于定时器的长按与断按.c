#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
#define s1   P0_1       //定义按键s1
unsigned int count = 0;  
unsigned char key = 0;
// 延迟函数
void Delay(unsigned int t)
{
  while(t--);
}
//初始化灯光和按钮
void Init_con(){
   P1SEL &=~0X03;   //设置为通用io口
   P1DIR |= 0x03; //P10、P11定义为输出  0000 0011
   D1=1;
   D2=1;  //灭灯状态
   
   //s1
   P0SEL &= ~0X02;
   P0DIR &= ~0x02;     //将P0_1设为输入方向
   P0INP &= ~0x02;     //将P0_1配置为：上拉/下拉
   P2INP &= ~0x20;     //将P0_1配置为：上拉
}
//初始化定时器

void Init_Timers(){
   T1CC0L = 0Xd4;  //第八位
   T1CC0H = 0X30;  //高八位
   T1CCTL0 |= 0x04;   //开启通道 0 的比较模式
   T1IE = 1;  //开启定时器一中断使能
   EA= 1;  //总中断开关
   T1CTL = 0X0E; //128 分频作为定时器的时钟源，工作模式为模模式

}

#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
  if(key == 1){
      count++;
  }
}
//按键扫描函数
void Scon_Keys(){
  if(s1 == 0){
   Delay(200);
   if(s1 == 0){
    count=0; //进来先清除计数
    key=1;
    while(s1 == 0);
    key=0;
    if(count > 5){
     //表示长按
      D1= ~D1;
    }else{
     //表示短按
       D2= ~D2;
    }
   }
  }
}
//主函数
void main(){
  Init_con();
 Init_Timers();
  while(1){
   Scon_Keys();
  }
}