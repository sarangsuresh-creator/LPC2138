 #include<lpc21xx.h>
 int i=0;
 void main(){
 IO0DIR |= 0xffffffff;
 
 while(1){
 IO0SET |= 0xffffffff;
 for(i=0;i<3000000;i++);
 IO0CLR |= 0xffffffff;
 for(i=0;i<3000000;i++);
 }
 }
