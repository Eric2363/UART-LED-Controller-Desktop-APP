#include <stdint.h>


#define GPIO_PORTF_ICR_R		(*((volatile unsigned long*)	0x4002541C))
	
void PortF_Init(void);

void ChangeColor(uint8_t Color);
