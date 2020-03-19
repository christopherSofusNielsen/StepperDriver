/*
 * UART_debug_v2.c
 *
 * Created: 12-Jun-19 12:11:09 PM
 *  Author: teamv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "UART_debug_v2.h"



char rxBuffer[RX_BUFFER_SIZE];
volatile uint8_t rxReadPos=0;
volatile uint8_t rxWritePos=0;
volatile uint8_t newMessage=0;

void initUART(){
	//set baudrate
	UBRR0H=(BRC>>8);
	UBRR0L=BRC;
	
	//full duplex
	UCSR0A=(1<<U2X0);
	
	//set data bit length
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00); //8 bit
	
	//enable tx and rx
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
	
	//enable rx interrupt
	UCSR0B|=(1<<RXCIE0);
	sei();
}

//the only function to write to the UART
void writeBytes(char data[], int bytesToWrite){

	//write each char in data to UDR0, when empty
	for (uint8_t i=0; i<bytesToWrite; i++)
	{
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0=(data[i]);
	}
	
	//if first endbyte is used then write to UDR0 when empty
	if(USEFIRSTENDBYTE){
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0=FIRSTENDBYTE;
	}
	//if second endbyte is used then write to UDR0 when empty
	if(USESECONDEDNBYTE){
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0=SECONDENDBYTE;
	}
}

void sendMsg(char msg[]){
	//if necessary, error handling should be executed here before calling writeBytes
	int l=strlen(msg);
	writeBytes(msg, l);
}

void sendMsgWithoutEnd(char data[], int bytesToWrite){
	for (uint8_t i=0; i<bytesToWrite; i++)
	{
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0=(data[i]);
	}
}

void sendInt(int x){
	char xStr[6]={'\0'};
	sprintf(xStr, "%d", x);
	sendMsg(xStr);
}

void sendUInt(unsigned int x){
	char xStr[6]={'\0'};
	sprintf(xStr, "%u", x);
	sendMsg(xStr);
}

void sendUINT8(uint8_t byte){
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=(byte);
}

void sendChar(char x){
	writeBytes(&x, 1);
}

void sendCharWithoutEnding(char x){
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=x;
}

void sendUIntAndMsg(char msg[], unsigned int val){
	char xStr[6]={'\0'};
	sprintf(xStr, "%u", val);
	char _msg[200]={'\0'};
	strcat(_msg, msg);
	strcat(_msg, "\t");
	strcat(_msg, xStr);
	sendMsg(_msg);
}


//returns the oldest message in the buffer
void getMsg(char msg[]){
	//there must be at least one message aviable
	if(newMessage>0){
		newMessage--;
		uint8_t i=0;
		/*do
		{
			msg[i]=rxBuffer[rxReadPos++];
			
			if(rxReadPos >= RX_BUFFER_SIZE)
			{
				rxReadPos = 0;
			}
		} while (msg[i++]!=FIRSTENDBYTE);*/
		
		while (rxBuffer[rxReadPos]!=FIRSTENDBYTE){
			msg[i++]=rxBuffer[rxReadPos++];
			
			if(rxReadPos >= RX_BUFFER_SIZE)
			{
				rxReadPos = 0;
			}
		}
		rxReadPos++;
		//if second endbyte is used, then move rxReadPos one forward
		if(USESECONDEDNBYTE){
			rxReadPos++;
			if(rxReadPos >= RX_BUFFER_SIZE)
			{
				rxReadPos = 0;
			}
		}
	}
}

uint8_t newMsgAv(){
	if(newMessage>0)
		return 1;
	else
		return 0;
}


//lib
ISR(USART0_RX_vect){
	rxBuffer[rxWritePos] = UDR0;
	
	if(rxBuffer[rxWritePos]==FIRSTENDBYTE){
		newMessage++;
	}
	
	rxWritePos++;
	
	if(rxWritePos >= RX_BUFFER_SIZE)
	{
		rxWritePos = 0;
	}
}
