#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

void LedBlink()
{
    InitBluePin(); // set pin 9 to OUTPUT
    ToggleBit(); // blink LED blue color on and off
}