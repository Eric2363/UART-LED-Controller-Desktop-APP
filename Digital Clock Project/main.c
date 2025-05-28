#include <stdint.h>
#include <stdio.h>
#include "PortFSetup.h"
#include "SysTick.h"
#include "Uart.h"

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
void GPIOPortF_Handler(void);




int main(void){
	PortF_Init();
	Systick_Timer_Init();
	Uart_Init();
	char Catch = 0;
	
	while(1){
		
		Catch = Uart_Recieve();      // Wait for char from PuTTY
		
		if (Catch == 'R') {
			
      ChangeColor(RED);
			Uart_SendString("Command Recevied: RED\r\n");
      Delay();
			
    }else if (Catch == 'B'){
			
			ChangeColor(BLUE);
			Uart_SendString("Command Recevied: BLUE\r\n");
			Delay();
			
		}else{
		
	
			ChangeColor(GREEN);
			Uart_SendString("Color:	GREEN\r\n");
			Delay();
			ChangeColor(PURPLE);
			Uart_SendString("Color:	PURPLE\r\n");
			Delay();
			ChangeColor(YELLOW);
			Uart_SendString("Color:	YELLOW\r\n");
			Delay();
			ChangeColor(OFF);
			Uart_SendString("Color: OFF\r\n");
			Delay();
			ChangeColor(WHITE);
			Uart_SendString("Color:	WHITE\r\n");
			Delay();
		}

		
	}
		
	

}

void GPIOPortF_Handler(void){
	GPIO_PORTF_ICR_R = 0x10;
	ChangeColor(CYAN);
	Uart_SendString("Interupt: Cyan\r\n");
}

