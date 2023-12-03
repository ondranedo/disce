
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "stm32_kit.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"

static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#'
  };

typedef struct {
    char* name;
    float price_l;
} Fuel;
typedef enum {
    STATION_STANDBY, STATION_PUMPING, STATION_RESULT, STATION_ADMIN
} StationState;
typedef struct {
    void(*callback)(void*);
    char input;
} CallbackButton;
typedef struct {
    void(*setup)(void);
    void(*update)(void);
    CallbackButton buttonStates[KEYPAD_ROWS*KEYPAD_COLS];
    StationState sate;
    char line1[LCD_COLS+1];
    char line2[LCD_COLS+1];
} State;

// GLOBAL BLOCK
static const size_t g_fuelSize = 2;
static Fuel g_fuel[g_fuelSize] = {
    {"BENAL", 45.6},
    {"NAFTA", 38.4}
};
static Fuel*         g_fuelActive = 0;
static float         g_pumpedLiters = 0;
static const size_t g_fuelLitersMax = 50;
static const size_t g_stationStateSize = 4;
static const size_t g_pumpingRate = 2; // 2l/s
static State*       g_activeState = 0;
//~GLOBAL BLOCK

// CALLBACK BLOCK
void set_fuel_1(void* argv);
void set_fuel_2(void* argv);
void set_fuel(void* argv) {
    Fuel* p = (Fuel*) argv;
    for(size_t i = 0; i < g_fuelSize; ++i)
        if(!strcmp(g_fuel[i].name, p->name))
            strcpy(g_fuel[i].name, p->name);
}

//~CALLBACK BLOCK

// DECLARE BLOCK
void state_goto_next(void* argv);
void state_goto_admin(void* argv);
void setup_standby();
void update_pumping();
void setup_pumping();
void setup_result();
void admin_change_fuel_1();
void admin_change_fuel_2();
void admin_setup();
void none(){}
//~DECLARE BLOCK

// FSM
static State g_state[g_stationStateSize] = {
    {
        setup_standby, none, 
        {{set_fuel_1, '1'},{set_fuel_2, '2'},{state_goto_next, '4'},{ state_goto_admin, '0'}},
        STATION_STANDBY,
        "",
        ""
    },
    {
        setup_pumping, update_pumping, 
        {{state_goto_next, '6'}},
        STATION_PUMPING,
        "",
        ""
    },
    {
        setup_result, none, 
        {{state_goto_next, '#'}},
        STATION_RESULT,
        "",
        ""
    }
    ,
    {
        afmin_setup, none, 
        {{state_goto_next, '#'}, {admin_change_fuel_1, '1'},{admin_change_fuel_2, '2'}},
        STATION_ADMIN,
        "",
        ""
    }
};

void state_goto_admin(void* argv)
{
    g_activeState = (State*)g_state+3;
    g_activeState->setup();
}

void admin_setup()
{
    strcpy(g_activeState->line1, "ZMENA");
    strcpy(g_activeState->line2, "1 2");
    g_activeState->line1[LCD_COLS] = '\0';
    g_activeState->line2[LCD_COLS] = '\0';
}

void set_fuel_1(void* argv) {
    g_fuelActive = g_fuel;
    strcpy(g_activeState->line1, g_fuelActive->name);
    strcpy(g_activeState->line2, "^^^^^^^^");
}
void set_fuel_2(void* argv) {
    g_fuelActive = g_fuel + 1;
    strcpy(g_activeState->line1, g_fuelActive->name);
    strcpy(g_activeState->line2, "^^^^^^^^");
}

void change_fuel(Fuel* const fuel)
{
    char c;
    int decimal = 0;
    char buff[32] = {0};
    size_t buff_size = 0;

    while (1)
    {
        do
            c = KBD_read();        
        while(!c);
        if(c=='#' || buff_size==32) break;
        if(c=='.' && !decimal) {
            buff[buff_size] = '.';
            decimal = 1;
            continue;
        }
        buff[buff_size] = c;
    }
 
    fuel->price_l = atof(buff);
}

void admin_change_fuel_1(void* argv)
{
    change_fuel(g_fuel);
}

void admin_change_fuel_2(void* argv)
{
    change_fuel(g_fuel + 1);
}

void setup_standby()
{
    strcpy(g_activeState->line1, g_fuel[0].name);
    strcpy(g_activeState->line2, g_fuel[1].name);
    g_activeState->line1[LCD_COLS] = '\0';
    g_activeState->line2[LCD_COLS] = '\0';
    g_pumpedLiters = 0;
    g_fuelActive = 0;
}

void setup_pumping() {
    strcpy(g_activeState->line1, g_fuelActive->name);
    strcpy(g_activeState->line2, " pumping");
    g_activeState->line1[LCD_COLS] = '\0';
    g_activeState->line2[LCD_COLS] = '\0';
}    

void update_pumping()
{
    delay_ms(1);
    g_pumpedLiters+=0.04*g_pumpingRate;
    if(g_pumpedLiters>=g_fuelLitersMax)
        g_pumpedLiters = g_fuelLitersMax;
}

void setup_result()
{
    char buff[8];
    snprintf(buff,8,"%f", g_pumpedLiters * g_fuelActive->price_l);
    strcpy(g_activeState->line1, buff);
}

void state_goto_next(void* argv) {
    if(g_activeState == g_state+0) g_activeState = (State*)g_state+1; else
    if(g_activeState == g_state+1) g_activeState = (State*)g_state+2; else
    if(g_activeState == g_state+2) g_activeState = (State*)g_state+0; else
    if(g_activeState == g_state+3) g_activeState = (State*)g_state+0;
    g_activeState->setup();
}

void state_print() {
    LCD_set(LCD_CLR);

    LCD_set(LCD_LINE1);
    LCD_print(g_activeState->line1);
    LCD_set(LCD_LINE2);
    LCD_print(g_activeState->line2);
    LCD_set(LCD_LINE3);
}

int state_call_callback(char c) {
    for(size_t i = 0; i < KEYPAD_ROWS*KEYPAD_COLS; ++i)
        if(g_activeState->buttonStates[i].input == c)
        {
            g_activeState->buttonStates[i].callback(0);
            return 1;
        }
    return 0;
}
//~FSM

int main(void) {
    g_activeState = (State*)g_state;
    g_activeState->setup();
    
    while (1) {
        state_print();
            
        char c;
        do {
            c = KBD_read();
            g_activeState->update();
        }
        while(!c);
            
        state_call_callback(c);
    }
}


BOARD_SETUP void setup(void) {
    SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 10000);
    LED_setup();
    LCD_setup();
    KBD_setup();
    
    LCD_set(LCD_CLR);
    LCD_goto(0,0);
};
