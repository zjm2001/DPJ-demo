#include <ioCC2530.h>
#include "stdio.h"

//��ʱ
void Delay(unsigned int n)
{
	unsigned int i;
	for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
}
//�л�ʱ�ӵ�ѡ����
void Set_Click(unsigned int clk){
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

//������
void main(){
  Set_Click(32);  //����32
  Init_uart0(); //���ڳ�ʼ��
  Delay(60000);
  UR0_SendString("AT+CWMODE=3\r\n");   
  Delay(60000);
  UR0_SendString("AT+CWJAP=\"zjm\",\"zjm555555\"\r\n");   //����wifi
  Delay(60000);
  Delay(60000);
  Delay(60000); 
  Delay(60000);  //�û���Ϣ����
  UR0_SendString("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"); 
  Delay(60000);
  Delay(60000); 
  UR0_SendString("AT+CIPSEND\r\n");  
  Delay(60000);
  Delay(60000); 
  
  

  while(1){
    UR0_SendString("POST /devices/1152311362/datapoints HTTP/1.1/r/n api-key:KX94Vgh9DdXpgEg9w=GHSLCjLJ0=/r/n Host:api.heclouds.com/r/n Connection:close/r/n Content-Length:63/r/n {\"Temp\":14}/r/n");
    Delay(60000);
    Delay(60000);
    Delay(60000); 
   UR0_SendString("POST /devices/1152311362/datapoints HTTP/1.1/r/n api-key:KX94Vgh9DdXpgEg9w=GHSLCjLJ0=/r/n Host:api.heclouds.com/r/n Connection:close/r/n Content-Length:63/r/n {\"Temp\":50}/r/n");
   Delay(60000);
   Delay(60000);
   Delay(60000); 
  }
  
}