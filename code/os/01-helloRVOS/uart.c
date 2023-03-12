#include "types.h"
#include "platform.h"

#define RHR 0x00
#define THR 0x00
#define DLL 0x00
#define IER 0x01
#define DLM 0x01
#define FCR 0x02
#define ISR 0x02
#define LCR 0x03
#define MCR 0x04
#define LSR 0x05
#define MSR 0x06
#define SPR 0x07

#define LSR_TX_IDLE (1 << 5)

#define UART_REG(reg) ((volatile uint8_t *)(UART_BASE_ADDR + reg))

#define uart_read_reg(reg) (*(UART_REG(reg)))
#define uart_write_reg(reg, v) (*(UART_REG(reg)) = (v))

void uart_init(void)
{
    uart_write_reg(IER, 0x00);

    uint8_t lcr = uart_read_reg(LCR);
    uart_write_reg(LCR, lcr | (1 << 7));
    uart_write_reg(DLL, 0x03);
    uart_write_reg(DLM, 0x00);

    lcr = 0;
    uart_write_reg(LCR, lcr | (3 << 0));
}

int uart_putc(char ch)
{
    while ((uart_read_reg(LSR) & LSR_TX_IDLE) == 0);
    return uart_write_reg(THR, ch);
}

void uart_puts(char *s)
{
    while (*s)
    {
        uart_putc(*s++);
    }
}