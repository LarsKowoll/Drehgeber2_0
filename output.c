
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

char* intToBinary(int zahl) {
	int rest;
	for (int i = 0; i < 8; i++) {
		rest = zahl % 2;
		binary[i] = '0' + rest;
		zahl = zahl / 2;
	}
	return binary;
	//return EOK;
}

int zaehlerstandToLED(int zaehlerstand) {	
	intToBinary(zaehlerstand);
	int led = 8;
	for (int i = 0; i < 8; i++) {
		if (binary[i] == '0' + 1) {
			setLED(led + i);
		}
		else {
			resetLED(led + i);
		}
	}
	
}

int intToString(int zahl,char* zahlAlsString){
	char tmpString[maxIntegerLaenge];
	int restZahl = zahl;
	
	for(int stelle = 0; (stelle < maxIntegerLaenge) && (restZahl != 0); stelle++){
		tmpString[stelle] = (char) ('0' + (restZahl % 10)); //letzte Ziffer wird gespeichert
		restZahl = (int) (restZahl / 10); //letzte Ziffer wird gelöscht
	}
	zahlAlsString = tmpString;
	return EOK;
}
	

//EOF
