#include <ioCC2530.h>
#include "stdio.h"
#define D1   P1_0	  //����LED1ΪP10�ڿ���
#define D2   P1_1	  //����LED2ΪP11�ڿ���
#define s1   P0_1       //���尴��s1
unsigned int count = 0;
unsigned char str[64];
// �ӳٺ���
void Delay(unsigned int t)
{
  while(t--);
}
//��ʼ��
void led_con(){
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
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}

  void Init_uart0(){
  PERCFG &= ~0X01;    //��ʼ����ʱ��1ͨ��0������ӳ�䱸��λ��1
  P0SEL |= 0X0C;   // 0000 1100
  U0BAUD = 216;
  U0GCR = 11;
  U0UCR |= 0X80;
  U0CSR |=  0XC0;
}
//���ͺ���
void UR0_SendByte(unsigned char dat){
   U0DBUF = dat;
   while(UTX0IF == 0);  //�ȴ�TX�жϱ�־�������ݷ������ 
   UTX0IF = 0;           //���TX�жϱ�־��׼����һ�η���
}

void UR0_SendString(unsigned char * str)
{
  while(*str != '\0')       //����һ���ַ���
  {
    UR0_SendByte(*str++);    //��������ַ����е��ֽ�
  }
}


//����ɨ�躯��
void Scon_Keys(){
  if(s1==0){
  Delay(200);
  if(s1 == 0){
   while(s1 == 0);
   D1 =~D1;
   count++;
   sprintf(str,"����s1�����Ĵ���Ϊ: %d \r\n",count);
    UR0_SendString(str);
  }
  }
}

//������
void main(){
  Set_Click(32);  //����32
  led_con();  //�ƹ��ʼ��
  Init_uart0(); //���ڳ�ʼ��
  while(1){
  Scon_Keys();
  }
  
}