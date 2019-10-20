//RCC setting
#define RCC_APB2ENR (*(volatile unsigned long *) (0x40023800 + 0x44)) //USART1 at APB2
#define RCC_AHB1ENR (*(volatile unsigned long *) (0x40023800 + 0x30)) //GPIOA at AHB1

//USART1 setting
#define USART1_SR (*(volatile unsigned long *) (0x40011000 + 0x00))  //Pick USART1 
#define USART1_DR (*(volatile unsigned long *) (0x40011000 + 0x04))
#define USART1_BRR (*(volatile unsigned long *) (0x40011000 + 0x08))
#define USART1_CR1 (*(volatile unsigned long *) (0x40011000 + 0x0C))
#define USART1_CR2 (*(volatile unsigned long *) (0x40011000 + 0x10))
#define USART1_CR3 (*(volatile unsigned long *) (0x40011000 + 0x14))
#define USART1_GTPR (*(volatile unsigned long *) (0x40011000 + 0x18))

//GPIOA setting
#define GPIOA_MODER (*(volatile unsigned long *) (0x40020000 + 0x00))
#define GPIOA_OTYPER (*(volatile unsigned long *) (0x40020000 + 0x04))
#define GPIOA_OSPEEDR (*(volatile unsigned long *) (0x40020000 + 0x08))
#define GPIOA_BSRR (*(volatile unsigned long *) (0x40020000 + 0x18))
#define GPIOA_PUPDR (*(volatile unsigned long *) (0x40020000 + 0x0C))

