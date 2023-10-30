#include <ioCC2530.h>
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
#define s1   P0_1       //���尴��s1
unsigned char key = 16;
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}

//��ʼ���ƹ�Ͱ�ť
void Init_con(){
   P1SEL &=~0X03;   //����Ϊͨ��io��
   P1DIR |= 0x03; //P10��P11����Ϊ���  0000 0011
   D1=1;
   D2=1;  //���״̬
   
   //s1
   P0SEL &= ~0X02;
   P0DIR &= ~0x02;     //��P0_1��Ϊ���뷽��
   P0INP &= ~0x02;     //��P0_1����Ϊ������/����
   P2INP &= ~0x20;     //��P0_1����Ϊ������
}

//�л�ʱ�ӵ�ѡ����
void Set_Click(unsigned char clk){
  if(clk==16){
    //�л���16HMz
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    //�л���32HMz
    CLKCONCMD &= ~0x40;        //0SCλ��0��ѡ��ϵͳʱ��ԴΪ 32MHz    ����λ��0
    while(CLKCONSTA & 0x40);    //�ȴ��ⲿ�����ȶ�
    CLKCONCMD &= ~0x07;        //���õ�ǰϵͳʱ�ӵ��ٶ�Ϊ 32MHz   ǰ��λ������ 
  }
}
//����ɨ��
//����ɨ�躯��
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
//������
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
    Delay(60000);   //Ч���ǵ�һ�ΰ��°�ťƵ�ʱ�32�����ĸ��� �ٰ��ͱ�16 ���ı���
  }
}