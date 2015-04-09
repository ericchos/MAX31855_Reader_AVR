/*
 * spi.c
 *
 * Created: 9/11/2014 8:37:54 AM
 *  Author: eric
 */ 
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

/*****************************************************************

******************************************************************/
void spi_master_init()
{
	/* Set MOSI and SCK output, while others as input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	
	/* Enable SPI */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	/* Set SPI Speed */
	SPSR = 0x00;
}

/*****************************************************************

******************************************************************/
void spi_master_transmit(char cData)
{
	/* Start Transmission */
	SPDR = cData;
	
	/* Wait for transmission to complete */
	while(!(SPSR & (1<<SPIF)));
}

/*****************************************************************

******************************************************************/
void spi_slave_init()
{
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	
	/* Enable SPI */
	SPCR = (1<<SPE);
}

/*****************************************************************

******************************************************************/
uint8_t spi_slave_receive()
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	
	/* Return Data Register */
	return SPDR;
}

