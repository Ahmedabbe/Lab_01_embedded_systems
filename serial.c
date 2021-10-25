#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void uart_init()
{
    //Set baud rate
    UBRR0H = (MYUBBR >> 8);
    UBRR0L = MYUBBR;

    //Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    //Set frame format: 1stop bit, 8bit data, no parity
    //(Just to be safe)
    UCSR0C = 0 
            | (0 << USBS0)                      // 1 stop bit
            | (1 << UCSZ01) | (1 << UCSZ00)     // 8 bit data
            | (0 << UPM01) | (0 << UPM00);      // Parity Disabled
}

//Transmit character to serial interface
void uart_putchar(char chr)
{
    if (chr == '\n')
    {
        //Wait for transmit buffer to be empty
        while (!(UCSR0A & (1 << UDRE0)));
        //Put data into buffer, sends the data
        UDR0 = '\r';

        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = '\n';
    }
    else
    {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = chr;
    }
}

void uart_putstr(const char *str)
{
    int i = 0;

    //Iterate buffer until end of line char
    while (str[i] != '\0')
    {
        //Transmit str[i] character ever iteration
        uart_putchar(str[i]); 
        i++;
    }
}

//Function to receive data
unsigned char uart_getchar()
{
    //Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));
    //Get and return received data from buffer
    return UDR0;
}

//Read and transmit back serial interface inputs
void uart_echo()
{
    uart_putchar(uart_getchar());
}
