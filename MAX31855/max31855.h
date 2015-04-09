/*
 * max31855.h
 *
 * Created: 2/26/2015 10:58:50 AM
 *  Author: eric
 */ 


#ifndef MAX31855_H_
#define MAX31855_H_

#include <avr/io.h>

#define MAX31855_CS_PORT	PORTC
#define MAX31855_CS_DDR		DDRC
#define MAX_31855_CS_PIN_1	0

#define MAX31855_SCV_BIT	(1<<2)
#define MAX31855_SCG_BIT	(1<<1)
#define MAX31855_OC_BIT		(1<<0)

typedef struct max31855Reading{
	uint16_t thermocoupleTemp;
	uint16_t internalTemp;
	uint8_t signBit;
	uint8_t faultBit;
	uint8_t error;
}MAX31855_t;

void max31855_init();

uint16_t max31855_read();

#endif /* MAX31855_H_ */