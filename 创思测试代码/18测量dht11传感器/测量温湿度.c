#include <ioCC2530.h>
#include "DHT11.h"
#include "stdio.h"
unsigned char str[64];

//��ʱ
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // ��ѭ����������ʱ
        }
    }
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
  //ʹ���ж����Ϳ���λ
  UTX0IF = 0;  //�����TX�����жϱ�־
  URX0IF = 0;  //�����TX�����жϱ�־
  URX0IE = 1;  //�����ж�ʹ�ܱ�־λ  IEN0�ĵ�2λ(��λѰַ)
  EA = 1;      //���ж�
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

//������
void main(){
   uchar temp[3]; 
   uchar humidity[3];
  Set_Click(32);  //����32
  Init_uart0(); //���ڳ�ʼ��
  while(1){

   DHT11();//��ȡ��ʪ��
//����ʪ�ȵ�ת�����ַ��� 
   temp[0]=wendu_shi+0x30; 
   temp[1]=wendu_ge+0x30; 
   humidity[0]=shidu_shi+0x30; 
   humidity[1]=shidu_ge+0x30;
    int number,number2;
    int tens = temp[0] - '0';  // ��ʮλ�� ASCII ��ת��Ϊ����
    int ones = temp[1] - '0';  // ����λ�� ASCII ��ת��Ϊ����
    number = (tens * 10) + ones;  // ����õ����յ���ֵ
    int tens2 = humidity[0] - '0';  // ��ʮλ�� ASCII ��ת��Ϊ����
    int ones2 = humidity[1] - '0';  // ����λ�� ASCII ��ת��Ϊ����
    number2 = (tens2 * 10) + ones2;  // ����õ����յ���ֵ
    sprintf((char *)str,"���������:%d  %d \r\n",number,number2);
   UR0_SendString(str);
   delay_ms(100);


  }
  
}