#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

void LedBlink()
{
    while (1)
    {
        ToggleBit(); // Blink blue LED color on and off
    }
}