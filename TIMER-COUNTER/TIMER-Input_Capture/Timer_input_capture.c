#include <lpc213x.h>
#include <stdio.h>
void UART0_Init(void);
void UART0_SendString(const char *str);
void UART0_SendChar(char ch);
void Timer1_Capture_Init(void);
void __irq Timer1_ISR(void);
							 

volatile unsigned int captured_value = 0;

int main() {
    UART0_Init();          // Initialize UART0
   Timer1_Capture_Init(); // Initialize Timer1 for capture

    while (1) {
        // Continuously print the captured timer value
        char buffer[10];
        sprintf(buffer,"%d",captured_value);
        UART0_SendString("Captured Value: ");
        UART0_SendString(buffer);
        UART0_SendString("\r\n");
    }
}

void UART0_Init(void) {
    PINSEL0 |= 0x00000005;  // Configure P0.0 as TXD0 and P0.1 as RXD0
    U0LCR = 0x83;           // Enable DLAB, 8-bit data, no parity, 1 stop bit
    U0DLL = 97;             // Set baud rate to 9600 (PCLK = 15 MHz)
    U0DLM = 0x00;
    U0LCR = 0x03;           // Disable DLAB
    U0TER = 0x80;           // Enable transmission
}

void UART0_SendString(const char *str) {
    while (*str) {
        UART0_SendChar(*str++);
    }
}

void UART0_SendChar(char ch) {
    U0THR = ch;
    while (!(U0LSR & 0x20)); // Wait for THR to be empty
}
 
void Timer1_Capture_Init(void) {
    T1TCR = 0x02;           // Reset Timer1
    T1PR = 14999;           // Prescaler for 1ms tick (PCLK = 15 MHz)
    T1CTCR = 0x00;          // Timer mode
    T1CCR = 0x05;           // Capture on rising edge, interrupt on capture
    PINSEL0 |= 0x00200000;  // Configure P0.17 as CAP1.0
    T1TCR = 0x01;           // Enable Timer1

    // Configure VIC for Timer1 Capture Interrupt
    VICIntSelect &= ~(1 << 5);       // Timer1 is IRQ (not FIQ)
    VICVectAddr1 = (unsigned long)Timer1_ISR; // Set ISR address
    VICVectCntl1 = 0x20 | 5;         // Enable interrupt slot 1 for Timer1
    VICIntEnable = (1 << 5);         // Enable Timer1 interrupt
}

void __irq Timer1_ISR(void) {
    if (T1IR & 0x10) {  // Check if capture interrupt (CR0)
        captured_value = T1CR0; // Store captured value
        T1IR = 0x10;     // Clear capture interrupt flag
    }
    VICVectAddr = 0x00; // Acknowledge interrupt
}


	
