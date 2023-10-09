#include "iocc2530.h"
#define D4 P1_1
void Delay(unsigned int t){
 while(t--);
}
void main() {
 P1SEL &=~0x02;
 P1DIR |=~0x02;
 while(1)
 {
 D4= ~D4;
 Delay(6000);
 Delay(6000);
 }
}