#include <stdio.h>
#include "newTimer.h"

#include "timer.h"

int gespeicherteZeit = 0;

int zeitSchritt(void){
	int aktuelleZeit = getTimeStamp();
	
	int zeitDif = aktuelleZeit - gespeicherteZeit;
	gespeicherteZeit = aktuelleZeit;
	return zeitDif;
}

void gespeicherteZeitAkt(void){
	gespeicherteZeit = getTimeStamp();
}
	
