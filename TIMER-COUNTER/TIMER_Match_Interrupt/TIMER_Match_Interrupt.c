#include <lpc213x.h>

void Timer0_Init(void);
void __irq Timer0_ISR(void);

int main() {
    // Configure P0.10 as output for the LED
    IO0DIR |= (1 << 10); // Set P0.10 as output
    IO0CLR = (1 << 10);  // Turn off LED initially

    Timer0_Init(); // Initialize Timer 0

    while (1) {
        // Main loop can perform other tasks
    }
}

void Timer0_Init(void) {
    T0TCR = 0x02;          // Reset Timer
    T0PR = 14999;          // Prescaler for 1 ms tick (PCLK = 15 MHz)
    T0MR0 = 1000;          // Match value for 1 second (1000 ms)
    T0MCR = 0x03;          // Interrupt and reset on match (MR0)

    // Configure Timer 0 interrupt in the VIC
    VICIntSelect &= ~(1 << 4);       // Timer 0 is an IRQ (not FIQ)
    VICVectAddr0 = (unsigned long)Timer0_ISR; // Set ISR address
    VICVectCntl0 = 0x20 | 4;         // Enable interrupt slot 0 for Timer 0
    VICIntEnable = (1 << 4);         // Enable Timer 0 interrupt

    T0TCR = 0x01;          // Enable Timer
}

void __irq Timer0_ISR(void) {
    // Toggle the LED on P0.10
    IO0PIN ^= (1 << 10);

    T0IR = 0x01;           // Clear interrupt flag for MR0
    VICVectAddr = 0x00;    // Acknowledge interrupt
}

