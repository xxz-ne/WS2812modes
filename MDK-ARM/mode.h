#ifndef MODE_H
#define MODE_H
#include "main.h"
#include "ws2812.h"

#define FLASH_PAGE_ADDRESS  0x0801FC00  // 假设最后一个扇区的起始地址
//#define FLASH_PAGE_SIZE     1024        // STM32F103 的每个扇区大小为 1KB
#define mode_num 5
extern uint32_t reset_count;

void System_ResetCount_Update(void) ;
uint32_t System_ResetCount_Get(void) ;
void Mode_work(uint32_t reset_count);

#endif

