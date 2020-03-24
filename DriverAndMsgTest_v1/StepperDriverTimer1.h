/*
 * StepperDriverTimer1.h
 *
 * Created: 19-Mar-20 7:05:59 PM
 *  Author: teamv
 */ 


#ifndef STEPPERDRIVERTIMER1_H_
#define STEPPERDRIVERTIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>


extern void initStepperT1();
extern void setVelocityT1(unsigned int vel);
extern void startT1(long int steps);
extern void stopAndClearT1();
extern void setDirectionT1(uint8_t dir);
extern void enableT1();
extern void disableT1();

extern uint8_t running;




#endif /* STEPPERDRIVERTIMER1_H_ */