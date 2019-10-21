#include <inttypes.h>

//RCC setting
#define RCC_APB2ENR (*(volatile unsigned long *) (0x40023800 + 0x44)) //USART1 at APB2
#define RCC_CR (*(volatile unsigned long *) (0x40023800 + 0x00)) //Control Register
#define RCC_PLLCFGR (*(volatile unsigned long *) (0x40023800 + 0x04)) //USART1 PLL Control
#define RCC_CFGR (*(volatile unsigned long *) (0x40023800 + 0x08)) //Clock control
#define RCC_AHB1ENR (*(volatile unsigned long *) (0x40023800 + 0x30)) //GPIOA, GPIOD at AHB1

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
#define GPIOA_AFRH (*(volatile unsigned long *) (0x40020000 + 0x24))

//GPIOD setting
#define GPIOD_MODER (*(volatile unsigned long *) (0x40020C00 + 0x00))
#define GPIOD_OTYPER (*(volatile unsigned long *) (0x40020C00 + 0x04))
#define GPIOD_OSPEEDR (*(volatile unsigned long *) (0x40020C00 + 0x08))
#define GPIOD_BSRR (*(volatile unsigned long *) (0x40020C00 + 0x18))
#define GPIOD_PUPDR (*(volatile unsigned long *) (0x40020C00 + 0x0C))

// GPIO Pin assignment
#define GPIO_Pin_09 ((uint16_t)0x200)   /* Pin 9  selected */ 
#define GPIO_Pin_10 ((uint16_t)0x400)   /* Pin 10  selected */               
#define GPIO_Pin_12 ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13 ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14 ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15 ((uint16_t)0x8000)  /* Pin 15 selected */

asm (".word 0x20001000"); // specify MSP
asm (".word main"); // specify RESET handler

static unsigned int i = 0;
static unsigned int ii = 0;
static const uint16_t LED[4] = {GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15}; // LED pin assignment

void init(void) {
    RCC_APB2ENR = (1 << 4); // Enable USART1
    RCC_AHB1ENR = ((1 << 3) | (1 << 0)); // Enable GPIOA, GPIOD
    RCC_CR |= (1 | (1 << 16)); // Enable HSE(Bit 16)
    RCC_CFGR |= 1 << 1; // Use internal clock fck = 16Mhz

    GPIOD_MODER |= (0x55 << 24); // Pin 12-15 set to General purpose output mode
    GPIOD_OTYPER = 0x00000000; // Pin 12-15 set to push pull mode
    GPIOD_OSPEEDR = 0x00000000; // Pin 12-15 speed set to 2Mhz
    GPIOD_PUPDR = 0x00000000;

    GPIOA_MODER |= (0x2 << 18); // Set PA9 Tx PA10 Rx
    GPIOA_OTYPER = 0x00000000; // PA9 PA 10 set to push pull mode
    GPIOA_OSPEEDR = (0x2 << 18); // Pin 9 speed set to 50Mhz
    GPIOA_AFRH = (0x7 << 4); // Set PA9 alternate function

    USART1_BRR = 0xD04 << 1; // Baud rate 2400 at fck = 8Mhz
    // USART1_BRR = 0x1A08 >> 0; // Baud rate 1200 at fck = 8Mhz
    USART1_CR1 = 0x0000200C; // UE TE RE enable
}

void blink(unsigned int *count_1, unsigned int *count_2, const uint16_t LED_In[]) {
    GPIOD_BSRR = LED_In[(*count_1) % 4];
    for (*count_2 = 0; *count_2 < 150000; ++(*count_2));
        GPIOD_BSRR = (LED_In[(*count_1) % 4] << 16);
    ++(*count_1);
}


int main(void) {
    char *str = "Hello World\n";
    init();

    while(1) {
        blink(&i, &ii, LED);
        while (*str) {
            while (!(USART1_SR & 0x0080));
                USART1_DR = *(str++) & 0xFF; 
        }
    }
    return 0;
}