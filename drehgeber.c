
#include "general.h"
#include "newTimer.h"



int anzahlSchritte = 0;
int winkel = 0;
int winkelDif;
int alterWinkel;

int getDrehrichtung(int* zustand1, int* zustand2, int* drehung) {
	switch (*zustand1) {
		case PHASE_A:
				switch (*zustand2) {
					case PHASE_A: *drehung = NO_CHANGE;
					              break;
					case PHASE_B: *drehung = FORWARD;
												anzahlSchritte++;
					              break;
					case PHASE_C: return PHASE_ERROR;
					case PHASE_D: *drehung = BACKWARD;
												anzahlSchritte--;
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_B:
				switch (*zustand2) {
					case PHASE_A: *drehung = BACKWARD;
												anzahlSchritte--;
					              break;
					case PHASE_B: *drehung = NO_CHANGE;
					              break;
					case PHASE_C: *drehung = FORWARD;
												anzahlSchritte++;
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
					              break;
					case PHASE_C: *drehung = NO_CHANGE;
					              break;
					case PHASE_D: *drehung = FORWARD;
												anzahlSchritte++;
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_D:
				switch (*zustand2) {
					case PHASE_A: *drehung = FORWARD;
												anzahlSchritte++;
					              break;
					case PHASE_B: return PHASE_ERROR;
					case PHASE_C: *drehung = BACKWARD;
												anzahlSchritte--;
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

int getAnzahlSchritte(){
	return anzahlSchritte;
	}

void setAnzahlSchritte(int zahl){
	anzahlSchritte = zahl;
}

int berechneWinkel(void) {
	int winkelInDezGrad = anzahlSchritte * 3;
	winkel = winkelInDezGrad/10;
	if (alterWinkel != winkel){
		winkelDif = winkel - alterWinkel;
		alterWinkel = winkel;
	} else {
		winkelDif = 0;
	}
	
	return winkel;
}

int berechneWinkelgeschwindigkeit(void) {	
	int winkelGeschwindigkeit = winkelDif / zeitSchritt();
	return winkelGeschwindigkeit;
}
		
//EOF
