#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

const uint16_t LEDS = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
const uint16_t LED[4] = {GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};
static unsigned int i = 0;

void init(void);
void loop(void);
void send(char *str_in);
void delay(uint32_t ms);

int main(void) {
    init();
    loop();
    return 0;
}

void InitUSART(void) {
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Enalbe GPIOA
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    GPIO_InitTypeDef gpio;
    
    //PA9 init
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_AF; // PA9 is Tx pin
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_Init(GPIOC, &gpio);
    
    //PA10 init
    gpio.GPIO_Pin = GPIO_Pin_11;
    gpio.GPIO_Mode = GPIO_Mode_AF; // PA10 is Rx pin
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
    GPIO_Init(GPIOC, &gpio);

    USART_InitTypeDef usart3;
    USART_StructInit(&usart3);
    usart3.USART_BaudRate = 19200;
    USART_Init(USART3, &usart3);
    USART_Cmd(USART3, ENABLE);
}

void InitLED(void) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // Enalbe GPIOD
    
    //LED init
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Pin = LEDS;
    GPIO_Init(GPIOD, &gpio);
    GPIO_SetBits(GPIOD, LEDS);
}

void init(void) {
    InitLED();
    InitUSART();
}

void loop(void) {
    char *str = "Hello World\n";
    while (1) {
        GPIO_ResetBits(GPIOD, LEDS);
        GPIO_SetBits(GPIOD, ~LED[i % 4]);
        ++i;
        delay(500);
        send(str);
        delay(5000);
    }
}

void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}

void send(char *str_in) {
    while(*str_in){
            USART_SendData(USART3, (unsigned int) *str_in++);
            while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
        }
    return ;
}