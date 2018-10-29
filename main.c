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
	while (1) { // super loop
		
		setLED(LED_D18); // zum Testen
		// resetLED(LED_D18); // zum Testen
		resetErrorLED(); // wenn Taste S6 gedrückt wird, geht LED D18 aus
		
		int zustand1, zustand2, drehung, drehungTMP, e;
		e = readDrehgeber(&zustand1); // Zustand 1 einlesen
		e = readDrehgeber(&zustand2); // Zustand 2 einlesen
	  e = getDrehrichtung(&zustand1, &zustand2, &drehung);
		
		zaehlerstandToLED(getAnzahlSchritte());
		zaehlerstandToTFT(getAnzahlSchritte());
		
		// Ausgabe zum Testen
		TFT_cls();
//		TFT_puts("Zustand 1: ");
//		switch (zustand1) {
//			case PHASE_A: TFT_puts("Phase A"); break;
//			case PHASE_B: TFT_puts("Phase B"); break;
//			case PHASE_C: TFT_puts("Phase C"); break;
//			case PHASE_D: TFT_puts("Phase D"); break;
//		}
//		TFT_puts("; Zustand 2: ");
//		switch (zustand2) {
//			case PHASE_A: TFT_puts("Phase A"); break;
//			case PHASE_B: TFT_puts("Phase B"); break;
//			case PHASE_C: TFT_puts("Phase C"); break;
//			case PHASE_D: TFT_puts("Phase D"); break;
//		}
		if (drehung != drehungTMP){
			TFT_puts("; Drehung: ");
			switch (drehung) {
				case FORWARD: TFT_puts("vorwaerts"); break;
				case BACKWARD: TFT_puts("rueckwaerts"); break;
				case NO_CHANGE: TFT_puts("keine Drehung"); break;
				default: TFT_puts("Fehler");
			}
		}
		drehungTMP = drehung;
  }
}

// EOF
