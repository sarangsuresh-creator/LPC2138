#include <lpc213x.h>
void delay();
void ISR() __irq{
IO0PIN ^= (1<<0);
EXTINT = (1<<1);
VICVectAddr = 0;
}
void main(){
PINSEL0 = 1<<7|1<<6;
IO0DIR = ~(1<<3);
IO0DIR = 1<<0;
IO1DIR = 1<<16;
IO0CLR |= 1<<3|1<<0;
IO1CLR = 1<<16;

VICIntEnClr = 1<<15;
EXTINT = 0X02;
EXTMODE = 0x02;
EXTPOLAR = 0x02;
VICIntSelect = 0;                        
VICVectCntl0 = 0x20|15;
VICVectAddr0 = (unsigned int)ISR;
VICIntEnable =1<<15;
IO0PIN =0;
while(1){

 IO1PIN ^= (1<<16);
 delay();
}

}
void delay(){
unsigned int i;
for(i=0;i<1000000;i++);
}