
#include "general.h"

int getDrehrichtung(int* zustand1, int* zustand2, int* drehung) {
	switch (*zustand1) {
		case PHASE_A:
				switch (*zustand2) {
					case PHASE_A: *drehung = NO_CHANGE;
					              break;
					case PHASE_B: *drehung = FORWARD;
					              break;
					case PHASE_C: return PHASE_ERROR;
					case PHASE_D: *drehung = BACKWARD;
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_B:
				switch (*zustand2) {
					case PHASE_A: *drehung = BACKWARD;
					              break;
					case PHASE_B: *drehung = NO_CHANGE;
					              break;
					case PHASE_C: *drehung = FORWARD;
					              break;
					case PHASE_D: return PHASE_ERROR;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_C:
				switch (*zustand2) {
					case PHASE_A: return PHASE_ERROR;
					case PHASE_B: *drehung = BACKWARD;
					              break;
					case PHASE_C: *drehung = NO_CHANGE;
					              break;
					case PHASE_D: *drehung = FORWARD;
					              break;
					default: return PHASE_ERROR; // ungültige Eingabe für Zustand 2
				}
				break;
				
		case PHASE_D:
				switch (*zustand2) {
					case PHASE_A: *drehung = FORWARD;
					              break;
					case PHASE_B: return PHASE_ERROR;
					case PHASE_C: *drehung = BACKWARD;
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

//EOF
