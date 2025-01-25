
#include <lpc213x.h>  // Include LPC213x header file

__irq void SoftwareInterruptHandler(void) {
    // Toggle LED connected to P0.0
    IO0PIN ^= (1 << 0);

    // Clear the software interrupt
    VICSoftIntClr = (1 << 14);

    // Signal the end of interrupt to the VIC
    VICVectAddr = 0;
}

void triggerSoftwareInterrupt() {
    // Manually trigger software interrupt for IRQ 14
    VICSoftInt = (1 << 14);
}

void delay(int count) {
    while (count-- > 0) {
       
    }
}

int main(void) {
    // Configure P0.0 as output
    IO0DIR |= (1 << 0);

    // Configure the interrupt
    VICVectAddr0 = (unsigned int)SoftwareInterruptHandler;  // Set ISR address
    VICVectCntl0 = 0x20 | 14;  // Enable IRQ 14 (software interrupt)
    VICIntEnable = (1 << 14);  // Enable IRQ 14

    // Main loop
    while (1) {
        triggerSoftwareInterrupt();  // Trigger the software interrupt
        delay(1000000);  // Delay for visible LED toggle
    }

    return 0;
}
