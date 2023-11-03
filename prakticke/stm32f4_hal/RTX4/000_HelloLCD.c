#define LCD_COLS 8
#define LCD_ROWS 2

#include <RTL.h>
#include "stm32_kit.h"
#include "stm32_kit/lcd.h"

OS_TID lcd_text;

struct text_data {
	char* text1;
	char* text2;
};

__task static void print_text(void* argv)
{
	struct text_data data;
	data.text1 = ((struct text_data*)argv)->text1;
	data.text2 = ((struct text_data*)argv)->text2;
	
	while(1)
	{
		LCD_set(LCD_LINE1);
		LCD_print(data.text1);

		LCD_set(LCD_LINE2);
		LCD_print(data.text2);
		
		delay_ms(100);
		os_tsk_pass();
	}
}

__task static void init_os(void)
{
	LCD_setup();
	LCD_set(LCD_CUR_OFF);

	while(1)
	{
			lcd_text = os_tsk_create_ex(print_text, 0,(void*)&((struct text_data)
				{"Hello..","..World"}
			));
			
	}
}

int main(void){
	os_sys_init(init_os);
}