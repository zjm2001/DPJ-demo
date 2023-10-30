#include <ioCC2530.h>
#include "DHT11.h"
#include "stdio.h"
#include "LCD.h"
unsigned char str[64];
char adc_value;
int  wd=0,sd=0,gz=99,mq=0;
unsigned char count = 0;
//��ʱ
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
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
//ad����
int start_adc(unsigned char channel){
   ADCCON3 = (0X80 | 0X20 |channel);
   while((ADCCON1 &0x80) != 0x80);
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   return adc_value;
}
void main(){
  uchar temp[3]; 
  uchar humidity[3];
  Set_Click(32);
  Init_uart0();
  while(1){
   //��һ���ɼ���ʪ��
     DHT11();//��ȡ��ʪ��
     temp[0]=wendu_shi+0x30; 
     temp[1]=wendu_ge+0x30; 
     humidity[0]=shidu_shi+0x30; 
     humidity[1]=shidu_ge+0x30;
     int tens = temp[0] - '0';  // ��ʮλ�� ASCII ��ת��Ϊ����
     int ones = temp[1] - '0';  // ����λ�� ASCII ��ת��Ϊ����
     wd = (tens * 10) + ones;  // ����õ����յ���ֵ
     int tens2 = humidity[0] - '0';  // ��ʮλ�� ASCII ��ת��Ϊ����
     int ones2 = humidity[1] - '0';  // ����λ�� ASCII ��ת��Ϊ����
     sd = (tens2 * 10) + ones2;  // ����õ����յ���ֵ
       sprintf((char *)str,"���������:%d ��%d\r\n",wd,sd);
     UR0_SendString(str);
     delay_ms(100);
  }
}
