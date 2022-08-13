/* objdump -s -x -d hello.o */

#include <stdio.h>

int global_init = 0x11111111; 			/* .data */
const int global_const = 0x22222222;	/* .rodata */


int main(void)
{
	static int static_var = 0x33333333;	/* .data */
	static int static_var_uninit;		/* .bss */

	int auto_var = 0x44444444;			/* .text */

	printf("hello world!");
	
	return 0;
}