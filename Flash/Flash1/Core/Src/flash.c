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
//#define FLASH_ADDRESS           ADDR_FLASH_PAGE_16   /* Start @ of user Flash area */
//#define DATA_64                 ((uint64_t)0x12345678ABCDEFGH)
//#define DATA_32                 ((uint32_t)0x12345678)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t FirstPage = 16;
//uint32_t NbOfPages = 0;
//uint32_t BankNumber = 0;
uint32_t Address = FLASH_ADDRESS;
uint32_t PAGEError = 0;
//__IO uint32_t data32 = 0;
//__IO uint32_t MemoryProgramStatus = 0;

/* Variable of type FLASH_EraseInitTypeDef */
static FLASH_EraseInitTypeDef EraseInitStruct;


/* Private function prototypes -----------------------------------------------*/


/* Public functions ---------------------------------------------------------*/
void FlashOperationInit(void)
{
  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks       = 0;
  EraseInitStruct.Page        = FirstPage;
  EraseInitStruct.NbPages     = 1;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
}

void FlashOperationDeInit(void)
{
  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
}

HAL_StatusTypeDef FlashErasePage(void)
{
  return HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
}

HAL_StatusTypeDef FlashWritePage(void)
{
  return HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, DATA_64);
}

uint32_t FlashRead(uint32_t ReadAddress)
{
	uint32_t DataRead;
	DataRead = *(uint32_t*)ReadAddress;
	return DataRead;
}














/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
//static uint32_t GetPage(uint32_t Addr)
//{
//  uint32_t page = 0;
//
//  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
//  {
//    /* Bank 1 */
//    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
//  }
//  else
//  {
//    /* Bank 2 */
//    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
//  }
//
//  return page;
//}

/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
//static uint32_t GetBank(uint32_t Addr)
//{
//  return FLASH_BANK_1;
//}


