#include "iocc2530.h"
#define D4 P1_1     //�궨��D4��
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}

//�˿ڳ�ʼ������
void Init_Prot(){
  P1SEL &= ~0x02;     //0000 0010 //ȡ0����1Ϊͨ��i/o�˿�
  P1DIR |= 0x02;      //ȡ1��λȡ1�������
  
}
//led��˸����
void Init_Led(){
  D4 =~D4;
  Delay(60000);
}

void main(){
  Init_Prot();
  while(1){
    Init_Led();
  }
}