/*
 * TypeCaster.c
 *
 * Created: 19-Mar-20 6:04:43 PM
 *  Author: teamv
 */ 

#include "TypeCaster.h"


/************************************************************************/
/* Concatenate two unsigned chars to an unsigned int                    */
/************************************************************************/
unsigned int charsToUInt(unsigned char LSB, unsigned char MSB){
	return ((MSB<<8)|(uint8_t) LSB);
}

/************************************************************************/
/* String to unsigned int                                               */
/************************************************************************/
unsigned int stringToUInt(char str[]){
	return atoi(str);
}