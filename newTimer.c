#include <stdio.h>
#include "newTimer.h"
#include "timer.h"

#define schrittTeiler 100000000 //Schritte pro Sekunde
#define messfenster 50

static uint32_t  startZeit = 0;
static long long zeitDif = 0;
static int counter = 0;

void zeitSchritt(uint64_t * schritteProSekunde, uint64_t schrittZaehler){
	uint64_t aktuelleZeit = getTimeStamp();
	counter++;
	
	if (counter > messfenster){
		zeitDif = (aktuelleZeit - startZeit +40) / CONVERT2US; // Mikrosekunden
		startZeit = aktuelleZeit;
		zeitDif = zeitDif / counter;
		counter = 0;
	}
	
	*schritteProSekunde = 360000000 / (1200 * zeitDif);
}



int checkRotation(void){
	uint32_t aktuelleZeit = getTimeStamp();
	uint32_t deltaTime = 0;
	deltaTime = aktuelleZeit - startZeit;
	if(deltaTime > 1000000000){
		return 1;		
	}else{
	return 0;
	}
	
}


void gespeicherteZeitAkt(void){
	startZeit = getTimeStamp();
}
	
