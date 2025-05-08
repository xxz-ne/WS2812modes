#ifndef WS2812_H
#define WS2812_H
 
#include "main.h"
 
#define l 					30
#define h 					60     //TURN TO THE ORDER: GRB
#define NUM   			60
#define RGB_BIT 		24
#define Maxlight    180    //呼吸灯亮度上限；
#define step        3
#define R_light     180    //常亮亮度；
#define G_light     180 
#define B_light     180 

void WS2812_setoneled(uint16_t order, uint8_t R, uint8_t G, uint8_t B);
void WS2812_Allsetcolor(uint8_t R, uint8_t G, uint8_t B);
void WS2812_START(void);
void WS2812_TurnOff(void);
void WS2812_Breathset(uint8_t flowflag);

// 报错：变量放在 .c 文件中定义，头文件中用extern声明，否则调用时重复定义；
extern uint8_t flow_flag;
extern uint8_t flow_light;

float mysin(float x);

#endif

