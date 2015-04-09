/*
 * main.c
 *
 * Created: 2/26/2015 10:30:12 AM
 *  Author: eric
 */ 

#include "config.h"
#include "uart.h"
#include "spi.h"
#include "max31855.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>

int main(void)
{
	uart0_init();
	spi_master_init();
	max31855_init();
	
	uart0_print("Testing MAX31855\r\n");
	
	int16_t rawdata;
	char printBuffer[5];
	
    while(1)
    {
        rawdata = max31855_read();
		
		itoa(rawdata, printBuffer, 10);
		
		uart0_print(printBuffer); uart0_print(", ");
		
		uart0_print("\r\n");
		
		_delay_ms(100);
    }
}