#include <stdint.h>
#include <stdio.h>
//#include "tm4c123gh6pm.h"


//==============================
//SYSTICK TIMER REGISTER ADDRESSES
//==============================
#define NVIC_ST_CTRL_R 			(*((volatile unsigned long*) 0xE000E010))
#define NVIC_ST_RELOAD_R		(*((volatile unsigned long*) 0xE000E014))
#define NVIC_ST_CURRENT_R		(*((volatile unsigned long*) 0xE000E018))

//==============================
//PORT F REGISTERS ADDRESSES
//==============================
#define GPIO_PORTF_DIR_R 		(*((volatile unsigned long*) 0x40025400))
#define GPIO_PORTF_AFSEL_R 	(*((volatile unsigned long*) 0x40025420))
#define GPIO_PORTF_DEN_R		(*((volatile unsigned long*) 0x4002551C))
#define GPIO_PORTF_CR_R			(*((volatile unsigned long*) 0x40025524))
#define GPIO_PORTF_AMSEL_R 	(*((volatile unsigned long*) 0x40025528))
#define GPIO_PORTF_PCTL_R		(*((volatile unsigned long*) 0x4002552C))
#define GPIO_PORTF_LOCK_R		(*((volatile unsigned long*) 0x40025520))
#define GPIO_PORTF_DATA_R  	(*((volatile unsigned long*) 0x400253FC))

//==============================
//SYSCTRL_RCGCGPIO REGISTERS ADDRESS
//==============================
#define SYSCTL_RCGCGPIO_R 	(*((volatile unsigned long*) 0x400FE608))
	
//==============================
//PORT F Constants
//==============================
#define PORTF_ENABLE_CLK 0x20UL
#define LED_BIT_MASK  0x0EUL
#define PORTF_PCTL_CODE 0x0FFF0UL
#define PORTF_UNLOCK_CODE 0x4C4F434BUL
//==============================
//LED color
//==============================
#define OFF		 0x00
#define RED 	 0x02
#define BLUE	 0x04
#define GREEN	 0x08
#define PURPLE 0x06 // RED + BLUE
#define YELLOW 0x0A // RED + GREEN
#define CYAN 	 0x0C // GREEN + BLUE
#define WHITE  0x0E // RED + GREEN + BLUE

void PortF_Init(void);
void Systick_Timer_Init(void);
void Delay(void);

int main(void){
	PortF_Init();
	Systick_Timer_Init();
	
	uint8_t Colors[] = {OFF, RED, BLUE, GREEN, PURPLE, YELLOW, CYAN, WHITE};
	uint8_t i;
	
	printf("Hello\n");
	
	while(1){
		
		for(i = 0;i < 8; i++){
			
			GPIO_PORTF_DATA_R = Colors[i];
			Delay();
		}
		
		
		
	}
		
	

}

//====================
// Port F GPIO Setup: F3,F2,F1 | Output
//====================
void PortF_Init(void){
	
	SYSCTL_RCGCGPIO_R |= PORTF_ENABLE_CLK; 
	//Enable PortF Clk
	while((SYSCTL_RCGCGPIO_R & PORTF_ENABLE_CLK) == 0){}
	//wait for PortF clk to startup
		
	GPIO_PORTF_LOCK_R 	|= PORTF_UNLOCK_CODE;	//Unlock PortF
	GPIO_PORTF_CR_R    	|=  LED_BIT_MASK;			//Allow Changes to PortF
	GPIO_PORTF_DIR_R 	 	|=  LED_BIT_MASK;			//Setting pins to output
	GPIO_PORTF_AFSEL_R 	&=~ LED_BIT_MASK;			// Disable Alternat Function Sel
	GPIO_PORTF_DEN_R   	|=  LED_BIT_MASK;			// Enable pins
	GPIO_PORTF_AMSEL_R 	&=~ LED_BIT_MASK;			// Disable Analog mode 
	GPIO_PORTF_PCTL_R		|= PORTF_PCTL_CODE;		// Enable Port Ctrl for our pins
	
}

//==============================
//System Timer: Setting up timer registers
//==============================
void Systick_Timer_Init(void){
	NVIC_ST_CTRL_R = 0 ; 								// Turn off systick timer
	NVIC_ST_RELOAD_R = 16000000 - 1;		// Add reload value of 1 second or 1000ms
	NVIC_ST_CURRENT_R = 0;							// write to clear current value

}
//==============================
//Delay: turns on timer and waits for it to finish
//==============================
void Delay(void){
	NVIC_ST_CTRL_R = 0x05; 											// Enable SRC clock and turn on timer
	
	while((NVIC_ST_CTRL_R & 0x00010000) == 0){} // Wait until counter flag is set
}
