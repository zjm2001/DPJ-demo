#include "ioCC2530.h"
void Delay(unsigned int time){
	while(time--);
}
void main()
{
	P1SEL &= ~0x30;
	P1DIR |= 0x03;
	P1_0 = 0;
	P1_1 = 0;
	
	while(1)
	{
		P1_0 = 1;
		Delay(50000);
		P1_1 = 1;
		Delay(50000);
		P1_0 = 0;
		Delay(50000);
		P1_1 = 0;
		Delay(50000);
	}
}

