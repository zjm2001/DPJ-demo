#include <ioCC2530.h>
#include "stdio.h"

//��ʱ
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // ��ѭ����������ʱ
        }
    }
}

////////////////////////////������2�����ڳ�ʼ������/////////////////////////////////////////

/***********************************************************
�������ƣ�Uart0_Send_Char ����0�����ַ�
�������ܣ����͵����ַ�
��ڲ���:ch      ���ڲ�������
***********************************************************/
void Uart0_Send_Char(char ch)//���͵����ַ�
{
  U0CSR &= ~0x40;			//��������
  U0DBUF = ch;
  while(UTX0IF == 0);
  UTX0IF = 0;
  U0CSR |= 0x40;			//�������
}

/***********************************************************
�������ƣ�Uart0_Send_String����0�����ַ���
�������ܣ������ַ���
��ڲ���:*str    ���ڲ�������
***********************************************************/
void Uart0_Send_String(char *str)//�����ַ���
{
  
  while(*str!='\0')
  {
    Uart0_Send_Char(*str);
    //DelayMS(2);
    str++;
  }
}

/****************************************************************
��ʼ������0����					
****************************************************************/
void initUART0(void)
{
  
  CLKCONCMD &= ~0x40;                    //����ϵͳʱ��ԴΪ32MHZ����
  while(CLKCONSTA & 0x40);               //�ȴ������ȶ�
  CLKCONCMD &= ~0x47;                    //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ
  
  PERCFG = 0x00;			//λ��1 P0.2 P0.3��
  P0SEL = 0x0c;				//P0.2 P0.3��������
  P2DIR &= ~0XC0;                       //P0������ΪUART0    
  
  U0CSR |= 0x80;			//��������ΪUART��ʽ
  U0GCR |= 11;				
  U0BAUD |= 216;		        //��������Ϊ115200
  UTX0IF = 1;                           //UART0 TX�жϱ�־��ʼ��λ1 
  
  U0CSR |= 0X40;		        //�������
  IEN0 |= 0x84;				//�����жϣ������ж�    
}



/*******************************************************************************
����1����һ���ֽں���			
*******************************************************************************/
void Uart1_Send_Char(char Data)
{
	U1CSR &= ~0x40;      //��ֹ����
	U1DBUF = Data;
	while(UTX1IF == 0);
	UTX1IF = 0;
	U1CSR |= 0x40;      //�������
}

/*******************************************************************************
����1�����ַ�������			
*******************************************************************************/
void Uart1_Send_String(char *Data)
{
      while(*Data!='\0')
      {
        Uart1_Send_Char(*Data);
        //DelayMS(2);
        Data++;
      }

}

/****************************************************************
��ʼ������1����					
****************************************************************/
void initUART1(void)
{ 
	PERCFG = 0x00;		//λ��1  P0.4/P0.5��
	P0SEL |= 0x30;		//P0.4,P0.5�������ڣ��ⲿ�豸���ܣ�

	U1CSR |= 0x80;		//����ΪUART��ʽ
	U1GCR |= 11;		//BAUD_E        
	U1BAUD |= 216;		//BAUD_M ��������Ϊ115200
	UTX1IF = 0;	        //UART1 TX�жϱ�־��ʼ��λ0
        U1CSR |= 0X40;              //������� 
        IEN0 |= 0x88;               // �����жϣ�UART1�����ж�  
}

////////////////////////////2�����ڳ�ʼ���������/////////////////////////////////////////
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

//������
void main(){
  Set_Click(32);  //����ʱ��Ƶ��
  initUART0();
  initUART1();
  delay_ms(100);
  Uart1_Send_String("AT+CWJAP=\"zjm\",\"zjm555555\"\r\n");
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   Uart1_Send_String("AT+MQTTUSERCFG=0,1,\"NULL\",\"hjjc&k0cluG1vuGb\",\"10f50e685ed1d40fa5f49b83b4b121af1738321450ab4f4a3d353611699425ef\",0,0,\"\"\r\n");
   delay_ms(100);
   Uart1_Send_String("AT+MQTTCLIENTID=0,\"k0cluG1vuGb.hjjc|securemode=2\\,signmethod=hmacsha256\\,timestamp=1697960094743|\"\r\n");
   delay_ms(100);
   Uart1_Send_String("AT+MQTTCONN=0,\"iot-06z00bcwy0zhq6u.mqtt.iothub.aliyuncs.com\",1883,1\r\n");
   delay_ms(100);
   Uart1_Send_String("AT+MQTTSUB=0,\"/sys/k0cluG1vuGb/hjjc/thing/event/property/post_reply\",1\r\n");
  delay_ms(100);
  while(1){
    delay_ms(100);
   Uart1_Send_String("AT+MQTTPUB=0,\"/sys/k0cluG1vuGb/hjjc/thing/event/property/post\",\"{\\\"params\\\":{\\\"temperature\\\":80\\,\\\"PowerSwitch_1\\\":1\\,\\\"Humidity\\\":25}}\",1,0\r\n");
   delay_ms(100);
   delay_ms(100);
   Uart1_Send_String("AT+MQTTPUB=0,\"/sys/k0cluG1vuGb/hjjc/thing/event/property/post\",\"{\\\"params\\\":{\\\"temperature\\\":50\\,\\\"PowerSwitch_1\\\":0\\,\\\"Humidity\\\":65}}\",1,0\r\n");
   delay_ms(100);
  }
 
}