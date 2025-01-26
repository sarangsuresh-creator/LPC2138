LPC2138 has two uarts.UART0 and UART1,here i am using UART0.UART1 also has same configurations.The only difference between them is that UART1 has additional handshake signals called modem control signals like RTS,CTS,DSR,DTR which can guarantee a more secure communication.

 UART(1):UART communication using VIC(vectored interrupt control) with trigger level 1(RDR will set and clear on receiving a single character)

 UART(2):UART communication using VIC(vectored interrupt control) with trigger level 2(RDR will set and clear on receiving 4 character)

 UART(3):UART communication without using VIC
 
![image Alt](https://github.com/sarangsuresh-creator/LPC2138/blob/9f79457990e224147ff11d22a68383a13ee42af6/UART0/modem%20signals.png)
