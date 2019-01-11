
#include "gpio.h"
#include "general.h"

#define MIN_GPIO_PIN		0
#define MAX_GPIO_PIN		15

void initHardwareDecoder(){
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; //Clock for GPIO Port F
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //Clock for Syscfg
// Connect EXTI2 with Pin 2 of GPIO F (MASK0x5)
SYSCFG->EXTICR[0] &= ~(0xf << (4*2)); //Remove old selection
SYSCFG->EXTICR[0] |= 0x5 << (4*2); //Select Port F
EXTI->RTSR |= (1<<2); //select rising trigger for INT2
EXTI->FTSR |= (1<<2); //select falling trigger for INT2
EXTI->IMR |= (1<<2); // Unmask Int2
	
// Connect EXTI3 with Pin 3 of GPIO F (MASK0x5)
SYSCFG->EXTICR[0] &= ~(0xf << (4*3)); //Remove old selection
SYSCFG->EXTICR[0] |= 0x5 << (4*3); //Select Port F
EXTI->RTSR |= (1<<3); //select rising trigger for INT3
EXTI->FTSR |= (1<<3); //select falling trigger for INT3
EXTI->IMR |= (1<<3); // Unmask INT3

// INIT Interrupt Controller
NVIC_SetPriorityGrouping(2); // Setup priorities and subpriorities
NVIC_SetPriority(EXTI2_IRQn, 8); // INT2: Set Group Prio = 2, Subprio = 0
NVIC_EnableIRQ(EXTI2_IRQn); // Enable IRQ
NVIC_SetPriority(EXTI3_IRQn, 8); // INT3: Set Group Prio = 2, Subprio = 0
NVIC_EnableIRQ(EXTI3_IRQn); // Enable IRQ
}



int setGPIOPin(GPIO_TypeDef* GPIOx, int pin) {
	/* Check second parameter */
	if ((pin < 0) || (pin > 15)) {
		return INTERNAL_ERR;
	}
	GPIOx->BSRRL = (0x01 << pin);
	return EOK;
}

int resetGPIOPin(GPIO_TypeDef* GPIOx, int pin) {
	/* Check second parameter */
	if ((pin < 0) || (pin > 15)) {
		return INTERNAL_ERR;
	}
	GPIOx->BSRRH = (0x01 << pin);
	return EOK;
}

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin) {
	/* Check second parameter */
	if ((pin < 0) || (pin > 15)) {
		return INTERNAL_ERR;
	}
	return (0x01 << pin) != (GPIOx->IDR & (0x01 << pin)); // '!=' has a higher priority than '&'
}
//EOF
