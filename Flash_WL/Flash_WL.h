/*
 * Flash_WL.h
 *
 *  Created on: Oct 7, 2024
 *      Author: PEGA_User
 */

#ifndef INC_FLASH_WL_H_
#define INC_FLASH_WL_H_

#include "stm32g0xx_hal.h"
#include "Uart.h"
#include "P_Dbg.h"

#if G030_64KB
#define FLASH_START_ADDRESS 		0x0800F000U 	/* page30 */
#else
#define FLASH_START_ADDRESS 		0x0801F000U 	/* page62 */
#endif
#define PAGE_NUMBER					2U				/* total use: page30, 31 */
#define EE_ELEMENT_SIZE				8U				/* size of per element */
#define PAGE_START_INDEX			(FLASH_START_ADDRESS - FLASH_BASE) / FLASH_PAGE_SIZE
#define PAGE_END_INDEX				PAGE_START_INDEX + (PAGE_NUMBER - 1U)
#define PAGE_SIZE 					FLASH_PAGE_SIZE /* size per element of page = 2Kbytes */
#define EE_BD_Mask					0xFF000000		/* position of the data */
#define EE_EMS_Mask					0xFF00000000
#define EE_BD_Pos					24U				/* mask of the data */
#define EE_EMS_Pos					32U
#define USELESS_BANK1				1


typedef union
{
	uint64_t 		data;
	uint8_t 		data_quarter[8]; // for violet case, we need to take the data of index 3, 4
}flash_pack_u;

typedef struct
{
	uint32_t 		start_addr; //should be fixed
	uint32_t 		cur_addr;
	uint32_t 		new_addr;	//address of not used element
	uint16_t 		page_size;  //total page size
	flash_pack_u 	buff;		//to store data format
}flasher_t;

#define newFlasher(start_addr, page_size) \
		{start_addr, 0, start_addr, page_size, {0}}
//		{start_addr, start_addr, start_addr, page_size, {0}}

/* the data we want to write into flash, and data size can be 8 bits to 48 bits, its up to your design ...*/
//typedef union
//{
//	uint8_t 		w_data8[2];
//	uint16_t 		w_data16;
//}writer_u;



void erase_flash(void);
void find_new_entry(void);
uint32_t find_used_entry(void);
void write_Dbword_to_flash(void);
uint64_t read_Dbword_from_flash(uint32_t target_addr);

#endif /* INC_FLASH_WL_H_ */
