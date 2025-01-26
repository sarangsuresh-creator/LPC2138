#include<lpc213x.h>
void string(const char *s);
void data(unsigned char dat); 
char receive();  

void UART0_Init(void);
void main(){
UART0_Init();
data('a');
while(1){

data(receive());

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

char receive(){
while(!(U0LSR & 0x01));
return U0RBR;
}
	   
void UART0_Init(void) {
PINSEL0 |= 0X00000005;
U0LCR = 0x83;
U0DLL = 97;
U0DLM = 0x00;
U0LCR = 0x03;
U0TER = 0x80;
}

