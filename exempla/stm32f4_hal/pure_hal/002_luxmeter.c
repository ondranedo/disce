#include "stm32_kit/lcd.h"
#include "stm32_kit/uart.h"
#include "stm32_kit/adc.h"

#include "stm32_kit.h"

#include <stdio.h>

#define ASCII_ENTER 13

BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 10000);
	
	LCD_setup();
	ADC_setup();
	UART_setup();
	
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
};

struct Program {
	const char* name;
	int(*callback)(void);
};

const char* device_name	= "stm32";
const size_t username_s = 128;
char username[username_s];
const size_t path_s = 512;
char path[path_s] = "/";

void uart_print(const char* str) {
	UART_write(str, strlen(str));
}

void uart_nl() {
	uart_print("\r\n");
}

void uart_clear() {
	uart_print("\033[2J\033[1;1H");
}

void uart_read(char* buff, size_t size) {
	char c;
	size_t s = 0;
	do {	
		UART_putc(c = UART_getc());
		if(c && c != ASCII_ENTER) {
			buff[s++] = c;
			if(s == size) break;
		}
	} while(c != ASCII_ENTER);
	buff[s]=0;
}

void authorize() {
	uart_clear();
	uart_print("LOGIN");
	uart_nl();
	uart_print("----------------------");
	uart_nl();
	uart_print("username: ");
	uart_read(username, username_s);
	uart_clear();
	uart_print("Hello ");
	uart_print(username);
	uart_print("!");
	uart_nl();
	uart_nl();
	uart_nl();
}

void stm_read(char* buff, size_t size) {
	uart_print(username);
	uart_print("@");
	uart_print(device_name);
	uart_print(":");
	uart_print(path);
	uart_print("$ ");
	uart_read(buff, size);
	uart_nl();
}


int help()
{
	uart_nl();
	uart_print("HELP");
	
	return 1;
}

struct Program programs[] = {
	{"help", help},
	{0,0}
};

struct Program* find_program(char* argv) {
	size_t it = 0;
	while(1)
	{
		if(!strcmp(programs[it++].name, argv))
			return &programs[it];
		
		if(!programs[it++].callback) break;
	}
	
	return 0;
}

int main(void) {
	authorize();
	
	while (1) {
		char buff[1024];
		stm_read(buff, 1024);
		struct Program* p = find_program(buff);
		
		if(p != 0)
		{
			int code = p->callback();
			uart_nl();
			uart_print("Program finished with error code ");
			
			char ret_code[16];
			snprintf(ret_code, 16, "%i", code);
			
		} else {
			uart_print("Unknown command");
			uart_nl();
		}
	}
}

