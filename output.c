#include <stdio.h>
#include "general.h"
#include "input.h"
#include "output.h"
#include "gpio.h"
#include "tft.h"
#include "drehgeber.h"

#define maxIntegerLaenge 20
#define INT_TO_STRING_LENGTH 20
#define OUT_STRING_LENGTH 100


char binary[8];
int alterZaehlerstand;

void Init_Output(void) {
	TFT_cls();
	
	TFT_gotoxy(7, 5);
	TFT_puts("Schritte: ");
	
	TFT_gotoxy(7, 6);
	TFT_puts("Winkel: ");
	TFT_gotoxy(28, 6);
	TFT_puts("Grad");
	
	TFT_gotoxy(7, 7);
	TFT_puts("Geschwindigkeit: ");
	TFT_gotoxy(28, 7);
	TFT_puts("Grad/s");
}

void setLED(int led) {
	setGPIOPin(LED_PORT, led);
}

void resetLED(int led) {
	resetGPIOPin(LED_PORT, led);
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
	return EOK;
}

int zaehlerstandToLED(int zaehlerstand) {	
	if (zaehlerstand < 0)
	{
		zaehlerstand = zaehlerstand * -1;
	}
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
	return EOK;
}

int zaehlerstandToTFT(int zaehlerstand) {
	if (1 || zaehlerstand != alterZaehlerstand) {
		TFT_gotoxy(24, 5);
		char outputString[12];
		sprintf(outputString, "%d", zaehlerstand);
		//TFT_cls();
	//	intToString(zaehlerstand, outputString);
		TFT_puts(outputString);
		TFT_puts("      ");
	}
	alterZaehlerstand = zaehlerstand;
	return EOK;
}

int winkelToTFT(void) {
	int winkel = berechneWinkel();
	TFT_gotoxy(24, 6);
	char outputString[12];
	sprintf(outputString, "%d", winkel);
	//intToString(winkel, outputString);
	TFT_puts(outputString);
	TFT_puts("      ");
	return EOK;
}

int winkelGeschwindigkeitToTFT(void) {
	int winkelGeschwindigkeit = berechneWinkelgeschwindigkeit();
	TFT_gotoxy(24, 7);
	char outputString[12];
	sprintf(outputString, "%d", winkelGeschwindigkeit);
	//intToString(winkelGeschwindigkeit, outputString);
	TFT_puts(outputString);
	TFT_puts("      ");
	return EOK;
}



//EOF
