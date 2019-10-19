#include <inttypes.h>

#define RCC_AHB1ENR (*(volatile unsigned long *) (0x40023800 + 0x30))
#define GPIOD_MODER (*(volatile unsigned long *) (0x40020C00 + 0x00))
#define GPIOD_OTYPER (*(volatile unsigned long *) (0x40020C00 + 0x04))
#define GPIOD_OSPEEDR (*(volatile unsigned long *) (0x40020C00 + 0x08))
#define GPIOD_BSRR (*(volatile unsigned long *) (0x40020C00 + 0x18))
#define GPIOD_PUPDR (*(volatile unsigned long *) (0x40020C00 + 0x0C))

// GPIO Pin assignment
#define GPIO_Pin_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /* Pin 15 selected */

asm (".word 0x20001000"); // specify MSP
asm (".word main"); // specify RESET handler

int main (void) {
    const uint16_t LED[4] = {GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15}; // LED pin assignment
    
    RCC_AHB1ENR = (1 << 3); // Enable GPIOD
    GPIOD_MODER = 0x55000000; // Pin 12-15 set to General purpose output mode
    GPIOD_OTYPER = 0x00000000; // Pin 12-15 set to open drain mode
    GPIOD_OSPEEDR = 0x00000000; // Pin 12-15 speed set to 2Mhz
    GPIOD_PUPDR = 0x00000000;

    unsigned int i = 0;
    unsigned int ii = 0;

    while (1) {
        GPIOD_BSRR = LED[i % 4];
        for (ii = 0; ii < 1500000; ++ii);
        GPIOD_BSRR = (LED[i % 4] << 16);
        ++i;
    }
    return 0;
}