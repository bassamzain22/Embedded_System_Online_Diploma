#include "uart.h"
unsigned char string_buffer[100]="learn-in-depth:<bassam>";
void main(void)
{
	Uart_send_string(string_buffer);
	
}