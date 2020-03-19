/*
 * StepperDriverTimer1.c
 *
 * Created: 19-Mar-20 7:05:43 PM
 *  Author: teamv
 */ 

#include "StepperDriverTimer1.h"


//Variables
uint8_t prescaleT1=1;
unsigned int compareValueT1=5000;

//static functions



void initStepperT1(){
	TCCR1A |=(1<<COM1A0); //toggle OC1A
	TCCR1B |=(1<<WGM12); //mode 4 CTC
	OCR1A = compareValueT1; //compare value
	TIMSK1 |= (1<<OCIE1A); // interrupt on comp A
	DDRB|=(1<<PB5); //enable port 
	PORTB &= ~(1<<PB5); //make sure port is low
	sei();
}

void setVelocityT1(unsigned int vel){
	compareValueT1=vel;
	OCR1A = compareValueT1;
}

void setPrescaleT1(uint8_t scale){
	
}

void startT1(){
	TCCR1B |= prescaleT1;
}

void stopAndClearT1(){
	TCCR1B &= ~0x07;
	PORTB &= ~(1<<PB5); //make sure port is low
}

ISR(TIMER1_COMPA_vect){
	
}


