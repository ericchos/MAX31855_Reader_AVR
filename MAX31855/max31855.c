/*
 * max31855.c
 *
 * Created: 2/26/2015 10:58:37 AM
 *  Author: eric
 */ 

#include "config.h"
#include <util/delay.h>
#include <stdlib.h>
#include "spi.h"
#include "uart.h"
#include "max31855.h"

void max31855_init()
{
	//Set CS Pin as an Output
	MAX31855_CS_DDR |= (1<<MAX_31855_CS_PIN_1);
	
	MAX31855_CS_PORT |= (1<<MAX_31855_CS_PIN_1);
}

uint16_t max31855_read()
{
	MAX31855_t max31855;
	uint8_t data[4];
	
	//Switch CS to low to initiate data transfer
	MAX31855_CS_PORT &= ~(1<<MAX_31855_CS_PIN_1);
	
	//Get bits D31 to D24
	spi_master_transmit(0xFF);
	data[0] = SPDR;
	
	//Get bits D23 to D16
	spi_master_transmit(0xFF);
	data[1] = SPDR;
	
	//Get bits D15 to D8
	spi_master_transmit(0xFF);
	data[2] = SPDR;
	
	//Get bits D7 to D0
	spi_master_transmit(0xFF);
	data[3] = SPDR;
	
	//Switch CS back to high to end data transfer
	MAX31855_CS_PORT |= (1<<MAX_31855_CS_PIN_1);
	
	#ifdef DEBUG_BUILD
	char buffer[8];
	uart0_print("Raw Value: ");
	itoa(data[0], buffer, 16); uart0_print(buffer); uart0_print(" ");
	itoa(data[1], buffer, 16); uart0_print(buffer); uart0_print(" ");
	itoa(data[2], buffer, 16); uart0_print(buffer); uart0_print(" ");
	itoa(data[3], buffer, 16); uart0_print(buffer); uart0_print(" ");
	uart0_print(", ");
	#endif
	
	//The two most significant bytes hold the thermocouple temp
	max31855.thermocoupleTemp = ((data[0]<<8)|(data[1]));
	
	//Check if the value is negative
	if((max31855.thermocoupleTemp & 0x8000) == 0x8000)
		max31855.signBit = 1;

	//Check if the fault bit(Bit 16) is 1
	if((max31855.thermocoupleTemp & 0x0001) == 0x0001)
	{
		max31855.faultBit = 1;
		#ifdef DEBUG_BUILD
		uart0_print("Fault Detected, ");
		#endif
	}
	
	//Shift out bits D16 and D17	
	max31855.thermocoupleTemp = (max31855.thermocoupleTemp >> 2);
	
	return max31855.thermocoupleTemp;
}