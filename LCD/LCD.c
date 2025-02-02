#include<lpc213x.h>

void command (char cmd);
void data(char dat);
void string(const char *s);
int Delay(unsigned int x);
void initialize();
#define RS 17
#define RW 18
#define EN 19
int i=0;
void main(){
IO1DIR = 0xffffffff;
initialize();
while(1){
command(0x80);
string("hello");
}
}
int Delay(unsigned int x)
 {
    x=x*12000;
    while(x!=0){
    x--;
    }
    return 0;
 }
void command (char cmd){
IO1CLR |= 0xffffffff;
IO1CLR |= (1<<RS);
IO1CLR |= (1<<RW);
IO1SET |= (1<<EN);
IO1SET |= (cmd & 0Xf0)<<16;

for(i=0;i<20000;i++);
IO1CLR |= (1<<EN);
IO1CLR |= 0x00f00000;
for(i=0;i<20000;i++);
IO1SET |= (1<<EN);
IO1SET |= (cmd & 0X0f)<<20;

for(i=0;i<2000;i++);
IO1CLR |= (1<<EN);
}
void data(char dat){
IO1CLR |= 0xffffffff;
IO1SET |= (1<<RS);
IO1CLR |= (1<<RW);
IO1SET |= (1<<EN);
IO1SET |= (dat & 0xf0)<<16;

for(i=0;i<2000;i++);
IO1CLR |= (1<<EN);
IO1CLR |= 0x00f00000;
for(i=0;i<2000;i++);
IO1SET |= (1<<EN);
IO1SET |= (dat & 0x0f)<<20;

for(i=0;i<2000;i++);
IO1CLR |= (1<<EN);
}
void string(const char *s){
while(*s){
data(*s++);
}
}
void initialize(){

command(0x33);
 Delay(10);
command(0x32);
 Delay(10);
command(0x20);
command(0x28);
command(0X80);
command(0X0c);
command(0x06);
}
