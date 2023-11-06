#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "stm32_kit.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"


#define INVERT(v) v?0:1
#define GET_BIT(f,b)(f>>b)&(uint8_t)0x1
#define GET_BIT_A(f,b,a) a?INVERT(GET_BIT(f,b)):GET_BIT(f,b)

#define MAX_BIT_LEN 8

static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#'
  };

BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 10000);
	LED_setup();
	KBD_setup();
	LCD_setup();
	
	LCD_goto(0,0);
};

struct led {
	enum pin pin;
	uint8_t active;
};

static struct led ledlist[8] = {
	{LED_EX_0, 1},	
	{LED_EX_1, 1},
	{LED_EX_2, 1},
	{LED_EX_3, 1},
	{LED_IN_0, 0},
	{LED_IN_1, 0},
	{LED_IN_2, 0},
	{LED_IN_3, 0}
};

void visualize_in_bin(uint8_t byte, uint8_t maxbit){
	for(size_t i = 0; i < maxbit; ++i)
		io_set(ledlist[i].pin,GET_BIT_A(byte, i, ledlist[i].active));
}

uint8_t get_bin_data_kbd(uint8_t maxbit){
	char arr[MAX_BIT_LEN] = {0};
	uint8_t arr_size = 0;
	uint8_t c = 0;
	
	LCD_set(LCD_CUR_OFF);
	
	do {
		do
        c = KBD_read();
    while(!c);
		
		if(c=='*')
		{
			arr[arr_size] = '\0';
			arr_size = arr_size>0?arr_size-1:arr_size;
		}
		else if(c != '#')
		{
			arr[arr_size] = c;
			arr_size++;
			
			if(atoi(arr)>pow(2.0, maxbit)-1){
				snprintf(arr, MAX_BIT_LEN, "%d", (int)pow(2.0, maxbit)-1);
				arr_size = floor(log10(pow(2.0, maxbit)));
			}
		}
		
		LCD_set(LCD_CLR);
		LCD_set(LCD_LINE1);
		LCD_print(arr);
		
		char buff[MAX_BIT_LEN+1] = {'x','x','x','x','x','x','x','x', '\0'};
		for(size_t i = 0; i < maxbit; ++i)
		{
			buff[MAX_BIT_LEN-i-1] = GET_BIT(atoi(arr), i)?'1':'0';
			LCD_set(LCD_LINE2);
			LCD_print(buff);
		}
		
		delay_ms(67);
	}while(c!='#');
	
	return atoi(arr);
}

int main(void) {
	uint8_t bin_data = 0xA;
	uint8_t bit_size = 5;
	
	if(bit_size>MAX_BIT_LEN) 
		return -1;
	
	while (1) {
		// Get input
		bin_data = get_bin_data_kbd(bit_size);
		
		// Output
		visualize_in_bin(bin_data, bit_size);
	}
}

