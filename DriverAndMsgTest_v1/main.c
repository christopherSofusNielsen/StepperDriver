/*
 * DriverAndMsgTest_v1.c
 *
 * Created: 19-Mar-20 11:08:21 AM
 * Author : teamv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>
#include "UART_debug_v2.h" //debug
#include "TypeCaster.h"
#include "StepperDriverTimer1.h"

//Global variables
unsigned int timer0cnt=0;
unsigned int timer0Steps=400;

//Functions
void initLED();
void ledOn();
void ledOff();
void getAction(char command[], char payload[]);





int main(void)
{
    //Initialize
	initUART();
	initStepperT1();
	sei();
	
	
    while (1) 
    {
		if (newMsgAv())
		{
			char command[20]={'\0'};
			char payload[30]={'\0'};
			getAction(command, payload);	
			
			if (strcmp(command, "vel")==0)
			{
				unsigned int val=stringToUInt(payload);
				setVelocityT1(val);
				sendUInt(val);
			}
			else if (strcmp(command, "start")==0)
			{
				startT1();
				sendMsg("started");
			}
			else if (strcmp(command, "stop")==0)
			{
				stopAndClearT1();
				sendMsg("stopped");
			}
			else{
				sendMsg("ERROR");
			}
			
			
		}
    }
}

void getAction(char command[], char payload[]){
	char msg[50]={'\0'};
	getMsg(msg);
	parseMsg(msg, command, payload);
}


/*
void initTimer0(){
	TCCR0A |= (1<<COM0B0)|(1<<WGM01); //Toggle on compare + CTC mode
	OCR0A=150;
	OCR0B=150;
	TIMSK0 |= (1<<OCIE0A);
	
	//Enable pin
	DDRG|=(1<<PG5);
	PORTG &= ~(1<<PG5);
}

void startTimer(){
	TCCR0B |= (1<<CS01)|(1<<CS00);
}

void stopTimer(){
	TCCR0B &= ~0x07; // set CS2, CS1, CS0 low
	PORTG &= ~(1<<PG5);
	timer0cnt=0;
}*/


void initLED(){
	DDRB |= (1<<PB7);
	
}

void ledOn(){
	PORTB |= (1<<PB7);
	
}

void ledOff(){
	PORTB &= ~(1<<PB7);
	
}

/*
ISR(TIMER0_COMPA_vect){
	timer0cnt++;
	if(timer0cnt>=timer0Steps){
		stopTimer();
	}
}*/