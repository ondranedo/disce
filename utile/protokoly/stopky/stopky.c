#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/button.h"
#include "stm32_kit/led.h"

#include <stdio.h>

OS_TID g_t[2];
size_t millicesocds = 0;

void showMilli(int millisecods, int line){    
        char buff[LCD_COLS+1] = {0};
        snprintf(buff, LCD_COLS, "%02u:%02u:%02u", 
        (millisecods/(1000*60))%60, 
        (millisecods/1000)%60,
        millisecods%1000
        );
        
        if(line == 0) LCD_set(LCD_LINE1);
        if(line == 1) LCD_set(LCD_LINE2);

        LCD_print(buff);
}

__task void counter() {
    millicesocds = 0;
    
    while(1) {
        millicesocds++;
        delay_ms(1);
    }
}

__task void show() {
    size_t mili_stamp = 0;
    while(1)
    {
        showMilli(millicesocds, 0);
        
        if(io_read(USER_BUTTON))
        {
            if(!mili_stamp)
                mili_stamp = millicesocds;
            showMilli(mili_stamp, 1);
            
            continue;
        }
        mili_stamp = 0;
        
        delay_ms(70);
    }
}    

__task void setup() {
    LCD_setup();
    LCD_set(LCD_CUR_NO_BLINK);
    LCD_set(LCD_CUR_OFF);
    KBD_setup();
    LED_setup();
    BTN_setup();

    
    g_t[0] = os_tsk_create(counter, 0);
    g_t[1] = os_tsk_create(show, 0);
    
    os_tsk_delete_self();
}

int main()
{
    os_sys_init(setup);
}