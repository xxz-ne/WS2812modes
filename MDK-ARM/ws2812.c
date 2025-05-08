#include "ws2812.h"
#include "tim.h"

#define Resettime 80          //	per-circle's first 80*1.25=100ns is used to reset;
						//扔掉初始一段时间的莫名乱序杂波，且传输完以后要及时reset更新颜色，否则颜色延迟一次；
#define DataNum 80+24*NUM+80
uint16_t txbuff[DataNum]={0}; 
uint16_t* txdata=&txbuff[Resettime];
uint16_t order=0;
uint8_t flow_flag=0;
uint8_t flow_light=0;

uint8_t direction=1;

void WS2812_Allsetcolor(uint8_t R, uint8_t G, uint8_t B)
{
		for(order=0;order<NUM;order++)
		{
			WS2812_setoneled(order, R, G, B);
		}
		WS2812_START();
}									 			

void WS2812_setoneled(uint16_t order, uint8_t R, uint8_t G, uint8_t B)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		txdata[24*order+7-i]=(G & 0x01) ? h : l ;
		G=G>>1;
		txdata[24*order+15-i]=(R & 0x01) ? h : l ;
		R=R>>1;
		txdata[24*order+23-i]=(B & 0x01) ? h : l ;
		B=B>>1;
	}
}

void WS2812_START()
{
  HAL_TIM_PWM_Start_DMA(&htim1,TIM_CHANNEL_2,(uint32_t *)txbuff, DataNum); 
	// 修改时没有跟着变数组大小导致乱了时序
}

void WS2812_TurnOff(void)
{
	for(order=0;order<NUM*24;order++)
	{
		txdata[order]=l;
	}
	WS2812_START(); 
}

void WS2812_Breathset(uint8_t flow_flag)
{

	if(flow_flag) 
		{
			if(flow_flag==1) WS2812_Allsetcolor(flow_light,0,0);
	    else if(flow_flag==2) WS2812_Allsetcolor(0,0,flow_light);
			
			if(flow_light <= 0) direction=1; 
			if(flow_light >= Maxlight) direction=-1; 
			flow_light=(flow_light+direction*step);
			HAL_Delay(100);
		}
  
}


//float mysin(float x) 
//{
//    float term = x; // 第一项是 x
//    float sin_x = 0.0; // sin(x)的累加结果
//		int n=5;
//    for (int i = 1; i <= n; i++) {
//        sin_x += term; // 累加当前项
//        term *= -x * x / ((2 * i) * (2 * i + 1)); // 计算下一项
//    }
//    return sin_x;
//}

