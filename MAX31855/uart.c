/*
 * uart.c
 *
 * Created: 7/3/2014 8:49:51 PM
 *  Author: eric
 */ 

#include "config.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

/***************************************************************** 
Initialize UART hardware 
******************************************************************/
void uart0_init()
{
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)/*|(1<<RXCIE0)*/;
	
	/* Set frame format: 8 bit data, 1 stop bit */
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	/* Set baud rate */
	UBRR0H = (uint8_t)(UART0_UBRR>>8);
	UBRR0L = (uint8_t) UART0_UBRR;
}

/***************************************************************** 
UART Transmit 
******************************************************************/
void uart0_tx(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while(!(UCSR0A & (1<<UDRE0)));
	
	/* Put data into buffer, and send data */
	UDR0 = data;
}


/*****************************************************************
UART Receive 
******************************************************************/
char uart0_rx(void)
{
	/* Wait for data to be received */
	while(!(UCSR0A & (1<<RXC0)));
	
	/* Get and return received data from buffer */
	return UDR0;
}

/***************************************************************** 
Write a null terminated string to UART
*****************************************************************/
void uart0_print(char *str)
{
	/* If string is empty or has reached the NULL terminator, 
		exit function */
	if(str==0 || *str == 0)
		return;
	
	/* Each character of the string starting with the first
	character will be sent off into the USART buffer to be 
	transmitted until the string reaches the last character */
	do 
	{
		uart0_tx(*str++);
	} while(*str!=0);	
}

/***************************************************************** 
Write a string of characters stored in flash to LPT100 module 
*****************************************************************/
void uart0_print_F(const char *fdata)
{
	while(pgm_read_byte(fdata) != 0x00)
	{
		uart0_tx(pgm_read_byte(fdata++));
	}
}

/*****************************************************************
Write an 8-bit integer value as ASCII characters
******************************************************************/
void uart0_print_8(uint8_t integerVal)
{
	uint16_t temp[3];
	int16_t i,j;
	
	for(i=0; i<=2; i++)
	{
		temp[i] = integerVal % 10;
		integerVal = integerVal/10;
	}
	
	/* Skip all the leading zeros */
	for (j = 2; j >= 1; j--)
	{
		if (temp[j] != 0)
		{
			break;
		}
	}
	
	/* Send converted int to ascii value to uart */
	for (; j >= 0; j--)
	{
		uart0_tx(temp[j]+'0');
	}
}

/*****************************************************************
Write an 16-bit integer value as ASCII characters
******************************************************************/
void uart0_print_16(uint16_t integerVal)
{
	uint16_t temp[5];
	int16_t i,j;
	
	for(i=0; i<=4; i++)
	{
		temp[i] = integerVal % 10;
		integerVal = integerVal/10;
	}
	
	/* Skip all the leading zeros */
	for (j = 4; j >= 1; j--)
	{
		if (temp[j] != 0)
		{
			break;
		}
	}
	
	/* Send converted int to ascii value to uart */
	for (; j >= 0; j--)
	{
		uart0_tx(temp[j]+'0');
	}
}

/*****************************************************************
Write convert a 32-bit integer value to ASCII characters
******************************************************************/
void uart0_print_32(uint32_t longVal)
{
	uint32_t temp[10];
	int32_t i,j;
	
	for(i=0; i<=9; i++)
	{
		temp[i] = longVal % 10;
		longVal = longVal/10;
	}
	
	/* Skip all the leading zeros */
	for (j = 9; j >= 1; j--)
	{
		if (temp[j] != 0)
		{
			break;
		}
	}
	
	/* Send converted int to ascii value to uart */
	for (; j >= 0; j--)
	{
		uart0_tx(temp[j]+'0');
	}
}

void uart0_print_itoa(int16_t integerValue)
{
	char printBuffer[6];
	
	itoa(integerValue, printBuffer, 10);
	
	uart0_print(printBuffer);
}

/*****************************************************************
Convert ASCII number to int
******************************************************************/
uint8_t uart0_convert_num(char rxNum)
{
	return rxNum &= ~(0x30);
}

/*****************************************************************
UART RX receive ISR 
******************************************************************/
/*
ISR(USART_RX_vect, ISR_BLOCK)
{
	
}
*/
/*****************************************************************
Empty UDRE ISR
******************************************************************/
/*
ISR(USART_UDRE_vect, ISR_BLOCK)
{
	
}
*/