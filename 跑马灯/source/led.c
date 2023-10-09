#include "ioCC2530.h"
#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}

//�˿ں���
void Init_Prot(){
//ѡ��˿ڵĹ���
  P1SEL &=~0x1B;   //0001 1011
//���ö˿ڵķ���
  P1DIR |=0x1B;   //0001 1011
}
 
//����ƺ���
void LED_Running(){
  unsigned char i;
  unsigned stat[4]={0x01,0x02 ,0x08,0x10};    //0000 0001     0000 0010   0000 1000  0001 0000
   for(i=0;i<4;i++)
    {
      P1=stat[i];
      Delay(60000);
      Delay(60000);
    }
   
  
}

void main(void){

  //�˿ڳ�ʼ��
  Init_Prot();
  while(1)
  {
    LED_Running();
  }

}