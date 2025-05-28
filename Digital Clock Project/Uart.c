#include "Uart.h"
#include <stdint.h>

#define UART0_MASK 0x0001
#define GPIO_PORTA 0x01

//==================================================================
// UART0 Setup
//==================================================================
void Uart_Init(void){
    SYSCTL_RCGCUART_R  |= UART0_MASK;      // Enable UART0 clock
		while((SYSCTL_RCGCUART_R & UART0_MASK) ==0){}// wait to stablize
	
    SYSCTL_RCGCGPIO_R  |= GPIO_PORTA;      // Enable Port A clock
		while((SYSCTL_RCGCGPIO_R & GPIO_PORTA) ==0){}// wait to stablize
			
    //volatile int delay = 0; delay++; delay++;

    UART0_CTL_R &= ~0x0001UL;                // Disable UART0 during config
    UART0_IBRD_R = 104;                    // 16 MHz / (16 * 9600) = 104.1667
    UART0_FBRD_R = 11;                     // Fraction = 0.1667 * 64 + 0.5 //11
    UART0_LCRH_R = 0x70;                   // 8-bit, 1 stop bit, no parity, FIFO
    UART0_CTL_R = 0x301;                   // Enable UART0, RXE, TXE

    GPIO_PORTA_AFSEL_R |= 0x03;            // Enable alt funct on PA0, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFFUL) | 0x11; // UART0
    GPIO_PORTA_AMSEL_R &= ~0x03UL;           // Disable analog on PA0, PA1
    GPIO_PORTA_DEN_R |= 0x03;              // Enable digital on PA0, PA1
}

//==================================================================
//Read an 8bit value being sent to MCU
//==================================================================
char Uart_Recieve(void){
	
	while((UART0_FR_R & 0x0010) !=0);//wait to receive char
	
	return ((char)(UART0_DR_R &0xFF));

}

//==================================================================
//Transmit a 8bit character
//==================================================================
void Uart_Transmit(char data){
	
	while((UART0_FR_R & 0x0020) !=0);//wait for reg to be full
	UART0_DR_R = data;

}

//==================================================================
//Transmit a string of characters
//==================================================================
void Uart_SendString(const char* str){

	while(*str){
		Uart_Transmit(*str++);
	}

}
