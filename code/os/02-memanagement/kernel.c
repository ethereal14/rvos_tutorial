#include "os.h"

extern void uart_init(void);
extern void page_test(void);

void start_kernel(void)
{
    uart_init();
    uart_puts("hello, RVOS!\n");
    page_init();
    page_test();
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