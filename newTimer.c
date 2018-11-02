#include <stdio.h>
#include "newTimer.h"

#include "timer.h"

#define schrittTeiler 1000000 //Schritte pro Sekunde

int startZeit = 0;

int zeitSchritt(void){
	int aktuelleZeit = getTimeStamp();
	int zeitDif = aktuelleZeit - startZeit;
	zeitDif = (zeitDif / CONVERT2US) / schrittTeiler;
	return zeitDif;
}

void gespeicherteZeitAkt(void){
	startZeit = getTimeStamp();
}
	
