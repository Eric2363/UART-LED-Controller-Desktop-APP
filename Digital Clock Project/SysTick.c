#include <stdint.h>
#include "SysTick.h"

//==============================
//SYSTICK TIMER REGISTER ADDRESSES
//==============================
#define NVIC_ST_CTRL_R 			(*((volatile unsigned long*) 0xE000E010))
#define NVIC_ST_RELOAD_R		(*((volatile unsigned long*) 0xE000E014))
#define NVIC_ST_CURRENT_R		(*((volatile unsigned long*) 0xE000E018))
	


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
