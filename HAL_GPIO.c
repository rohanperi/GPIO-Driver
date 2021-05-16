#include "HAL_GPIO.h"
#include <stdint.h>

// The index in this array is the pin you want to access and the value at that index gives us the 1st bit in that mode register
static uint32_t PINPOS[16] = { 
		(0X00),		//pin0 position starts at 0
		(0x02),
		(0x04),
		(0x06),
		(0x08),
		(0x0A),
		(0x0C),
		(0x0E),
		(0x10),
		(0x12),
		(0x14),
		(0x16),
		(0x18),
		(0x1A),
		(0x1C),
		(0x1E)
};

// This will set the correct registers to allow for a specific pin in a given port to be in a certain mode of choice
void config_pin (GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type) 
{
	switch(mode_type)
	{
		case INPUT:
			port->MODER &= ~(1<<(PINPOS[pinNumber]) | 1<<(PINPOS[pinNumber] + 1));
		break;
		
		case OUTPUT_GEN_PURPOSE:
			port->MODER &= ~( 1<< (PINPOS[pinNumber]+1) );
			port->MODER |=  (1<<PINPOS[pinNumber]);
		break;
		
		case ALT_FUNCTION_MODE:
			port->MODER |= ALT_FUNCTION_MODE<<(PINPOS[pinNumber]);
		break;
		
		case ANALOG_MODE:
			port->MODER |= ANALOG_MODE<<(PINPOS[pinNumber]);
		break;
	}
}

// Set a value to a pin on a port
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state)
{
	if (state)
	{
		port->BSRR = (1<<pinNumber);
	} else 
	{
		port->BSRR = (1<<(pinNumber+16));
	}
}

// Toggle the current value of a pin on a port
void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber ) 
{
	port->ODR ^= (1<<pinNumber);
}

// Given a gpio type struct from the user, enable the clock for the port and configure the specific pin
void gpio_init( GPIO_TYPE gpio_type ) 
{
	if(gpio_type.port == PORTA) 
		GPIO_CLOCK_ENABLE_PORTA;
	
	if(gpio_type.port == PORTB) 
		GPIO_CLOCK_ENABLE_PORTB;
	
	if(gpio_type.port == PORTC) 
		GPIO_CLOCK_ENABLE_PORTC;
	
	if(gpio_type.port == PORTD) 
		GPIO_CLOCK_ENABLE_PORTD;

	config_pin(gpio_type.port, gpio_type.pin, gpio_type.mode_type);
}
