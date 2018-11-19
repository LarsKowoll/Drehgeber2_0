
#ifndef OUTPUT_H
#define OUTPUT_H

void Init_Output(void);
int setLED(int);
int resetLED(int);
int drehungToLED(int drehung);
int zaehlerstandToLED(int zaehlerstand);
void aktualisiereTFTAusgabe(void);

void aktualsiereWerte(int steps_per_s);

#endif	/* OUTPUT_H */
//EOF
