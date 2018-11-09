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
#define Y_DIR 2
#define Y_Schritte 5
#define Y_GeschWinkel 7
#define Y_Winkel 6
#define PULSES_PER_ROTATION 1200



char binary[8];
int alterZaehlerstand;

//---------------- VALUE -----------------
static int stagedRotMode = 0;
static int stagedStepCounter = 0;
static int stagedSpeed = 0;
//-------------------------------------------

static int newStepValue = 1 ;
static int newDegValue = 1 ;
//--------------- STRINGS + INDEX ----------

static char schritteString[INT_TO_STRING_LENGTH];
static int schritteIndex = 0;
static int schritteLastIndex = 0;

static char geschwWinkelString[INT_TO_STRING_LENGTH];
static int geschwWinkelIndex = 0;
static int geschwWinkelLastIndex = 0;

static char winkelString[INT_TO_STRING_LENGTH];
static int winkelIndex = 0;
static int winkelLastIndex =0;

typedef enum {step, degTime, deg} Line; 

static Line LineCounter = step;	


/**
*********************************************************************
* @brief Initialisiert Output Module
*
* @param  void
*
* @return void
********************************************************************/

void stageRotationMode(int rotMode){	
	stagedRotMode = rotMode;	
}


/**
*********************************************************************
* @brief Ldt den Stepcounter in den Zwischenspeicher
*
* @param int Anzahl der Schritte
*
* @return void
********************************************************************/
void stageStepCounter(int AnzahlSchritte){
	newStepValue = 1;
	stagedStepCounter = AnzahlSchritte;
}


/**
*********************************************************************
* @brief Ldt die Letzte gemessene Geschwindikeit in den Zwischenspeicher
*
* @param int letzte gemessene Geschwindigkeit
*
* @return void
********************************************************************/
void stageLastSpeed(int steps_per_s){	//Schritte pro S
	newDegValue = 1;
	stagedSpeed = steps_per_s;
}

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
	
	schritteString[1] = '\0';
	
	geschwWinkelString[1] = '\0';
	
	winkelString[1] = '\0';

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


void writeNextBufferValue(void){
	
	switch(LineCounter){		
		case step:		//---------------------- SCHRITT ANZEIGE ------------------------------
			if(schritteString[schritteIndex] == '\0' && (schritteIndex >= schritteLastIndex)){				
				if(newStepValue){
					int steps = getAnzahlSchritte();
					intToString(steps, schritteString);				
					schritteLastIndex = schritteIndex;
					schritteIndex = 0;
					newStepValue = 0;
				}
			}else if(schritteString[schritteIndex] == '\0' && (schritteIndex < schritteLastIndex)){

				// Set LED an
				//setOut(1,1);
				
				TFT_gotoxy(schritteLastIndex+23, Y_Schritte);
				TFT_putc(' ');
				schritteLastIndex--;				
			}else{

				// Set LED an
				//setOut(1,1);				
				
				TFT_gotoxy(schritteIndex+24, Y_Schritte);
				TFT_putc(schritteString[schritteIndex]);
				schritteIndex++;
			}			
			break;
			
		case degTime: 		//-------------- WINKEL GESCHWINDIGKEIT ANZEIGE -----------------------
			if(geschwWinkelString[geschwWinkelIndex] == '\0' && (geschwWinkelIndex >= geschwWinkelLastIndex)){
				if(newDegValue){
				//int winkelGeschwin = stagedSpeed;
				int winkelGeschwin = ((stagedSpeed * 360)) / (PULSES_PER_ROTATION);	//Umrechnung der Schritte pro Sekunde in Grad pro sekunde			<--------- TODO Rechnung checken
				
				// Ergebnis Runden				
				int geschw = winkelGeschwin+((winkelGeschwin % 100)+50);
				int geschwGerundet = (geschw / 100);				
				
				intToString(geschwGerundet, geschwWinkelString);				
				
				geschwWinkelLastIndex = geschwWinkelIndex;
				geschwWinkelIndex = 0;					
				}	
			}else if(geschwWinkelString[geschwWinkelIndex] == '\0' && (geschwWinkelIndex < geschwWinkelLastIndex)){
				
				// Set LED an
				//setOut(1,1);
				
				TFT_gotoxy(geschwWinkelLastIndex+23, Y_GeschWinkel);
				TFT_putc(' ');
				geschwWinkelLastIndex--;				
			}else{		

				// Set LED an
				//setOut(1,1);
				
				TFT_gotoxy(geschwWinkelIndex+24,Y_GeschWinkel );
				TFT_putc(geschwWinkelString[geschwWinkelIndex]);
				geschwWinkelIndex++;
			}					
			break;
			
		case deg:		// --------------   WINKEL ANZEIGE ---------------
			if(winkelString[winkelIndex] == '\0' && (winkelIndex >= winkelLastIndex)){
				if(newDegValue){
				int winkel = berechneWinkel();
	
				
				intToString(winkel, winkelString);				


				winkelLastIndex = winkelIndex;
				winkelIndex = 0;
				newDegValue = 0;
				}
			}else if(winkelString[winkelIndex] == '\0' && (winkelIndex < winkelLastIndex)){
				
				// Set LED an
				//setOut(1,1);
				
				TFT_gotoxy(winkelLastIndex+23, Y_Winkel);
				TFT_putc(' ');
				winkelLastIndex--;				
			}else{	

				// Set LED an
			//	setOut(1,1);
				
				TFT_gotoxy(winkelIndex+24, Y_Winkel);
				TFT_putc(winkelString[winkelIndex]);
				winkelIndex++;
			}				
			break;
			
	
	}


//	setOut(1, 0);	// Kontroll LED wieder ausschalten
	
		//Aktualisieren des Line Counters
	if(LineCounter == deg){
		LineCounter = step;
	}else{
		LineCounter++;
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


void intToString(int input, char* intAsString){
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
