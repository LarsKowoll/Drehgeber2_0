#ifndef NEWTIMER_H
#define	NEWTIMER_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif
	
void zeitSchritt(uint64_t *, uint64_t);
void gespeicherteZeitAkt(void);
int checkRotation(void);

#ifdef	__cplusplus
}
#endif

#endif	/* NEWTIMER_H */
