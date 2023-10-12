#include "iocc2530.h"
#define D1 P1_0
#define D2 P1_1
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//===========��ʼ��
void Init_Port(){
 P1SEL &= ~0X03;   //����ͨ��i/o��      
 P1DIR |= 0X03;    //��Ϊͨ��i/oʱ������˿�
 P1 |=0x03;       //�ƹعر�״̬
}
void Init_INTP0(){
  //1.ʹ�ܶ˿�����ⲿ�ж�
  IEN1 |= 0x20;//��P0�˿����ж�  //IEN1��λѰַҲ��ʹ�� P0IE=1
  //2.ʹ�ܾ������ŵ��ⲿ�ж�
  P0IEN |=0X02;
  //3.�����ⲿ�жϵ��źŴ�������
  PICTL |=0X01;
  //�������ж�
  EA =1;
  
}
//============
//p0����Ӧ�жϺ���жϷ�����
#pragma vector = P0INT_VECTOR
__interrupt void Service_INTP0(){
  //�ж��Ǹ����Ŵ������ж�����
  if((P0IFG & 0X02) ==  0X02){
    Delay(200);
    D1 = ~D1;
  }
  P0IFG=0;
  P0IF=0;
}

void main(){
  Init_Port();
  Init_INTP0();
  while(1){
    D2=0;
    Delay(60000);
    D2=1;
    Delay(60000);
 
  }
}