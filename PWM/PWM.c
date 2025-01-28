#include <lpc213x.h>
volatile unsigned int i;
void PWM_Init(void);

int main() {
    PWM_Init(); // Initialize PWM
    
    while (1) {
        // Vary the duty cycle
        PWMMR1 = 25; // Set duty cycle to 25% 
        PWMLER = 0x02; // Latch the updated value of PWMMR1
        for ( i = 0; i < 1000000; i++); // Delay
        
        PWMMR1 = 50; // Set duty cycle to 50% 
        PWMLER = 0x02; // Latch the updated value of PWMMR1
        for ( i = 0; i < 1000000; i++); // Delay
        
        PWMMR1 = 75; // Set duty cycle to 75% 
        PWMLER = 0x02; // Latch the updated value of PWMMR1
        for ( i = 0; i < 1000000; i++); // Delay
    }
}

void PWM_Init(void) {
    // Configure P0.0 as PWM1
    PINSEL0 |= 0x00000002; // Set P0.0 as PWM1 output
     IO0DIR =~0;

    // Configure PWM
    PWMPCR = 0x0200;       // Enable PWM1 output
    PWMMCR = 0x02;         // Reset on PWMMR0 match
    PWMMR0 = 100;         // Set PWM period (PCLK = 15 MHz, 100 ms period)
    PWMMR1 = 0;         // Set initial duty cycle to 50% 
    PWMLER = 0x03;         // Latch enable for PWMMR0 and PWMMR1
    PWMPR = 14999;
    PWMTC = 0;
    PWMPC = 0;
    // Enable PWM counter and PWM mode
    PWMTCR = 0x09;         // Counter enable and PWM enable
}

