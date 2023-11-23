#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"

#include <stdio.h>

static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#'
  };

OS_TID g_tskIncr, g_tskDecr, g_tskMenu;
OS_SEM g_lcdSema;
	
typedef struct {
	int starting_seconds;
	int direction; //0 down, 1 up
	int line;
} CounterParam;

CounterParam g_incrData = {0, 1, 0};

void showSeconds(int seconds, int line){	
		char buff[LCD_COLS+1] = {0};
		snprintf(buff, LCD_COLS, "%02u:%02u",seconds/60,seconds%60);
		
		for(size_t i = 0; i < LCD_COLS; ++i)
			if(buff[i] == '\0')
				buff[i] = ' ';
		
		os_sem_wait(g_lcdSema, 0xFFFF);
		
		if(line == 0) LCD_set(LCD_LINE1);
		if(line == 1) LCD_set(LCD_LINE2);

		LCD_print(buff);
		
		os_sem_send(g_lcdSema);
}

__task void counter(void* argv) {
	CounterParam* param = (CounterParam*)argv;
	int seconds = param->starting_seconds
		;
	while(1) {
			showSeconds(seconds, param->line);
			delay_ms(1000);
			
			if(param->direction == 1 && seconds == 3)
			{
				OS_TID task = g_tskIncr;
				g_tskIncr = os_tsk_create_ex(counter, 0, &g_incrData);
				os_tsk_delete(task);
				break;
			}
		
			param->direction?
		    seconds++:
		   (seconds>0?
		      seconds--:
		      seconds);
	}
}

__task void menu() {
	int option = 0;
	const int arrSize = 4;
	int arr[arrSize] = {60, 120, 180, 360};

	while(1) {
			char buff[LCD_COLS] = { 0 };
			snprintf(buff, LCD_COLS, "%u]%u", option+1, arr[option]);
			LCD_set(LCD_CLR);
			LCD_set(LCD_LINE1);
			LCD_print(buff);
		
			char c;
			do
				c = KBD_read();
			while(!c);
			if(c=='5')
			{
					g_tskIncr = os_tsk_create_ex(counter, 0, &((CounterParam){0  , 1, 0}));
					g_tskDecr = os_tsk_create_ex(counter, 0, &((CounterParam){arr[option], 0, 1}));
			
					break;
			}
			if(c=='2' && option>0) option--;
			if(c=='8' && option<arrSize-1) option++;
	}	
	
	os_tsk_delete_self();
}

__task void setup() {
	LCD_setup();
	LCD_set(LCD_CUR_NO_BLINK);
	LCD_set(LCD_CUR_OFF);
	KBD_setup();
	
	os_sem_init(g_lcdSema, 1);
	
	g_tskMenu = os_tsk_create(menu, 0);

	os_tsk_delete_self();
}

int main()
{
	
	os_sys_init(setup);
}
