
#include "general.h"
#include "input.h"
#include "gpio.h"


/**
  * @brief 		Liest Werte des Pins an Kanal A und B des Drehgebers aus und gibt den Zustand zurück
	*/
int readDrehgeber(int* zustand) {
	int kanal_a = readGPIOPin(BUTTON_PORT, KANAL_A);
	int kanal_b = readGPIOPin(BUTTON_PORT, KANAL_B);
	
	if (!kanal_a && !kanal_b) {
		*zustand = PHASE_A;
		return EOK;
	}
	else if (kanal_a && !kanal_b) {
		*zustand = PHASE_B;
		return EOK;
	}
	else if (kanal_a && kanal_b) {
		*zustand = PHASE_C;
		return EOK;
	}
	else if (!kanal_a && kanal_b) {
		*zustand = PHASE_D;
		return EOK;
	}
	else {
		return PHASE_ERROR;
	}
}

int readGPIO(int number, int* value) {
	if ((number < 0) || (number > 15)){
	*value = readGPIOPin(BUTTON_PORT, number);
	return EOK;
	}
}

//EOF
