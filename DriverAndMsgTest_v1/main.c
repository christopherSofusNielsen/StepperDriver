/*
 * DriverAndMsgTest_v1.c
 *
 * Created: 19-Mar-20 11:08:21 AM
 * Author : teamv
 */ 

#include <avr/io.h>

#include "UART_debug_v2.h" //debug

//Global variables


//Functions



int main(void)
{
    //Initialize
	initUART();
	sendMsg("Hello");
	sendMsg("World");
	
	
    while (1) 
    {
		if (newMsgAv())
		{
			char msg[50]={'\0'};
			getMsg(msg);
			sendMsg(msg);
		}
    }
}

