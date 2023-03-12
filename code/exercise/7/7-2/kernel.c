#include "types.h"
#include "platform.h"

extern void uart_init(void);
extern void uart_puts(char *s);
extern int uart_putc(char ch);
extern char uart_getc(void);

void start_kernel(void)
{
    uart_init();
    uart_puts("hello, RVOS!\n");
    while (1)
    {
        uint8_t ch = uart_getc();
        if (ch == '\r')
        {
            uart_puts("\r\n");
        }
        uart_putc(ch);
    }
    
}