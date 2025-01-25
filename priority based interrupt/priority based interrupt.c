#include <lpc213x.h>
void delay(int count);  // Include LPC213x header file
int i;
// Interrupt Service Routine for Software Interrupt 1 (Higher Priority)
__irq void SoftwareInterrupt1Handler(void) {
  for( i=0;i<4;i++){
    IO0PIN ^= (1 << 0);  // Toggle LED on P0.0
	 delay(1000000);
	}
    // Clear the software interrupt
    VICSoftIntClr = (1 << 14);

    // Signal the end of interrupt to the VIC
    VICVectAddr = 0;
}

// Interrupt Service Routine for Software Interrupt 2 (Lower Priority)
__irq void SoftwareInterrupt2Handler(void) {
    
	 for( i=0;i<6;i++){
    IO0PIN ^= (1 << 1);  // Toggle LED on P0.1
	 delay(1000000);
	}
    // Clear the software interrupt
    VICSoftIntClr = (1 << 15);

    // Signal the end of interrupt to the VIC
    VICVectAddr = 0;
}

// Function to trigger Software Interrupt 1
void triggerSoftwareInterrupt1() {
    VICSoftInt = (1 << 14);  // Trigger Software Interrupt 1
}

// Function to trigger Software Interrupt 2
void triggerSoftwareInterrupt2() {
    VICSoftInt = (1 << 15);  // Trigger Software Interrupt 2
}

// Simple software delay function
void delay(int count) {
    while (count-- > 0) {
        
    }
}

int main(void) {
    // Configure P0.0 and P0.1 as output pins
    IO0DIR |= (1 << 0) | (1 << 1);

    // Configure the interrupt for Software Interrupt 1 (Higher Priority)
    VICVectAddr0 = (unsigned int)SoftwareInterrupt1Handler;  // Set ISR address
    VICVectCntl0 = 0x20 | 14;  // Enable IRQ 14 with priority 0
    VICIntEnable = (1 << 14);  // Enable IRQ 14

    // Configure the interrupt for Software Interrupt 2 (Lower Priority)
    VICVectAddr1 = (unsigned int)SoftwareInterrupt2Handler;  // Set ISR address
    VICVectCntl1 = 0x20 | 15;  // Enable IRQ 15 with priority 1
    VICIntEnable = (1 << 15);  // Enable IRQ 15

    // Main loop
    while (1) {
        triggerSoftwareInterrupt1();  // Trigger the higher-priority interrupt
        triggerSoftwareInterrupt2();  // Trigger the lower-priority interrupt
        delay(1000000);  // Delay for visibility
    }

    return 0;
}

