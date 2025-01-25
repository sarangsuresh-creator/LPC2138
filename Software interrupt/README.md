This code demonstrates the use of a software interrupt on the LPC2138 microcontroller to toggle an LED connected to P0.0.
A software interrupt is used to trigger an interrupt using the software.The software interrupt can be timer,ext interrupt,adc or from any other peripheral.the point is that these interrups can be triggered manually by the software.
Configures a software interrupt (IRQ 14) using the VIC (Vectored Interrupt Controller),(here IRQ 14 is EINT0).
EINT0 is an external interrupt but here we are not using a external button to trigger the interrupt but rather it is done by the software using the command
(VICSoftInt = (1 << 14);)
after the ISR function is executed the interrupt need to be cleared by using (VICSoftIntClr = (1 << 14);)
