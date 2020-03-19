/*
 * UART_debug_v2.h
 *
 * Created: 12-Jun-19 12:12:58 PM
 *  Author: teamv
 */ 


#ifndef UART_DEBUG_V2_H_
#define UART_DEBUG_V2_H_

#define USEFIRSTENDBYTE 1
#define USESECONDEDNBYTE 1
#define FIRSTENDBYTE '\r'
#define SECONDENDBYTE '\n'

#define F_CPU 16000000
#define BAUD 19200
#define BRC ((F_CPU/8/BAUD)-1) //full duplex
#define RX_BUFFER_SIZE 1024

#include <avr/io.h>

void initUART();
void getMsg(char msg[]);
void sendMsg(char msg[]);
uint8_t newMsgAv();
void writeBytes( char data[], int bytesToWrite);
void sendMsgWithoutEnd(char data[], int bytesToWrite);
void sendCharWithoutEnding(char x);
void sendInt(int x);
void sendChar(char x);
void sendUInt(unsigned int x);
void sendUINT8(uint8_t byte);
void sendUIntAndMsg(char msg[], unsigned int val);





#endif /* UART_DEBUG_V2_H_ */