/*
 * int_flash.c
 *
 *  Created on: Dec 22, 2024
 *      Author: Alon Boyarski
 */


/* Includes ------------------------------------------------------------------*/
#include <flash.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MASK_2K 			~0x07FF //

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t PAGEError = 0;

/* Variable of type FLASH_EraseInitTypeDef */
static FLASH_EraseInitTypeDef EraseInitStruct;


/* Private function prototypes -----------------------------------------------*/


/* Public functions ---------------------------------------------------------*/
void FlashOperationInit(void)
{
  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks       = 0;
  EraseInitStruct.Page        = ADDR_FLASH_PAGE_63; //Default is the last page in the Bank
  EraseInitStruct.NbPages     = 1;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
}

void FlashOperationDeInit(void)
{
  /* Lock the Flash to disable the flash control register access *************/
  HAL_FLASH_Lock();
}

HAL_StatusTypeDef FlashErasePage(uint32_t WriteAddress)
{
  EraseInitStruct.Page = ((WriteAddress & MASK_2K) - ADDR_FLASH_PAGE_0) >> 11;
  return HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
}

HAL_StatusTypeDef FlashWritePage(uint32_t WriteAddress, uint64_t WriteWord)
{
  return HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddress, WriteWord);
}

uint32_t FlashRead(uint32_t ReadAddress)
{
	uint32_t DataRead = *(uint32_t*)ReadAddress;
	return DataRead;
}

