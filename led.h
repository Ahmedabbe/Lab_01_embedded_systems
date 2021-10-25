#ifndef LED_H
#define LED_H

#define bluePin PB1

void InitLedPin()
{
    DDRB |= (1 << DDB1); //setting pin 9 to OUTPUT
}

void ToggleBit()
{
        // Toggling bit 1 on/off using XOR (setting 0->1 & 1->0) on the shifted bit
        PORTB ^= (1 << bluePin);
        _delay_ms(500);
}

#endif