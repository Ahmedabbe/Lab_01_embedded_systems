#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUD 36800
#define MYUBBR ((F_CPU/(16*BAUD))-1)



void uart_init();

void uart_putchar(char chr);
void uart_putstr(const char *str);

unsigned char uart_getchar();

void uart_echo();

#endif

