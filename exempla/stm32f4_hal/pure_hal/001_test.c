/*
	Napiste program pro ovdladani lrkoveho motoru
	
	-Vyberte smer pomoci klaves < 4, > 6, ^ 8, v 2
	-zmacknutim 5 rozhpohybujte motorek
	-zmacknutim 5 ukoncete pohyb
	-na LED diodach zobrazte smer pohybu
	-rychlost pohybu je 0.1U/250ms
	-na obrazovku vzpisujte souradnice X, Y pro novy kro a kroky kumulative
	-limit X, Y je 1000



*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "stm32_kit.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"

int Invert(int v)
{
	return v?0:1;
}

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
	
	LCD_set(LCD_CLR);
	LCD_goto(0,0);
	
	LCD_set(LCD_CUR_NO_BLINK);
	LCD_set(LCD_CUR_OFF);
};

enum Direction {
	LEFT, UP, RIGHT, DOWN
};
typedef enum Direction Direction;

struct PosXY {
	double x, y;
};
typedef struct PosXY PosXY;


int g_moving = 0;
Direction g_direction = LEFT;
PosXY g_pathXY = {0, 0};
const float g_speed = 0.4; // 0.4U / 1s

Direction DireFromChar(char c)
{
	switch(c)
	{
		case '4': return LEFT;
		case '2': return DOWN;
		case '8': return UP;
		case '6': return RIGHT;
	}
	return LEFT;
}

void PathRenderLCD(PosXY* pos)
{
	char buff1[LCD_COLS + 1];
	char buff2[LCD_COLS + 1];
	
	snprintf(buff1, LCD_COLS + 1, "X:%.2f", pos->x);
	snprintf(buff2, LCD_COLS + 1, "X:%.2f", pos->y);
	
	for(size_t i = 0; i < LCD_COLS+1; ++i)
		if(buff1[i] == '\0')
			buff1[i] = ' ';
	
	for(size_t i = 0; i < LCD_COLS+1; ++i)
		if(buff2[i] == '\0')
			buff2[i] = ' ';
		
	LCD_set(LCD_LINE1);	
	LCD_print(buff1);
	LCD_set(LCD_LINE2);
	LCD_print(buff2);
}

void DireRenderLed(Direction dir)
{
	io_set(LED_IN_0, 0);
	io_set(LED_IN_1, 0);
	io_set(LED_IN_2, 0);
	io_set(LED_IN_3, 0);
	io_set(LED_EX_1, 1);
	
	switch(dir)
	{
		case LEFT:  io_set(LED_IN_0, 1); break;
		case UP:    io_set(LED_IN_1, 1); break;
		case RIGHT: io_set(LED_IN_2, 1); break;
		case DOWN:  io_set(LED_IN_3, 1); break;
	}
	
	if(g_moving)
		io_set(LED_EX_1, 0);
}

void PathIncreaseDir(PosXY* pos, Direction dir, float delta)
{
	switch(dir)
	{
		case LEFT:  pos->x-=delta; break;
		case UP:    pos->y+=delta; break;
		case RIGHT: pos->x+=delta; break;
		case DOWN:  pos->y-=delta; break;
	}
}

// Should take 10ms
void update()
{	
		float speed_10ms = g_speed / 10.0;
		delay_ms(9); // 1 ms for render...
	
		if(!g_moving)
			PathIncreaseDir(&g_pathXY, g_direction, speed_10ms);

		PathRenderLCD(&g_pathXY);
}

int main(void) {
		while(1)
		{
			char c;
			do {
				c = KBD_read();
				update();
			} while(!c);
			
			if(c == '5')
				g_moving = Invert(g_moving);
			else
				g_direction = DireFromChar(c);
			
			DireRenderLed(g_direction);
		}
}

