
#ifndef OUTPUT_H
#define OUTPUT_H

void setLED(int);
void resetLED(int);
int resetSchrittzaehler(void);
int resetErrorLED(void);
int drehungToLED(int drehung);
int zaehlerstandToLED(int zaehlerstand);
int zaehlerstandToTFT(int zaehlerstand);

#endif	/* OUTPUT_H */
//EOF
