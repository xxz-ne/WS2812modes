#include "mode.h"

extern uint8_t mode_flag;
void System_ResetCount_Update(void) {
    uint32_t reset_count;
    // 读取当前的重启次数
    reset_count = *(__IO uint32_t*)FLASH_PAGE_ADDRESS;
    if (reset_count == 0xFFFFFFFF) {
        reset_count = 0;  // 如果是初次写入，初始化为 0
    }
    
    // 条件增加计数
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==GPIO_PIN_SET) reset_count++;
    
		if( reset_count >=5) reset_count = 0;
    // 解锁 Flash
    HAL_FLASH_Unlock();
    
    // 擦除指定扇区
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = FLASH_PAGE_ADDRESS;
    EraseInitStruct.NbPages = 1;
    HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
    
    // 写入新的重启次数
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_PAGE_ADDRESS, reset_count);
    
    // 锁定 Flash
    HAL_FLASH_Lock();
}

uint32_t System_ResetCount_Get(void) {
    // 读取当前的重启次数
    return *(__IO uint32_t*)FLASH_PAGE_ADDRESS;
}

void Mode_work(uint32_t reset_count)
{
	  switch(reset_count){
			case 1:
				WS2812_Allsetcolor(R_light,0,0);
			  break;
			case 2:
				flow_flag=1;
			  break;
			case 3: 
				WS2812_Allsetcolor(0,0,B_light);
				break;
			case 4:
				flow_flag=2;
				break;
			default: 
        WS2812_TurnOff();
    }
}
