
#include<lpc213x.h>
void string(const char *s);
void data(unsigned char dat); 
//char receive();  // this function needs to be used when we dont use interrupt
volatile char received_char[4];
volatile int i,j=0;
void __irq UART0_InterruptHandler(void);
void UART0_Init(void);
void main(){
UART0_Init();
data('a');
while(1){
 if (i==4) {
 while(j!=4){
           data(received_char[j]);
		   j++;
		   }
		   i=j=0;
            
        }

}
}
void string(const char *s){
while(*s){
data(*s++);
}
}
void data(unsigned char dat){
U0THR = dat;
while(!(U0LSR & 0x20));
}

/*char receive(){
while(!(U0LSR & 0x01));
return U0RBR;
}*/	
	   
void UART0_Init(void) {
PINSEL0 |= 0X00000005;
U0LCR = 0x83;
U0DLL = 97;
U0DLM = 0x00;
U0LCR = 0x03;
U0TER = 0x80;
U0FCR = 0x47;
U0IER = 0x01;
VICIntSelect &= ~(1 << 6);   
VICVectCntl0 = 0x20 | 6;    
VICVectAddr0 = (unsigned long)UART0_InterruptHandler;
VICIntEnable = (1 << 6); 
}
void __irq UART0_InterruptHandler(void) {
    unsigned char interrupt_id = U0IIR;
    
 	  i=0; 
    if ((interrupt_id & 0x04) == 0x04) {
	while(U0LSR & 0x01){
        received_char[i] = U0RBR;
		   i++;
		   
		} 
    }
    
  
    VICVectAddr = 0;
}
