#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

void BlinkLed()
{
    while (1)
    {
        //Toggling bit 1 on/off using XOR (setting 0->1 & 1->0) on the shifted bit
        PORTB ^= (1 << bluePin);
        _delay_ms(500);
    }
}

void InitLedPin()
{
    DDRB |= (1 << DDB1);     //Setting pin 9 to OUTPUT
    PORTB ^= (1 << bluePin); //Starts by turning LED off
}

void led_switch(const char *buffer)
{
    if (!strcmp(buffer, "on\r\n"))
    {
        PORTB &= ~(1 << PB1);
    }
    if (!strcmp(buffer, "off\r\n"))
    {
        PORTB |= (1 << PB1);
    }
}
