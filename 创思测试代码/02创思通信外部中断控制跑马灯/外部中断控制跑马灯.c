#include <ioCC2530.h>
#define LED1   P1_0	  //����LED1ΪP10�ڿ���
#define LED2   P1_1	  //����LED2ΪP11�ڿ���
#define LED3   P0_4	  //����LED3ΪP04�ڿ���
unsigned char key=1;  //����һ������һ���Ķ���
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--){
  while(key == 0);
  }
}
//��ʼ���ƹ�Ĵ���
void Init_led(){
   P1DIR |= 0x13; //P10��P11����Ϊ���
   P0DIR |= 0x10; //P04����Ϊ���
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;	    //LED�Ƴ�ʼ��Ϊ��
}
//�ж�ʹ�ܳ�ʼ��-----------------------------
void Init_INTP2(){
  //1.ʹ�ܶ˿�����ⲿ�ж�(p2_0)
   IEN2 |= 0x02;
  //2.ʹ�ܾ������ŵ��ⲿ�ж�
  P2IEN |=0X01;
  //3.�����ⲿ�жϵ��źŴ�������
  PICTL |=0X01;
  //�������ж�
  EA =1;
  
}
#pragma vector = P2INT_VECTOR
__interrupt void selev_init() 
{
  if((P2IFG & 0x01)== 0x01){
    if(key == 1){
     key=0;
    }else{
     key=1;
    }
  }
   P2IFG = 0; 
   P2IF = 0; 
}
//-------------------------------------
void led(){
   LED1 = 0;
    LED2 = 1;
    LED3 = 1;	
  Delay(60000);
  Delay(60000);
    LED1 = 1;
    LED2 = 0;
    LED3 = 1;	
  Delay(60000);
  Delay(60000);
    LED1 = 1;
    LED2 = 1;
    LED3 = 0;	
  Delay(60000);
  Delay(60000);

}
void main(){
  Init_led();
  Init_INTP2();
  while(1){
     led();
  }
}