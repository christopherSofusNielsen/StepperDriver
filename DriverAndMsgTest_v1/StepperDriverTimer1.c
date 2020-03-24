/*
 * StepperDriverTimer1.c
 *
 * Created: 19-Mar-20 7:05:43 PM
 *  Author: teamv
 */ 

#include "StepperDriverTimer1.h"

#define DIR_PIN_PA1 PA1
#define ENABLE_PIN_PA0 PA0
#define INIT_VEL 35000
#define ACCELERATION 50
#define PRESCALE 1

//extern variables
uint8_t running=0;

//Variables
unsigned int activeVel=INIT_VEL;
unsigned int setVel=INIT_VEL; 

long int stepsToGo=0;
unsigned int beginDeeAcc=400;


//static functions



void initStepperT1(){
	TCCR1A |=(1<<COM1A0); //toggle OC1A
	TCCR1B |=(1<<WGM12); //mode 4 CTC
	OCR1A = activeVel; //compare value
	TIMSK1 |= (1<<OCIE1A); // interrupt on comp A
	DDRB|=(1<<PB5); //enable port 
	PORTB &= ~(1<<PB5); //make sure port is low
	
	//direction pin
	DDRA |=(1<<DIR_PIN_PA1);
	PORTA &= ~(1<<DIR_PIN_PA1);
	
	//enable pin
	DDRA |=(1<<ENABLE_PIN_PA0);
	PORTA |= (1<<ENABLE_PIN_PA0);
		
	sei();
}

void setVelocityT1(unsigned int vel){
	setVel=vel;
}

void enableT1(){
	PORTA &= ~(1<<ENABLE_PIN_PA0);
}

void disableT1(){
	PORTA |= (1<<ENABLE_PIN_PA0);
	stepsToGo=0;
	stopAndClearT1();
}

void setDirectionT1(uint8_t dir){
	if (dir){
		PORTA |= (1<<DIR_PIN_PA1);
	}
	else{
		PORTA &= ~(1<<DIR_PIN_PA1);
	}
}


unsigned int calculateBeginDeAcc(long int steps){
	int stde=(INIT_VEL-setVel)/ACCELERATION;
	
	long int halfSteps=steps/2;
	
	if(stde>halfSteps)
		return (unsigned int)halfSteps;
		
	return stde;
}

void startT1(long int steps){
	beginDeeAcc=calculateBeginDeAcc(steps);
	stepsToGo=steps;
	running=1;
	TCCR1B |= PRESCALE;
}

void stopAndClearT1(){
	TCCR1B &= ~0x07;
	PORTB &= ~(1<<PB5); //make sure port is low
	running=0;
	activeVel=INIT_VEL;
	OCR1A =activeVel ;
}

//change for axel

ISR(TIMER1_COMPA_vect){
	
	if (stepsToGo<=0){
		stopAndClearT1();
	}else if(stepsToGo<=beginDeeAcc){
		activeVel+=ACCELERATION;
		OCR1A = activeVel;
	}else if(activeVel>setVel){
		activeVel-=ACCELERATION;
		OCR1A = activeVel;
	}
	stepsToGo--;
}


