#include <stdio.h>
#include "newTimer.h"
#include "timer.h"

#define schrittTeiler 100000000 //Schritte pro Sekunde
#define messfenster 50

static uint64_t startZeit = 0;
static uint64_t zeitDif = 0;
static int counter = 0;

void zeitSchritt(int* schritteProSekunde, int schrittZaehler){
	uint64_t aktuelleZeit = getTimeStamp();
	counter++;
	
	if (counter > messfenster){
		zeitDif = (aktuelleZeit - startZeit) / CONVERT2US; // Mikrosekunden
		startZeit = aktuelleZeit;
		zeitDif = zeitDif / counter;
		counter = 0;
	}
	
	*schritteProSekunde = 360000 / ((1200 * zeitDif) / 1000);
}

void gespeicherteZeitAkt(void){
	startZeit = getTimeStamp();
}
	
