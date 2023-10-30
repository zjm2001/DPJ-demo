#include <ioCC2530.h>
#include "stdio.h"
//#define ADC_CHANNEL_1 0x04
//#define ADC_CHANNEL_2 0x00
unsigned int adc_value,one=0,two=99;
unsigned char count = 0;
unsigned char str[64];
void Init_Port(){
 P1SEL &= ~0X03;   //����ͨ��i/o��      
 P1DIR |= 0X03;    //��Ϊͨ��i/oʱ������˿�
 P1 |=0x03;       //�ƹعر�״̬
}
void Set_Click(unsigned char clk){
  if(clk==16){
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}
void Init_uart0(){
  PERCFG &= ~0X01;    
  P0SEL |= 0X0C;   
  U0BAUD = 216;
  U0GCR = 11;
  U0UCR |= 0X80;
  U0CSR |=  0XC0;
  UTX0IF = 0;  //�����TX�����жϱ�־
  URX0IF = 0;  //�����TX�����жϱ�־
  URX0IE = 1;  //�����ж�ʹ�ܱ�־λ  IEN0�ĵ�2λ(��λѰַ)
  EA = 1;      //���ж�
}
void UR0_SendByte(unsigned char dat){
   U0DBUF = dat;
   while(UTX0IF == 0);  //�ȴ�TX�жϱ�־�������ݷ������ 
   UTX0IF = 0;           //���TX�жϱ�־��׼����һ�η���
}
void UR0_SendString(unsigned char * str){
  while(*str != '\0')       //����һ���ַ���
  {
    UR0_SendByte(*str++);    //��������ַ����е��ֽ�
  }
}



//-------------------------
//��ʼ����ʱ��
void Init_Timer1(){
  
   T1CC0L = 0Xd4;
   T1CC0H = 0X30;
   T1CCTL0 |=0X04;
     T1IE = 1; //������ʱ��һ�ж�
     EA=1;     //�������ж�
     T1CTL = 0X0E; //128 ��Ƶ��Ϊ��ʱ����ʱ��Դ������ģʽΪģģʽ
}


#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice(){
    count++;
  
  }
int start_adc(unsigned char channel){
   ADCCON3 = (0X80 | 0X20 |channel);
   while((ADCCON1 &0x80) != 0x80);
  //��������
   adc_value = ADCH;
   adc_value= (adc_value << 8) | ADCL;
   adc_value=adc_value >> 2;
   return adc_value;
}

//������
void main(){
  Set_Click(32);  //����32
  Init_uart0(); //���ڳ�ʼ��
  Init_Timer1();
  Init_Port();
  while(1){
    if(count==10){
      APCFG  |= 0x40;   //����p0_7λ����//0100 0000
      one = start_adc(0x07);
    }else if(count==20){
     APCFG  |= 0x01;   //����p0_1λ����
     two= start_adc(0x01);
     
    }else if(count == 30){
     sprintf((char *)str,"���������:%d ��%d\r\n",one,two);
     UR0_SendString(str);
     count=0;
    }
    
    //�ƹ⺯��
    if(two<30){
     P1_0=0;
    }else{
    P1_0=1;
    }
        
  }
  
}