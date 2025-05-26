#include <stdint.h>
#include <stdio.h>
#include "PortFSetup.h"
#include "SysTick.h"


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

static uint8_t Colors[] = {OFF, RED, BLUE, GREEN, PURPLE, YELLOW, CYAN, WHITE};
static uint8_t UpperBound = 8;
	
int main(void){
	PortF_Init();
	Systick_Timer_Init();
	
	while(1){
		
		for(uint8_t i = 0;i < UpperBound; i++){
			
			ChangeColor(Colors[i]);
			Delay();
		}
		
	}
		
	

}

