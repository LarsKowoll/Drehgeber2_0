
#ifndef GPIO_H
#define GPIO_H

#include "TI_memory_map.h"

extern int setGPIOPin(GPIO_TypeDef* GPIOx, int pin);

extern int resetGPIOPin(GPIO_TypeDef* GPIOx, int pin);

extern int readGPIOPin(GPIO_TypeDef* GPIOx, int pin);

extern void initHardwareDecoder();

#endif	/* GPIO_H */
//EOF
