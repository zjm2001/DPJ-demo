#include <ioCC2530.h>
#include "stdio.h"

//延时
void delay_ms(unsigned int milliseconds) {
    unsigned int i, j;
    
    for(i = 0; i < milliseconds; i++) {
        for(j = 0; j < 30000; j++) {
            // 空循环，用于延时
        }
    }
}

////////////////////////////下面是2个串口初始化函数/////////////////////////////////////////

/***********************************************************
函数名称：Uart0_Send_Char 串口0发送字符
函数功能：发送单个字符
入口参数:ch      出口参数：无
***********************************************************/
void Uart0_Send_Char(char ch)//发送单个字符
{
  U0CSR &= ~0x40;			//不能收数
  U0DBUF = ch;
  while(UTX0IF == 0);
  UTX0IF = 0;
  U0CSR |= 0x40;			//允许接收
}

/***********************************************************
函数名称：Uart0_Send_String串口0发送字符串
函数功能：发送字符串
入口参数:*str    出口参数：无
***********************************************************/
void Uart0_Send_String(char *str)//发送字符串
{
  
  while(*str!='\0')
  {
    Uart0_Send_Char(*str);
    //DelayMS(2);
    str++;
  }
}

/****************************************************************
初始化串口0函数					
****************************************************************/
void initUART0(void)
{
  
  CLKCONCMD &= ~0x40;                    //设置系统时钟源为32MHZ晶振
  while(CLKCONSTA & 0x40);               //等待晶振稳定
  CLKCONCMD &= ~0x47;                    //设置系统主时钟频率为32MHZ
  
  PERCFG = 0x00;			//位置1 P0.2 P0.3口
  P0SEL = 0x0c;				//P0.2 P0.3用作串口
  P2DIR &= ~0XC0;                       //P0优先作为UART0    
  
  U0CSR |= 0x80;			//串口设置为UART方式
  U0GCR |= 11;				
  U0BAUD |= 216;		        //波特率设为115200
  UTX0IF = 1;                           //UART0 TX中断标志初始置位1 
  
  U0CSR |= 0X40;		        //允许接收
  IEN0 |= 0x84;				//开总中断，接收中断    
}



/*******************************************************************************
串口1发送一个字节函数			
*******************************************************************************/
void Uart1_Send_Char(char Data)
{
	U1CSR &= ~0x40;      //禁止接收
	U1DBUF = Data;
	while(UTX1IF == 0);
	UTX1IF = 0;
	U1CSR |= 0x40;      //允许接收
}

/*******************************************************************************
串口1发送字符串函数			
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
初始化串口1函数					
****************************************************************/
void initUART1(void)
{ 
	PERCFG = 0x00;		//位置1  P0.4/P0.5口
	P0SEL |= 0x30;		//P0.4,P0.5用作串口（外部设备功能）

	U1CSR |= 0x80;		//设置为UART方式
	U1GCR |= 11;		//BAUD_E        
	U1BAUD |= 216;		//BAUD_M 波特率设为115200
	UTX1IF = 0;	        //UART1 TX中断标志初始置位0
        U1CSR |= 0X40;              //允许接收 
        IEN0 |= 0x88;               // 开总中断，UART1接收中断  
}

////////////////////////////2个串口初始化函数完毕/////////////////////////////////////////
//切换时钟的选择函数
void Set_Click(unsigned int clk){
  if(clk==16){
    //切换到16HMz
    CLKCONCMD |= 0x40;        
    while(!(CLKCONSTA & 0x40));    
    CLKCONCMD |= 0x01;    
  }else if(clk == 32){
    //切换到32HMz
    CLKCONCMD &= ~0x40;        
    while(CLKCONSTA & 0x40);    
    CLKCONCMD &= ~0x07;     
  }
}

//主函数
void main(){
  Set_Click(32);  //设置时钟频率
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