
#ifndef GENERAL_H
#define GENERAL_H

// Definitions for I/O ports
#define BUTTON_PORT		GPIOE
#define KANAL_A				0				// Kanal A des Drehgebers
#define KANAL_B				1				// Kanal B des Drehgebers

#define LED_PORT			GPIOG
#define LED_D18				5
#define LED_D19				6
#define LED_D20				7
#define LED_D21				8
#define LED_D22				9
#define LED_D23				10
#define LED_D24				11
#define LED_D25				12
#define LED_D26				13
#define LED_D27				14
#define LED_D28				15


#define PHASE_A		0x00	// A = 0, B = 0
#define PHASE_B		0x02	// A = 1, B = 0
#define PHASE_C		0x03	// A = 1, B = 1
#define PHASE_D		0x01	// A = 0, B = 1

#define FORWARD		1
#define BACKWARD	2
#define NO_CHANGE	3


// Values for error handling

#define INTERNAL_ERR	-1
#define PHASE_ERROR		-2
#define EOK						1

#endif	/* GENERAL_H */
//EOF
