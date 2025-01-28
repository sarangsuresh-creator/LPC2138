#include <lpc213x.h>

void Timer0_Init(void);
//void __irq Timer0_ISR(void);

int main() {
PINSEL0 = 0x00000020;
    // Configure P0.10 as output for the LED
    IO0DIR |= (1 << 10); // Set P0.10 as output
    IO0CLR = (1 << 10);  // Turn off LED initially

    Timer0_Init(); // Initialize Timer 0

    while (1) {
        // Main loop can perform other tasks
		if(T0TC ==1){
		 IO0PIN ^= (1 << 10);
		 T0TC = 0;
    }
}
}

void Timer0_Init(void) {
    T0TCR = 0x02;          // Reset Timer
    T0CTCR =0x01;     //Counter /input-CAP0.0      
	  T0TCR = 0x01;    //enable timer
	} 
