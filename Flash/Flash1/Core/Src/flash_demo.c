/*
 * flash_demo.c
 *
 *  Created on: Dec 22, 2024
 *      Author: pc
 */

#include "flash.h"


int8_t flash_example()
{
	uint64_t flash_data = 0;
  	extern uint32_t Address;

	/* 1. Enbele flash Write\Erase */
	FlashOperationInit();

	/* 2. Erase the 2Kbytes Page where data has to be written */
	if(FlashErasePage() != HAL_OK)
	{
      return -1; //print "Page Erase error"
	}

	/* 3. Write 64Bits word  */
    if(FlashWritePage() != HAL_OK)
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


    return 0; //Valid flash operations

}
