#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void main(void)
{
    char *str = {"Ahmed Alhasani\n"};

    //InitLedPin(); // set pin 9 to OUTPUT
    //LedBlink(); // Blink blue light
    
    uart_init();
    
    while(1){
        //uart_putstr(str);
        uart_echo();
    }
    
    
}
