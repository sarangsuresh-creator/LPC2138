#include<lpc213x.h>
#include<stdio.h>
#include<stdint.h>
void command (char cmd);
void data(char dat);
void string(const char *s);
int Delay(unsigned int x);
void initialize();
#define RS 17
#define RW 18
#define EN 19
int i=0;
char buffer[4];
int result;
void main(){
PINSEL1 = 0X04000000;

AD0CR = 0X00200304;
IO1DIR = 0xffffffff;
IO0DIR = 0x00000000;
initialize();
while(1){
AD0CR |= (1<<24);
while(!(AD0DR & 0X80000000));
result = AD0DR;
result = (result>>6);
result = (result & 0x000003FF);
sprintf(buffer,"%4d",result);
command(0x80);
string(buffer);
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
