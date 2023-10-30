#include <ioCC2530.h>
#define D1   P1_0	  //定义LED1为P10口控制
#define D2   P1_1	  //定义LED2为P11口控制
#define s1   P0_1       //定义按键s1
unsigned char key = 16;
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

//切换时钟的选择函数
void Set_Click(unsigned char clk){
  if(clk==16){
    //切换到16HMz
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    //切换到32HMz
    CLKCONCMD &= ~0x40;        //0SC位清0，选择系统时钟源为 32MHz    第六位置0
    while(CLKCONSTA & 0x40);    //等待外部晶振稳定
    CLKCONCMD &= ~0x07;        //设置当前系统时钟的速度为 32MHz   前三位都清零 
  }
}
//按键扫描
//按键扫描函数
void Scon_Keys(){
  if(s1 == 0){
  Delay(200);
  if(s1 == 0){
    while(s1== 0);
    if(key == 16){
     Set_Click(32);
     key=32;
    }else if(key == 32){
     Set_Click(16);
     key=16;
    }
  }
  }
}
//主函数
void main(){
  Init_con();
  while(1){
    D1=0;
    Delay(60000);
    Scon_Keys();
    Delay(60000);
    D1=1;
    Delay(60000);
    Scon_Keys();
    Delay(60000);   //效果是第一次按下按钮频率变32灯闪的更快 再按就变16 闪的变慢
  }
}