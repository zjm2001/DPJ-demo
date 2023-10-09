#include "ioCC2530.h"
#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4
//���ð�����
#define SW1 P1_2
#define SW2 P0_1

// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//�˿ڳ�ʼ������
void Init_Prot(){
  //LED��ʼ��
  P1SEL &=~0x1b;              //0001 1011 ������
  P1DIR |= 0x1b;              //��һ
  P1   &=~0x1b;                //��P1�˿ڵ�0 1 3 4 ����
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
//ledЧ��
void LED_Check()
{
  P1 |= 0x1B;                 //ͬʱ����4��LED��
  Delay(60000);               //��ʱ
  Delay(60000);
  P1 &= ~0x1B;                //ͬʱϨ��4��LED��
  Delay(60000);               //��ʱ
  Delay(60000);
}

void Scan_Keys()
{
  //����SW1��ɨ�账�����
  if(SW1 == 0)                //ɨ���Ƿ��е͵�ƽ����
  {
    Delay(200);               //��ʱ��ȥ��������
    if(SW1 == 0)              //ȷ�ϰ��������ź�
    {
      while(SW1 == 0);        //�ȴ�����SW1�ɿ�
      D4 = ~D4;               //�л�D4�ƵĿ���״̬
    }
  }
  //����SW2��ɨ�账�����
  if(SW2 == 0)
  {
    Delay(200);
    if(SW2 == 0)            
    {
      while(SW2 == 0);        //�ȴ�����SW2�ɿ�
      D6 = ~D6;               //�л�D6�ƵĿ���״̬
    }
  }
}
void main(void){

  Init_Prot();                //�˿ڳ�ʼ��
  LED_Check();                //�ƹ���
  while(1)
  {
   Scan_Keys();              //ѭ��ɨ�账�����
  }

}