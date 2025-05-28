
//==================================================================
//UART0 and GPIO PORT A Addresses
//==================================================================
#define SYSCTL_RCGCUART_R  (*((volatile unsigned long*) 0x400FE618))
#define SYSCTL_RCGCGPIO_R  (*((volatile unsigned long*) 0x400FE608))
#define UART0_DR_R				 (*((volatile unsigned long*) 0x4000C000))
#define UART0_RSR_R				 (*((volatile unsigned long*) 0x4000C004))
#define UART0_FR_R				 (*((volatile unsigned long*) 0x4000C018))
#define UART0_IBRD_R			 (*((volatile unsigned long*) 0x4000C024))
#define UART0_FBRD_R			 (*((volatile unsigned long*) 0x4000C028))
#define UART0_LCRH_R			 (*((volatile unsigned long*) 0x4000C02C))
#define UART0_CTL_R				 (*((volatile unsigned long*) 0x4000C030))

#define GPIO_PORTA_PCTL_R  (*((volatile unsigned long*) 0x4000452C))
#define GPIO_PORTA_AMSEL_R (*((volatile unsigned long*) 0X40004528))
#define GPIO_PORTA_AFSEL_R (*((volatile unsigned long*) 0x40004420))
#define GPIO_PORTA_DEN_R	 (*((volatile unsigned long*) 0x4000451C))

void Uart_Init(void);

char Uart_Recieve(void);

void Uart_Transmit(char data);

void Uart_SendString(const char* str);
