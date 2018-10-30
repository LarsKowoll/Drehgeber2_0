
#ifndef OUTPUT_H
#define OUTPUT_H

void Init_Output(void);
void setLED(int);
void resetLED(int);
int drehungToLED(int drehung);
int zaehlerstandToLED(int zaehlerstand);
int zaehlerstandToTFT(int zaehlerstand);
int winkelToTFT(void);

#endif	/* OUTPUT_H */
//EOF
