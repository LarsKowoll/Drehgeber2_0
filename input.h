
#ifndef INPUT_H
#define INPUT_H

int readDrehgeber(void);
int isPressed(int button);
int readGPIO(int number, int* value);
extern int anzahlSchritte;


#endif	/* INPUT_H */
//EOF
