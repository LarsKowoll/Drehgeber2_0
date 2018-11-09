#include <stdio.h>
#include "newTimer.h"
#include "timer.h"

#define schrittTeiler 100000000 //Schritte pro Sekunde
#define messfenster 50

int startZeit = 0;
int counter = 0;
long long timeSum = 0;

void zeitSchritt(int* schritteProSekunde, int schrittZaehler){
	int aktuelleZeit = getTimeStamp();
	int zeitDif = 0;
	counter++;
	
	zeitDif = aktuelleZeit - startZeit;
	startZeit = aktuelleZeit;
	
	if (counter > messfenster){
		timeSum = 0;
		counter = 1;
	}
	
	timeSum = timeSum + zeitDif;
	int durchSchnitt = timeSum / counter;


	*schritteProSekunde = (schrittTeiler / (durchSchnitt)) * CONVERT2US;
}

void gespeicherteZeitAkt(void){
	startZeit = getTimeStamp();
}
	
