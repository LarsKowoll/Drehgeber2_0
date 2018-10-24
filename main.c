/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
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
		
		int zustand, e;
		e = readDrehgeber(&zustand); // Zustand einlesen
		e = switchZustand(&zustand, INPUT_D);
		
  }
}

// EOF
