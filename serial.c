#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void uart_init()
{
    //Set baud rate
    UBRR0H = (BRC >> 8);
    UBRR0L = BRC;

    //Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    //Set frame format: 1stop bit, 8bit data, no parity
    //(Just to be safe)
    UCSR0C = 0 
             | (0 << USBS0)                  // 1 stop bit

             | (1 << UCSZ01) | (1 << UCSZ00) // 8 bit data

             | (0 << UPM01) | (0 << UPM00);  // Parity Disabled
}

//Transmit character to serial interface
void uart_putchar(char chr)
{
    /*
    This check is for arranging the order of '\r' and '\n' being printed 
    to always be the same, no matter which serial terminal is used for input.
    */
    if (chr == '\r' || chr == '\n')
    {
        //Wait for transmit buffer to be empty
        while (!(UCSR0A & (1 << UDRE0)));
        //Put data into buffer and transmit the data
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

void uart_getstr(char *buffer)
{
    
    char c;
    int i = 0;

    //Receives serial input in char c and prints it on screen.
    c = uart_getchar();
    uart_putchar(c);

    /*
    Add input into array and keep receiving, printing 
    and adding until user inputs an EOL char (hits enter key)
    */
    while ((c != '\r') && (c != '\n') && i <= (MAX_BUFFER_LEN-3))
    {
        buffer[i] = c;
        i++;
        c = uart_getchar();
        uart_putchar(c);

    }
    //Cap off array with EOL chars
    add_EOL_chars(buffer, i);
}

void add_EOL_chars(char *buffer, int i)
{
    //Add EOL chars manually into array in any order desired, finished with '\0'
    buffer[i] = '\r';
    buffer[i + 1] = '\n';
    buffer[i + 2] = '\0';
}

//Read and transmit back serial interface inputs
void uart_echo()
{
    uart_putchar(uart_getchar());
}
