/*
 * spi.h
 *
 * Created: 9/11/2014 8:37:43 AM
 *  Author: eric
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

#define DDR_SPI			DDRB
#define DD_SS			(2) /* SS is PB2 */
#define DD_MOSI			(3)	/* MOSI is PB3 */
#define DD_MISO			(4) /* MISO is PB4 */
#define DD_SCK			(5) /* SCK is PB5 */

#define SPI_MODE_0		(0<<CPOL)|(0<<CPHA)
#define SPI_MODE_1		(0<<CPOL)|(1<<CPHA)
#define SPI_MODE_2		(1<<CPOL)|(0<<CPHA)
#define SPI_MODE_3		(1<<CPOL)|(1<<CPHA)

#define SPI_FOSC_4		(0<<SPR1)|(0<<SPR0)
#define SPI_FOSC_16		(0<<SPR1)|(1<<SPR0)
#define SPI_FOSC_64		(1<<SPR1)|(0<<SPR0)
#define SPI_FOSC_128	(1<<SPR1)|(1<<SPR0)

void spi_master_init();
/****************************************************************
DESCRIPTION: 

ARGUMENTS: None
RETURN: None
****************************************************************/

void spi_master_transmit(char cData);
/****************************************************************
DESCRIPTION:

ARGUMENTS: char cData
RETURN: None
****************************************************************/

void spi_slave_init();
/****************************************************************
DESCRIPTION:

ARGUMENTS: None
RETURN: None
****************************************************************/

uint8_t spi_slave_receive();
/****************************************************************
DESCRIPTION:

ARGUMENTS: None
RETURN: None
****************************************************************/

#endif /* SPI_H_ */