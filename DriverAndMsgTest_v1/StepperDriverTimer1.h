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

#define 

extern void initStepperT1();
extern void setVelocityT1(unsigned int vel);
extern void setPrescaleT1(uint8_t scale);
extern void startT1();
extern void stopAndClearT1();




#endif /* STEPPERDRIVERTIMER1_H_ */