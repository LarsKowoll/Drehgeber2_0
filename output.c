#include <stdio.h>
#include "general.h"
#include "input.h"
#include "output.h"
#include "gpio.h"
#include "tft.h"
#include "drehgeber.h"

#define maxIntegerLaenge 20

char binary[8];
int alterZaehlerstand;

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

int resetSchrittzaehler(void) {
	int value = 0;
	int e = 0;
	int taste = 7;
	e = readGPIO(taste, &value);
	
	if (value == 1) {
		setAnzahlSchritte(0);
	}
	return e;
}

void intToBinary(int zahl) {
	int rest;
	for (int i = 0; i < 8; i++) {
		rest = zahl % 2;
		binary[i] = '0' + rest;
		zahl = zahl / 2;
	}
}

int drehungToLED(int drehung) {
	if (drehung == FORWARD) {
		setLED(LED_D20);
		resetLED(LED_D19);
	}
	else if (drehung == BACKWARD) {
		setLED(LED_D19);
		resetLED(LED_D20);
	}
}

int zaehlerstandToLED(int zaehlerstand) {	
	intToBinary(zaehlerstand);
	int led = 8;
	for (int i = 0; i < 8; i++) {
		if (binary[i] == ('0' + 1)) {
			setLED(led + i);
		}
		else {
			resetLED(led + i);
		}
	}
}

int zaehlerstandToTFT(int zaehlerstand) {
	if (zaehlerstand != alterZaehlerstand) {
		char outputString[12];
		sprintf(outputString, "%d", zaehlerstand);
		TFT_cls();
		TFT_puts(outputString);
	}
	alterZaehlerstand = zaehlerstand;
	return EOK;
}
	

//EOF
