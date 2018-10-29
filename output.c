#include <stdio.h>
#include "general.h"
#include "input.h"
#include "output.h"
#include "gpio.h"
#include "tft.h"

#define maxIntegerLaenge 20

char binary[8];

void setLED(int led) {
	setGPIOPin(LED_PORT, led);
}

void resetLED(int led) {
	resetGPIOPin(LED_PORT, led);
}

/** @brief Setzt LED D18 zur�ck, wenn Taste S6 gedr�ckt wurde */
int resetErrorLED(void) {
	int value, e;
	int taste = 6;
	e = readGPIO(taste, &value);
	
	if (value == 1) {
		resetLED(LED_D18);
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
	char outputString[12];
	sprintf(outputString, "%d", zaehlerstand);
	TFT_puts(outputString);
	return EOK;
}
	

//EOF
