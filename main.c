#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void main(void)
{
    char *buffer[MAX_BUFFER_LEN];
    
    // char *str = {"Ahmed Alhasani\n"};

    InitLedPin(); // set pin 9 to OUTPUT

    //BlinkLED(); // Blink blue light

    uart_init();

    while (1)
    {
        uart_getstr(buffer);
        led_switch(buffer);

        //uart_putstr(str);
        //uart_echo();
    }
}