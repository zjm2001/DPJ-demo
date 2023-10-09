#include "ioCC2530.h"
#define SW1 P1_2
#define SW2 P0_1
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}

//�˿ں���
void Init_Prot(){
  P1SEL &=~0x1B;   //0001 1011
  P1DIR |=0x1B;   //0001 1011
  P1 &=~0x1b;     //��P1�˿ڵ�0 1 3 4 ����
  //sw1 ����һ����  P1_2
  P1SEL &= ~0x04;               //�ѵڶ�λ��0����ͨ��i/o��
  P1DIR &= ~0x04;             //�ڶ�λ���ö˿ڷ���Ĵ���Ϊ����0
  P1INP &= ~0x04;            //��������/����
  P2INP &= ~0x40;           //0100 0000 ����λp2 p1  p0����
  //sw2 ����������  P0_1
   P0SEL &= ~0x02;     //��P0_1��Ϊͨ��I/O�˿�
   P0DIR &= ~0x02;     //��P0_1��Ϊ���뷽��
   P0INP &= ~0x02;     //��P0_1����Ϊ������/����
   P2INP &= ~0x20;     //��P0_1����Ϊ������
}
 
//����ƺ���
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
//���ð�������
void Scan_Keys()
{
  //����SW1��ɨ�账�����
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
  //����SW2��ɨ�账�����
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

  //�˿ڳ�ʼ��
  Init_Prot();
  while(1)
  {
    Scan_Keys();
  }

}