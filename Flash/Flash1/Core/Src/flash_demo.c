/*
 * flash_demo.c
 * This demonstration shows how to write data into the STM32L412 MCU's Flash.
 * It supports writing a single 8 byte Word at a time. This is just a
 * demonstration project with basic functionality, and many limitations.
 * Properties:
 * Reading operation reads a single 4 byte word at a time.
 * Page Erase size is 2K Bytes.
 * Writing data can only be performed on erased memory cells (bytes with 0xFF).
 * Only 1st memory Bank is supported (addresses 0x0 - 0x0801FFFF)
 *
 * Note! Do not Erase or Write data to flash pages overlapping
 *       your code memory regions!
 *
 *  Created on: Dec 22, 2024
 *      Author: Alon Boyarski
 */

#include "flash.h"


int8_t flash_example()
{
    /* Flash Address of data to write */
	uint32_t Address = ADDR_FLASH_PAGE_16;
  	//uint32_t Address = ADDR_FLASH_PAGE_16 + 8;
  	//uint32_t Address = ADDR_FLASH_PAGE_16 + 16;
    /* 64bit Word to be written */
	uint64_t WriteWord = 0x1234567890ABCDEF;

	uint64_t flash_data = 0;

	/* 1. Enbele flash Write\Erase */
	FlashOperationInit();

	/* 2. Erase the 2Kbytes Page where data has to be written */
	if(FlashErasePage(Address) != HAL_OK)
	{
      return -1; //print "Page Erase error"
	}

	/* 3. Write 64Bits word  */
    if(FlashWritePage(Address, WriteWord) != HAL_OK)
    {
      return -1; //print "Page Write error"
    }

	/* 4. Disable flash Write\Erase */
	FlashOperationDeInit();

	/* 5. Read 32 bit words from the flash */
    Address += 4;
    flash_data = FlashRead(Address);
    flash_data <<= 32;
    Address -= 4;
    flash_data |= FlashRead(Address);
    if(WriteWord != flash_data)
    {
      return -1; //print "verify failed"
    }

    return 0; //Valid flash operations

}
