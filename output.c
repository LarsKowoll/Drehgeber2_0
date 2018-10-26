
#include "general.h"
#include "input.h"
#include "output.h"
#include "gpio.h"
#include "tft.h"

void setLED(int led) {
	setGPIOPin(LED_PORT, led);
}

void resetLED(int led) {
	resetGPIOPin(LED_PORT, led);
}

/** @brief Setzt LED D18 zurück, wenn Taste S6 gedrückt wurde */
int resetErrorLED(void) {
	int value, e;
	int taste = 6;
	e = readGPIO(taste, &value);
	
	if (value == 1) {
		resetLED(LED_D18);
	}
	
	return e;
}

//EOF
