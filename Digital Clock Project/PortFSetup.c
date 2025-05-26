#include "PortFSetup.h"
#include <stdint.h>

//========================================================================
//PORT F REGISTERS ADDRESSES
//========================================================================
#define GPIO_PORTF_DIR_R 		(*((volatile unsigned long*) 0x40025400))
#define GPIO_PORTF_AFSEL_R 	(*((volatile unsigned long*) 0x40025420))
#define GPIO_PORTF_DEN_R		(*((volatile unsigned long*) 0x4002551C))
#define GPIO_PORTF_CR_R			(*((volatile unsigned long*) 0x40025524))
#define GPIO_PORTF_AMSEL_R 	(*((volatile unsigned long*) 0x40025528))
#define GPIO_PORTF_PCTL_R		(*((volatile unsigned long*) 0x4002552C))
#define GPIO_PORTF_LOCK_R		(*((volatile unsigned long*) 0x40025520))
#define GPIO_PORTF_DATA_R  	(*((volatile unsigned long*) 0x400253FC))
#define	GPIO_PORTF_PUR_R		(*((volatile unsigned long*) 0x40025510))
//========================================================================
//SYSCTRL_RCGCGPIO REGISTERS ADDRESS
//========================================================================
#define SYSCTL_RCGCGPIO_R 	(*((volatile unsigned long*) 0x400FE608))
	
//========================================================================
//PORT F INTERUPT ADDRESSES
//========================================================================
#define GPIO_PORTF_IS_R 		(*((volatile unsigned long*)	0x40025404))
#define GPIO_PORTF_IBE_R		(*((volatile unsigned long*)	0x40025408))
#define GPIO_PORTF_IEV_R		(*((volatile unsigned long*)	0x4002540C))
#define GPIO_PORTF_IM_R			(*((volatile unsigned long*)	0x40025410))
#define GPIO_PORTF_RIS_R		(*((volatile unsigned long*)	0x40025414))
#define GPIO_PORTF_MIS_R		(*((volatile unsigned long*)	0x40025418))
#define GPIO_PORTF_ICR_R		(*((volatile unsigned long*)	0x4002541C))
#define NVIC_EN0_R					(*((volatile unsigned long*)	0xE000E100))
#define NVIC_PRI7_R					(*((volatile unsigned long*)	0xE000E41C))
//========================================================================
//PORT F Constants
//========================================================================
#define PORTF_ENABLE_CLK 0x20UL
#define LED_BIT_MASK  0x0EUL
#define SWITCH_MASK 0x10UL
#define PORTF_MASK 0x1EUL
#define PORTF_PCTL_CODE 0xFFFF0UL
#define PORTF_UNLOCK_CODE 0x4C4F434BUL
#define PORTF_INTERUPT_PRIORITY_1 0x00200000

//========================================================================
// Port F GPIO Setup: F3,F2,F1 | Output
//========================================================================
void PortF_Init(void){
	
//===============================
//PORTF Clk setup
//===============================
	
	SYSCTL_RCGCGPIO_R |= PORTF_ENABLE_CLK; 
	//Enable PortF Clk
	while((SYSCTL_RCGCGPIO_R & PORTF_ENABLE_CLK) == 0){}
	//wait for PortF clk to startup
		
//===============================
//GPIO Setup
//===============================
	GPIO_PORTF_LOCK_R 	= PORTF_UNLOCK_CODE;	//Unlock PortF
	GPIO_PORTF_CR_R    	|=  LED_BIT_MASK;			//Allow Changes to PortF
	GPIO_PORTF_DIR_R 	 	|=  LED_BIT_MASK;			//Setting pins to output
	GPIO_PORTF_DIR_R		&=~ SWITCH_MASK; 			// Setting F4 Switch to input
	GPIO_PORTF_PUR_R		|=	SWITCH_MASK;		// Enable pull up resistor on Port F4. Press --> 0
	GPIO_PORTF_AFSEL_R 	&=~ PORTF_MASK;			// Disable Alternat Function Sel
	GPIO_PORTF_DEN_R   	|=  PORTF_MASK;			// Enable pins
	GPIO_PORTF_AMSEL_R 	&=~ PORTF_MASK;			// Disable Analog mode 
	GPIO_PORTF_PCTL_R		|= PORTF_PCTL_CODE;		// Enable Port Ctrl for our pins
		
//===============================
//Interupt Setup
//===============================
	GPIO_PORTF_IS_R 	&=~ SWITCH_MASK;		// Clear to 0: Edge detection setting | 1: Level detection setting
	GPIO_PORTF_IBE_R 	&=~ SWITCH_MASK;			// Clear to 0: Not both edges | 1: Detect both edges
	GPIO_PORTF_IEV_R	&=~ SWITCH_MASK;		//Clear to 0: Detect falling edge | 1: Detect rising edge
	GPIO_PORTF_ICR_R	|=  SWITCH_MASK;		// set to 1: Clears that bit
	GPIO_PORTF_IM_R		|= 	SWITCH_MASK;		// Set to 1: Arms interupt
	
//===============================
// Priority Setup
//===============================
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF1FFFFF) | PORTF_INTERUPT_PRIORITY_1;		// Sets interupt priority to 1
	NVIC_EN0_R |= 0x40000000;																									// Enables PORTF interupt scheduler
	
}

//========================================================================
//Sets PORTF LEDs to desired color
//========================================================================
void ChangeColor(uint8_t Color){
	
	GPIO_PORTF_DATA_R = Color;
	
}
