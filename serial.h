#ifndef SERIAL_H_
#define SERIAL_H_

#define FOSC 16000000UL
#define BAUD 36800UL
#define BRC ((FOSC / (16 * BAUD)) - 1)

#define MAX_BUFFER_LEN 50

void uart_init();

void uart_putchar(char chr);
void uart_putstr(const char *str);

unsigned char uart_getchar();
void uart_getstr(char *buffer);

void uart_echo();
#endif
