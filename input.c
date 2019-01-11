
#include "general.h"
#include "input.h"
#include "gpio.h"


/**
  * @brief 		Liest Werte des Pins an Kanal A und B des Drehgebers aus und gibt den Zustand zurück
	*/
int readDrehgeber(void) {
//	int kanal_a = readGPIOPin(BUTTON_PORT, KANAL_A);
//	int kanal_b = readGPIOPin(BUTTON_PORT, KANAL_B);
//	
//	if (!kanal_a && !kanal_b) {
//		return PHASE_A;
//	}
//	else if (kanal_a && !kanal_b) {
//		return PHASE_B;
//	}
//	else if (kanal_a && kanal_b) {
//		return PHASE_C;
//	}
//	else {
//		return PHASE_D;
//	}
	int input = (GPIOF->IDR & 0x0C) >> 2;	
	
	switch(input){
		case PHASE_A:
			return PHASE_A;
		case PHASE_B:
			return PHASE_B;
		case PHASE_C:
			return PHASE_C;
		case PHASE_D:
			return PHASE_D;
	}
}

int isPressed(int button) {
	return readGPIOPin(BUTTON_PORT, button);
}

int readGPIO(int number, int* value) {
	if ((number > 0) && (number < 15)){
		*value = readGPIOPin(BUTTON_PORT, number);
		return EOK;
	}
	else {
		*value = -1;
		return INTERNAL_ERR;
	}
}




//EOF
