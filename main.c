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



/**
  * @brief  Main program
  * @param  None
  */
int main(void) {
	// Initialisation
	Init_TI_Board(); // Initialisation of Port E and G
	int zustand, alterZustand, drehung, drehungTMP, e;
	int e_phase = 0;
	alterZustand = PHASE_A;
	setLED(LED_D18); // zum Testen
	
	while (1) { // super loop
		
		
		// resetLED(LED_D18); // zum Testen
	
		
		/* Einlesen */
		
		e = readDrehgeber(&zustand); // Zustand einlesen
		
		
		/* Update */
	  
		
		
		
		/* Ausgabe berechnen */
		e_phase = getDrehrichtung(&zustand, &alterZustand, &drehung);
		
		
		
		/* Ausgabe */
		drehungToLED(drehung);
		zaehlerstandToLED(getAnzahlSchritte());
		zaehlerstandToTFT(getAnzahlSchritte());
		resetErrorLED(); // wenn Taste S6 gedrückt wird, geht LED D18 aus
		resetSchrittzaehler();
		if (e_phase == PHASE_ERROR) {
			setLED(LED_D18);
		}
	
		// Aktualisierung Zustand
		alterZustand = zustand;
  }
}

// EOF
