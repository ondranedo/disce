// I hate WYSIWYG

#include <stdio.h>
#include <math.h>
#include "stm32_kit.h"             
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/button.h"
#include "stm32_kit/led.h"

static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = { 
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#',
};

typedef struct {
	size_t part;
  char name;
} WashingCycle;

WashingCycle g_washingCycles[4] = {
	{10,'P'},{60,'W'},{90,'R'},{100, 'D'}
};

size_t g_washingCycleRelative[4];

typedef enum { 
	LINE1, 
	LINE2
} Line;

OS_SEM g_lcdSemID;
size_t g_timePassed; // in seconds

__task void menu(void);

void printLCD(const char* payload, Line line) {
	os_sem_wait(g_lcdSemID, 0xFFFF);
	LCD_set(line == LINE1?LCD_LINE1: LCD_LINE2);
	LCD_print(payload);
	os_sem_send(g_lcdSemID);
}

void clearLCD()
{
	os_sem_wait(g_lcdSemID, 0xFFFF);
	LCD_set(LCD_CLR);
	os_sem_send(g_lcdSemID);
}

__task void washingTask(void* argv) {
	size_t option = *(size_t*)argv;	
	char buff[LCD_COLS+1] = {0};

	while(1) {
		if(g_washingCycleRelative[option] > g_timePassed) {
			size_t min = (g_washingCycleRelative[option]-g_timePassed)/60, sec = (g_washingCycleRelative[option] - g_timePassed)%60;
			
			snprintf(buff, LCD_COLS, "%c %02zi:%02zi",g_washingCycles[option].name, min, sec);
			printLCD(buff, LINE1);
		} else {
			(*(size_t*)argv)++;
			if(option < 3)
				os_tsk_create_ex(washingTask, 0, argv);
			os_tsk_delete_self();
		}
	}
}

// Task that runs each cycle and counts total time3
__task void motherTask(void* argv) {
	size_t duration = *(size_t*)argv, option = 0;
	
	for(size_t i = 0 ; i < 4; ++i)
		g_washingCycleRelative[i] = ((float)g_washingCycles[i].part/100.0)*duration;
	
	g_timePassed = 0;
	os_tsk_create_ex(washingTask, 0, &option);
	
	while(1) {
		char buff[LCD_COLS+1] = {0};
		snprintf(buff, LCD_COLS, "%02zi:%02zi",(duration-g_timePassed)/60,(duration-g_timePassed)%60);
		printLCD(buff, LINE2);
		
		if(g_timePassed >= duration) {
			g_timePassed = 0;
			os_tsk_create(menu, 0);
			os_tsk_delete_self();
		}
				
		delay_ms(1000);
		g_timePassed++;
	} 
}

__task void menu() {
	const size_t
		duration_size = 3;
	size_t
		duration[duration_size] = {60, 90, 120},
		option = 0;
			
	while(1) {
		// Render
		clearLCD();
		
		char buff[LCD_COLS + 1] = { 0 };
		snprintf(buff, LCD_COLS, ">%zis", duration[option]);
		printLCD(buff, LINE1);
		
		
		if(option < duration_size - 1) {
			snprintf(buff, LCD_COLS, " %zis", duration[option+1]);
			printLCD(buff, LINE2);
		}
		
		// W8 for input
		char c;
		do
			c = KBD_read();
		while (!c);
		
		// Move down
		if(c == '2' && option > 0)
			option--;
		
		// Move up
		if(c == '8' && option < duration_size - 1) 
			option++;
		
		// Start washing cycle
		if(c == '5')
		{
			os_tsk_create_ex(motherTask, 0, &duration[option]);
			os_tsk_delete_self();
		}		
	}
}

__task void setup() {
	LCD_setup();
	KBD_setup();
	LED_setup();
	
	LCD_set(LCD_CUR_NO_BLINK);
	LCD_set(LCD_CUR_OFF);
	
	os_sem_init(g_lcdSemID, 1);
	
	os_tsk_create(menu, 0);
	
	os_tsk_delete_self();
}

int main(void) {
  os_sys_init(setup);
}
