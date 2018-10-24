
#include "general.h"

int switchZustand(int* zustand, int eingabe) {
	switch (*zustand) {
		case PHASE_A:
				switch (eingabe) {
					case INPUT_A: *zustand = PHASE_A;
					              break;
					case INPUT_B: *zustand = PHASE_B;
					              break;
					case INPUT_C: return PHASE_ERROR;
					case INPUT_D: *zustand = PHASE_D;
					              break;
					default: return PHASE_ERROR; // keine gültige Eingabe übergeben
				}
				break;
				
		case PHASE_B:
				switch (eingabe) {
					case INPUT_A: *zustand = PHASE_A;
					              break;
					case INPUT_B: *zustand = PHASE_B;
					              break;
					case INPUT_C: *zustand = PHASE_C;
					              break;
					case INPUT_D: return PHASE_ERROR;
					default: return PHASE_ERROR; // keine gültige Eingabe übergeben
				}
				break;
				
		case PHASE_C:
				switch (eingabe) {
					case INPUT_A: return PHASE_ERROR;
					case INPUT_B: *zustand = PHASE_B;
					              break;
					case INPUT_C: *zustand = PHASE_C;
					              break;
					case INPUT_D: *zustand = PHASE_D;
					              break;
					default: return PHASE_ERROR; // keine gültige Eingabe übergeben
				}
				break;
				
		case PHASE_D:
				switch (eingabe) {
					case INPUT_A: *zustand = PHASE_A;
					              break;
					case INPUT_B: return PHASE_ERROR;
					case INPUT_C: *zustand = PHASE_C;
					              break;
					case INPUT_D: *zustand = PHASE_D;
					              break;
					default: return PHASE_ERROR; // keine gültige Eingabe übergeben
				}
				break;
		
		default: return PHASE_ERROR; // keine gültige Phase übergeben
	}
	return EOK;
}

//EOF
