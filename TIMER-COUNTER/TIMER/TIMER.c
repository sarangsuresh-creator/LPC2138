#include <lpc213x.h>

void Timer0_Init(void);
void delay_ms(unsigned int ms);

int main() {
    // Configure GPIO pin for LED
    IO0DIR |= (1 << 10); // Set P0.10 as output (LED)
    IO0CLR = (1 << 10);  // Turn off LED initially

    Timer0_Init(); // Initialize Timer0

    while (1) {
        IO0SET = (1 << 10); // Turn ON LED
        delay_ms(1000);     // Delay 1 second

        IO0CLR = (1 << 10); // Turn OFF LED
        delay_ms(1000);     // Delay 1 second
    }
}

void Timer0_Init(void) {
    T0PR = 14999;        // Prescaler: Generates 1ms delay (PCLK = 15MHz)  
	T0TC = 0;     
}

void delay_ms(unsigned int ms) {
    T0TCR = 0x02;       // Reset Timer
    T0TCR = 0x01;       // Enable Timer
    T0TC = 0;           // Clear Timer Counter

    while (T0TC < ms);  // Wait until the desired delay is reached

    T0TCR = 0x00;       // Disable Timer
}

