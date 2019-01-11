#include "general.h"
#include "newTimer.h"
#include "output.h"
#include <stdio.h>
#include "stdint.h"

//Variablen
static int anzahlSchritte = 0;
static int winkelInDezGrad = 0;
static int winkel = 0;



int getDrehrichtung(int* zustand1, int* zustand2, int* drehung) {
	uint64_t  timeStep = 0;
	switch (*zustand1) {
		case PHASE_A:
				switch (*zustand2) {
					case PHASE_A: *drehung = NO_CHANGE;
					              break;
					case PHASE_B: *drehung = FORWARD;
												anzahlSchritte++;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					case PHASE_C: return PHASE_ERROR;
					case PHASE_D: *drehung = BACKWARD;
												anzahlSchritte--;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_B:
				switch (*zustand2) {
					case PHASE_A: *drehung = BACKWARD;
												anzahlSchritte--;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					case PHASE_B: *drehung = NO_CHANGE;
					              break;
					case PHASE_C: *drehung = FORWARD;
												anzahlSchritte++;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					case PHASE_D: return PHASE_ERROR;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_C:
				switch (*zustand2) {
					case PHASE_A: return PHASE_ERROR;
					case PHASE_B: *drehung = BACKWARD;
												anzahlSchritte--;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					case PHASE_C: *drehung = NO_CHANGE;
					              break;
					case PHASE_D: *drehung = FORWARD;
												anzahlSchritte++;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_D:
				switch (*zustand2) {
					case PHASE_A: *drehung = FORWARD;
												anzahlSchritte++;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					case PHASE_B: return PHASE_ERROR;
					case PHASE_C: *drehung = BACKWARD;
												anzahlSchritte--;
												zeitSchritt(&timeStep, anzahlSchritte);
												aktualsiereWerte(timeStep);
					              break;
					case PHASE_D: *drehung = NO_CHANGE;
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
		
		default: return PHASE_ERROR; // ungültige Eingabe für Zustand 1
	}
	return EOK;
}

uint64_t getAnzahlSchritte(){
	return anzahlSchritte;
	}

void setAnzahlSchritte(uint64_t zahl){
	anzahlSchritte = zahl;
}

uint64_t berechneWinkel(void) {
	winkelInDezGrad = anzahlSchritte * 3;
	winkel = winkelInDezGrad/10;
	//winkel = winkel % 360;
	return winkel;
}
		
//EOF
