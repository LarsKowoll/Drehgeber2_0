
#ifndef DREHGEBER_H
#define DREHGEBER_H
#include <stdint.h>

int getDrehrichtung(int*, int*, int*);
uint64_t getAnzahlSchritte(void);
void setAnzahlSchritte(uint64_t);
uint64_t  berechneWinkel(void);
int berechneWinkelgeschwindigkeit(void);

#endif	/* DREHGEBER_H */
//EOF
