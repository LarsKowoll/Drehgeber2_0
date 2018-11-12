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
#define Y_Schritte 5
#define Y_GeschWinkel 7
#define Y_Winkel 6
#define PULSES_PER_ROTATION 1200



//---------------- VALUE -----------------
// static int stagedStepCounter = 0;
static int stagedSpeed = 0;
//-------------------------------------------

int SchritteHatNeuenWert = 1 ;
int WinkelHatNeuenWert = 1 ;
char binary[8];
int alterZaehlerstand;
//--------------- STRINGS + INDEX ----------

char schritteString[INT_TO_STRING_LENGTH];
int schritteIndex = 0;
int schritteLastIndex = 0;

char geschwWinkelString[INT_TO_STRING_LENGTH];
int geschwWinkelIndex = 0;
int geschwWinkelLastIndex = 0;

char winkelString[INT_TO_STRING_LENGTH];
int winkelIndex = 0;
int winkelLastIndex =0;

typedef enum {schritte, geschwWinkel, winkel} Status; 

static Status currentStatus = schritte;	

static void intToString(int input, char* intAsString);

/**
*********************************************************************
* @brief Initialisiert Output Module
*
* @param  void
*
* @return void
********************************************************************/
void Init_Output(void) {
	TFT_cls();
	TFT_cursor_off();
	
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
	
	schritteString[1] = '\0';
	
	geschwWinkelString[1] = '\0';
	
	winkelString[1] = '\0';

}



void aktualsiereWerte(int schritteProSekunde){
	SchritteHatNeuenWert = 1;
	WinkelHatNeuenWert = 1;
	stagedSpeed = schritteProSekunde;
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

/**
*********************************************************************
* @brief Uebergibt sie an die LED-Leiste
*
* @param  Der aktuelle Zaehlerstand
*
* @return int
********************************************************************/
int zaehlerstandToLED(int zaehlerstand) {	
	if (zaehlerstand < 0)
	{
		zaehlerstand = zaehlerstand * -1; //Falls der Zaehlerstand im negativen Bereich ist
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


void aktualisiereTFTAusgabe(void){
	
	switch(currentStatus){		
		case schritte:		//---------------------- SCHRITT ANZEIGE ------------------------------
			if(schritteString[schritteIndex] == '\0' && (schritteIndex >= schritteLastIndex)){				
				if(SchritteHatNeuenWert){
					int schritte = getAnzahlSchritte();
					intToString(schritte, schritteString);				
					schritteLastIndex = schritteIndex;
					schritteIndex = 0;
					SchritteHatNeuenWert = 0;
				}
			}else if(schritteString[schritteIndex] == '\0' && (schritteIndex < schritteLastIndex)){
				
				TFT_gotoxy(schritteLastIndex+23, Y_Schritte);
				TFT_putc(' ');
				schritteLastIndex--;				
			}else{		
				
				TFT_gotoxy(schritteIndex+24, Y_Schritte);
				TFT_putc(schritteString[schritteIndex]);
				schritteIndex++;
			}			
			break;
			
		case geschwWinkel: 		//-------------- WINKEL GESCHWINDIGKEIT ANZEIGE -----------------------
			if(geschwWinkelString[geschwWinkelIndex] == '\0' && (geschwWinkelIndex >= geschwWinkelLastIndex)){
				if(WinkelHatNeuenWert){	
				
				intToString(stagedSpeed, geschwWinkelString);				
				
				geschwWinkelLastIndex = geschwWinkelIndex;
				geschwWinkelIndex = 0;					
				}	
			}else if(geschwWinkelString[geschwWinkelIndex] == '\0' && (geschwWinkelIndex < geschwWinkelLastIndex)){
				
				TFT_gotoxy(geschwWinkelLastIndex+23, Y_GeschWinkel);
				TFT_putc(' ');
				geschwWinkelLastIndex--;			
				
			}else{		
				
				TFT_gotoxy(geschwWinkelIndex+24,Y_GeschWinkel );
				TFT_putc(geschwWinkelString[geschwWinkelIndex]);
				geschwWinkelIndex++;
			}					
			break;
			
		case winkel:		// --------------   WINKEL ANZEIGE ---------------
			if(winkelString[winkelIndex] == '\0' && (winkelIndex >= winkelLastIndex)){
				if(WinkelHatNeuenWert){
				int winkel = berechneWinkel();
			
				intToString(winkel, winkelString);				

				winkelLastIndex = winkelIndex;
				winkelIndex = 0;
				WinkelHatNeuenWert = 0;
				}
				
			}else if(winkelString[winkelIndex] == '\0' && (winkelIndex < winkelLastIndex)){
		
				TFT_gotoxy(winkelLastIndex+23, Y_Winkel);
				TFT_putc(' ');
				winkelLastIndex--;		
				
			}else{	
				
				TFT_gotoxy(winkelIndex+24, Y_Winkel);
				TFT_putc(winkelString[winkelIndex]);
				winkelIndex++;
			}				
			break;
			
	
	}
		//Aktualisieren des Line Counters
	if(currentStatus == winkel){
		currentStatus = schritte;
	}else{
		currentStatus++;
	}
}


/**
*********************************************************************
* @brief Converts int to String  - String gets Terminated
*
* @param input - The Input Int value - Value has to be smaller than 100 digits
* @param intAsString a array to write the output String to (Size hast to be >100)
*
* @return void
********************************************************************/

static void intToString(int input, char* intAsString){
		int restInput = 0;	
		int negativ = 0;
		
		if(input < 0){		//Wenn negativ -> betrag,  und Flag fuer das Anhngen von -
				restInput = input * - 1;	
				negativ = 1;
		}else{
				restInput = input;
		}	
		
		char tmpString[INT_TO_STRING_LENGTH];
		int stelle =0;
		
		for(stelle = 0;(stelle<INT_TO_STRING_LENGTH) && (restInput != 0);stelle++){
				tmpString[stelle] = (char) ('0' + (restInput % 10)); 	// Letzte Stelle wird Zwischengespeichert
				restInput = (int) (restInput / 10);		//Letzte Stelle wird abgeschnitten
		}
		
		int j = 0;
	
		if(negativ){
				j = 1;
				intAsString[0] = '-';
		}else if(input == 0){		// Wenn zahl == 0 Dann wird eine 0 reingeschrieben
				tmpString[0] = '0';
				stelle++;
		}
	
		for(int i = stelle-1; i >=0;i--){		// Umdrehen der Reihenfolge der ziffern. Groesste stelle nach Links
				intAsString[j++] = tmpString[i];		
		}	
		
		intAsString[j] = '\0';		//Terminieren des StringArrays
}


//EOF
