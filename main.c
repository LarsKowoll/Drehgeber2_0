/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	
  * @version V1.0
  * @date    
  * @brief   Main program body
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "TI_Lib.h"
#include "tft.h"

//--- For GPIOs -----------------------------
//Include instead of "stm32f4xx.h" for
//compatibility between Simulation and Board
#include "TI_memory_map.h"
#include "gpio.h"

//--- For Touch Keypad ----------------------
//#include "keypad.h"

//--- For Timer -----------------------------
//#include "timer.h"

#include "general.h"
#include "input.h"
#include "output.h"
#include "drehgeber.h"
#include "newTimer.h"
#include "timer.h"

int zustand = 0;
int alterZustand = 0;

/**
  * @brief  Main program
  * @param  None
  */

int main(void) {
	//------------------------------------------Initialisation------------------------------------------
	Init_TI_Board(); // Initialisation of Port E and G
	Init_Output();
	timerinit();
	
	zustand = readDrehgeber();
	alterZustand = readDrehgeber();
	
	int drehung = NO_CHANGE;
	int taste_S6 = 0;
	int taste_S7 = 0;
	int e_phase = 0;
	
	gespeicherteZeitAkt();
	
	while (1) { // super loop
		
		//-----------------------------------------Einlesen------------------------------------------------
		
		zustand = readDrehgeber(); // Zustand einlesen
		taste_S6 = isPressed(TASTE_S6); // = 1, wenn Taste gedrückt ist
		taste_S7 = isPressed(TASTE_S7); // = 1, wenn Taste gedrückt ist
		
		//--------------------------------------Ausgabe berechnen-------------------------------------------
		
		e_phase = getDrehrichtung(&zustand, &alterZustand, &drehung);
		
		//-------------------------------------------Ausgabe------------------------------------------------
		
		// LEDs
		
		drehungToLED(drehung);
		zaehlerstandToLED(getAnzahlSchritte());	
		
		//TFT
		setLED(LED_D14);
		aktualisiereTFTAusgabe();
		resetLED(LED_D14);
		
		// Tasten
		
		if (e_phase == PHASE_ERROR) { // wenn LED18 leuchtet, ist ein Fehler passiert
			setLED(LED_D18);
		}	
		
		if (taste_S6 == 1) { // wenn Taste S6 gedrückt wird, geht LED D18 aus
			resetLED(LED_D18);
		}
		
		if (taste_S7 == 1) { // wenn Taste S7 gedrückt wird, wird der Zählerstand zurückgesetzt			
			resetLED(LED_D19);
			resetLED(LED_D20);
			setAnzahlSchritte(0);
			Init_Output();
		}
		
	
		//--------------------------------------Zustand aktualisieren---------------------------------------------
		
		alterZustand = zustand;
  }
}

// EOF
