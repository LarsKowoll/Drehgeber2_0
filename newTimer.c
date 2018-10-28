#include <stdio.h>
#include "newTimer.h"

#include "timer.h"

int gespeicherteZeit = 0;

void zeitSchritt(){
	int aktuelleZeit = getTimeStamp();
	int vergangeneZeit;
	
	int zeitDif = aktuelleZeit - vergangeneZeit;
	vergangeneZeit = aktuelleZeit;
}