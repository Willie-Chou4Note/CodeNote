/*
 * Flash_WL.c
 *
 *  Created on: Oct 7, 2024
 *      Author: PEGA_User
 */

#include "Flash_WL.h"

extern void FLASH_PageErase(uint32_t Banks, uint32_t Page);
//extern FLASH_ProcessTypeDef pFlash;
extern uint8_t BD_Mode;
extern uint8_t EMS_Level;
extern __IO uint8_t EE_flag;

/* initialize all param */
static flasher_t flasher = newFlasher(FLASH_START_ADDRESS, PAGE_SIZE*PAGE_NUMBER);
static flash_pack_u buff = {.data_quarter = {0x5A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA5}}; // init the write buffer
static flash_pack_u check_buff = {0x00}; // init the check buffer

uint8_t WriteErrorCount = 0;
/**
  * @brief  erase the entire page and wait the operation finish ...
  * @param  None
  * @retval None
  */
void erase_flash(void)
{
	HAL_FLASH_Unlock();

	for (int idx = PAGE_START_INDEX; idx <= PAGE_END_INDEX; idx++)
	{
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_PGAERR | FLASH_SR_OPERR);
					//Eed of Operation | Write Protection Error | Programming Sequence Error | Programming Alignment Error | operation error
		FLASH_PageErase(USELESS_BANK1, idx); // the first param is useless (for 1 bank case)
		FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE); // if flash operation execute more than 1 sec, return error

		/* If operation is completed or interrupted, disable the Page Erase Bit */
		CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
	}
	HAL_FLASH_Lock();
}

/**
  * @brief  go through the entire page, to build the flasher structure.
  * @param  None
  * @retval None
  */

uint32_t find_used_entry(void)
{
	//check if to use the flash storage first time.
	flasher.buff.data = read_Dbword_from_flash(flasher.start_addr);
	if (flasher.buff.data_quarter[0] == 0xFF) return 0;

	//search pattern /0x5A....0xA5/ algorithm
	uint32_t left_addr = flasher.start_addr;
	uint32_t right_addr = flasher.start_addr + flasher.page_size;
	uint32_t mid_addr = 0;
	while(left_addr < right_addr) {
		mid_addr = (left_addr + right_addr) / 2;
		flasher.buff.data = read_Dbword_from_flash(mid_addr);
		if (flasher.buff.data_quarter[0] == 0x00) left_addr = mid_addr;
		else if (flasher.buff.data_quarter[0] == 0xFF) right_addr = mid_addr;
		else break;
	}

	if (flasher.buff.data_quarter[0] == 0x5A && flasher.buff.data_quarter[7] == 0xA5) { // if data is valid
		flasher.cur_addr = mid_addr;
		flasher.new_addr = mid_addr + EE_ELEMENT_SIZE;
		return mid_addr;

	} else if (flasher.buff.data != 0x00 && flasher.buff.data_quarter[7] == 0x00) { // if page broken flag has been set
		flasher.cur_addr = 0;
		flasher.new_addr = 0;
		EE_flag = 1;
//		return 1;
	}
	return 0; // if no found
}

/**
  * @brief  write the format and data into element of page, and set previous element to all 0 (0x00 00 00 00 00 00 00 00).
  * @param  writer contain the format | 0x5A | (optional) | (optional) | data1 | data2 | (optional) | (optional) | 0xA5 | total 8 bytes
  * @retval None
  */
void write_Dbword_to_flash(void)
{

	if ( flasher.cur_addr != 0 ) {
		flasher.buff.data = read_Dbword_from_flash(flasher.cur_addr);
	}

	/* check if data updated needed */
	if ( (BD_Mode ^ flasher.buff.data_quarter[3]) || (EMS_Level ^ flasher.buff.data_quarter[4]) )
	{
		if ( flasher.new_addr >= flasher.start_addr + flasher.page_size) {
			flasher.new_addr = flasher.start_addr;
			erase_flash();
			check_buff.data = read_Dbword_from_flash(flasher.start_addr);
			if (check_buff.data_quarter[0] != 0xFF) {
				flasher.new_addr = 0;
				flasher.cur_addr = 0;
				EE_flag = 1;
				return;
			}
		}

		buff.data_quarter[3] = BD_Mode;
		buff.data_quarter[4] = EMS_Level;

		HAL_FLASH_Unlock();

		if ( (flasher.cur_addr >= flasher.start_addr) && (flasher.cur_addr != (flasher.start_addr + flasher.page_size - EE_ELEMENT_SIZE)) ) {
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flasher.cur_addr, 0x00);
		}

		/* check if data was updated */
		for (WriteErrorCount = 0; WriteErrorCount < 3; WriteErrorCount++) {
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flasher.new_addr, buff.data);

			flasher.buff.data = read_Dbword_from_flash(flasher.new_addr);

			/*hand check if the write process is actually successful (flash w/r endurance), if page broken, disable EEPROM*/
			if ( flasher.buff.data == buff.data ) {
				WriteErrorCount = 0;
				break;
			}
		}

		if (WriteErrorCount >= 3) {
			buff.data_quarter[7] = 0x00;
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flasher.new_addr, buff.data);
			flasher.new_addr = 0;
			flasher.cur_addr = 0;
			EE_flag = 1;
		} else {
			flasher.cur_addr = flasher.new_addr;
			flasher.new_addr += EE_ELEMENT_SIZE;
		}

		HAL_FLASH_Lock();
	}

}

uint64_t read_Dbword_from_flash(uint32_t target_addr)
{
//	flasher.buff.data = *(uint64_t* )target_addr;
//	return flasher.buff.data;
	return *(uint64_t* )target_addr;
}