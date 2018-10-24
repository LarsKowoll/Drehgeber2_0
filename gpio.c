
#include "gpio.h"
#include "general.h"

#define MIN_GPIO_PIN		0
#define MAX_GPIO_PIN		15

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
