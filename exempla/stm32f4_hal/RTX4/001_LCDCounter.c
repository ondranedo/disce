#define LCD_COLS 8
#define LCD_ROWS 2

#include <RTL.h>
#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/gpio.h"
#include "stm32_kit/led.h"

#include <stdio.h>

#define TO_OSX(x, ...) (void*)&((x){__VA_ARGS__})

int lock;

OS_TID lcd_text;
OS_TID button_monitor;
OS_TID timer;

struct text_data {
	char* text1;
	char* text2;
};

struct button_data {
	char* counter_str;
};

struct time {
	char* time_str;
}

__task static void print_text(void* argv)
{
	struct text_data* data = argv;
	struct text_data prev = *data;
	int diff = 0;

	while(1)
	{
		if(strcmp(prev.text1, data->text1))
			diff = 1;
		else if(strcmp(prev.text2, data->text2))
			diff = 1;
		else
			diff = 0;
		
		
		LCD_set(LCD_LINE1);	
		LCD_print(data->text1);;

		LCD_set(LCD_LINE2);
		LCD_print(data->text2);
		
		if(diff)
			LCD_set(LCD_CLR);
		
		prev = *data;
	}
}


__task static void monitor_button(void* argv){
	struct button_data* data = (struct button_data*)argv;
	int counter = 0;
	
	while(1)
	{
		if(io_read(USER_BUTTON))
		{
			counter++;
			delay_ms(35);
		}
		
		if(lock)
			os_tsk_pass();
		lock = 1;
		snprintf(data->counter_str, 8, "%d", counter);
		lock = 0;
	}
}

__task static void init_os(void)
{
	LED_setup();
	LCD_setup();
	LCD_set(LCD_CUR_OFF);
	
	char counter_str[8];
	char timer_str[8];
	
	while(1)
	{
			lcd_text = os_tsk_create_ex(print_text, 0, TO_OSX(struct text_data, counter_str, timer_str));
			button_monitor = os_tsk_create_ex(monitor_button, 0, TO_OSX(struct button_data, counter_str));
			//timer = os_tsk_create_ex(timer_mmss, 0, TO_OSX(struct time, timer_str));
	}
}

int main(void){
	os_sys_init(init_os);
}