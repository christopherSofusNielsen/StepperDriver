/*
 * TypeCaster.h
 *
 * Created: 19-Mar-20 6:04:55 PM
 *  Author: teamv
 */ 


#ifndef TYPECASTER_H_
#define TYPECASTER_H_

#include <stdlib.h>
#include <avr/io.h>

extern unsigned int charsToUInt(unsigned char LSB, unsigned char MSB);
extern unsigned int stringToUInt(char str[]);



#endif /* TYPECASTER_H_ */