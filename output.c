
#include "general.h"
#include "output.h"
#include "gpio.h"
#include "tft.h"

void setLED(int led) {
	setGPIOPin(LED_PORT, led);
}


//EOF
