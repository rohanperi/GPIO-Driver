#ifndef _HAL_GPIO
#define _HAL_GPIO

#include "stm32f767xx.h"

#define LOW 0
#define HIGH 1

// PORT names
#define PORTA		GPIOA
#define PORTB		GPIOB
#define PORTC		GPIOC
#define PORTD		GPIOD
#define PORTE		GPIOE
#define PORTF		GPIOF
#define PORTG		GPIOG
#define PORTH		GPIOH

#define INPUT ((uint32_t) 0x00)
#define OUTPUT_GEN_PURPOSE ((uint32_t) 0x01)
#define ALT_FUNCTION_MODE ((uint32_t) 0x02)
#define ANALOG_MODE ((uint32_t) 0x03)

#define GPIO_CLOCK_ENABLE_PORTA		(RCC->AHB1ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTB		(RCC->AHB1ENR |= (1<<1))
#define GPIO_CLOCK_ENABLE_PORTC		(RCC->AHB1ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTD		(RCC->AHB1ENR |= (1<<3))

//Configuration structure
typedef struct 
{
	GPIO_TypeDef *port;
	
	uint32_t pin;
	
	uint32_t mode;
	
	uint32_t mode_type;
	
	uint32_t pull;
	
	uint32_t speed;
	
	uint32_t alt_func;
	
}GPIO_TYPE;

//Functions Prototype 
// **************************************************************************
//													GPIO Configuration
void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type);

// **************************************************************************
//													GPIO User Pin Functions
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state);
void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber);
void gpio_init(GPIO_TYPE gpio_type);
#endif
