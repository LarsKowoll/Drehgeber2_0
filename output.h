
#ifndef OUTPUT_H
#define OUTPUT_H

void setLED(int);
void resetLED(int);
int resetErrorLED(void);
char* intToBinary(int zahl);
int zaehlerstandToLED(void);
int intToString(int zahl,char* zahlAlsString);

#endif	/* OUTPUT_H */
//EOF
