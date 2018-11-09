
#ifndef OUTPUT_H
#define OUTPUT_H

void Init_Output(void);
void setLED(int);
void resetLED(int);
int drehungToLED(int drehung);
int zaehlerstandToLED(int zaehlerstand);
//int zaehlerstandToTFT(int zaehlerstand);
//int winkelToTFT(void);
//int winkelGeschwindigkeitToTFT(void);
void intToString(int input, char* intAsString);
void concat(char* string1, char* string2, char* outString, int sizeOutArray);
void writeNextBufferValue(void);
void stageStepCounter(int);
void stageLastSpeed(int steps_per_s);

#endif	/* OUTPUT_H */
//EOF
