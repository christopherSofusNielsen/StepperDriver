/*
 * DriverAndMsgTest_v1.c
 *
 * Created: 19-Mar-20 11:08:21 AM
 * Author : teamv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "UART_debug_v2.h" //debug

//Global variables
unsigned int timer0cnt=0;
unsigned int timer0Steps=400;

//Functions
void initLED();
void ledOn();
void ledOff();

//DriverController
void initTimer0();
void startTimer();
void stopTimer();



int main(void)
{
    //Initialize
	initUART();
	initLED();
	initTimer0();
	sei();
	
	
    while (1) 
    {
		if (newMsgAv())
		{
			char msg[50]={'\0'};
			getMsg(msg);
			
			if((char)msg[0]==(char)'1'){
				ledOn();
				startTimer();
			}else if ((char)msg[0]==(char)'0')
			{
				ledOff();
				stopTimer();
			}else{
				//sendMsg("Error");
				sendMsg(msg);
			}
			
		}
    }
}


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
}


void initLED(){
	DDRB |= (1<<PB7);
	
}

void ledOn(){
	PORTB |= (1<<PB7);
	
}

void ledOff(){
	PORTB &= ~(1<<PB7);
	
}

ISR(TIMER0_COMPA_vect){
	timer0cnt++;
	if(timer0cnt>=timer0Steps){
		stopTimer();
	}
}