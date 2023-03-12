#ifndef _OS_H_
#define _OS_H_

#include "types.h"
#include "platform.h"

#include <stddef.h>
#include <stdarg.h>

/* uart */
extern int uart_putc(char ch);
extern void uart_puts(char *s);
extern char uart_getc(void);

/* printf */
extern int printf(const char *s, ...);
extern void panic(char *s);

/* memory management */
extern void page_init(void);

#endif // _OS_H_