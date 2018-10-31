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



/**
  * @brief  Main program
  * @param  None
  */
int main(void) {
	// Initialisation
	Init_TI_Board(); // Initialisation of Port E and G
	Init_Output();
	
	int zustand = PHASE_A;
	int alterZustand = PHASE_A;
	int drehung = NO_CHANGE;
	int taste_S6 = 0;
	int taste_S7 = 0;
	
	int e = 0;
	int e_phase = 0;
	gespeicherteZeitAkt();
	
	while (1) { // super loop
		
		/* Einlesen */
		
		e = readDrehgeber(&zustand); // Zustand einlesen
		taste_S6 = isPressed(TASTE_S6); // = 1, wenn Taste gedrückt ist
		taste_S7 = isPressed(TASTE_S7); // = 1, wenn Taste gedrückt ist
		
		/* Update */
	  
		
		
		
		/* Ausgabe berechnen */
		e_phase = getDrehrichtung(&zustand, &alterZustand, &drehung);
		
		
		
		/* Ausgabe */
		
		// LEDs
		drehungToLED(drehung);
		zaehlerstandToLED(getAnzahlSchritte());
		if (e_phase == PHASE_ERROR) {
			setLED(LED_D18);
		}
		
		// TFT
		zaehlerstandToTFT(getAnzahlSchritte());
		winkelToTFT();
		winkelGeschwindigkeitToTFT();
		
		// Tasten
		if (taste_S6 == 1) { // wenn Taste S6 gedrückt wird, geht LED D18 aus
			resetLED(LED_D18);
		}
		if (taste_S7 == 1) { // wenn Taste S7 gedrückt wird, wird der Zählerstand zurückgesetzt
			setAnzahlSchritte(0);
		}
		
	
		// Aktualisierung Zustand
		alterZustand = zustand;
  }
}

// EOF
