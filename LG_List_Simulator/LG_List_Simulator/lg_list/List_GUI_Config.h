/*
 * List_GUI_Config.h
 *
 *  Created on: 2022��6��5��
 *      Author: nisag
 */

#ifndef APP_INCLUDE_PUBLIC_LIST_GUI_LIST_GUI_CONFIG_H_
#define APP_INCLUDE_PUBLIC_LIST_GUI_LIST_GUI_CONFIG_H_

#define CRAPHICS_DEVICE_SCREENSIZE_X (160U)
#define CRAPHICS_DEVICE_SCREENSIZE_Y (128)

#define LIST_GUI_FLASH_HANZI_ADDR_BEGAN	(0U)

#define COLOR_BITS_32				 (32U)
#define COLOR_BITS_16				 (16U)
#define COLOR_BITS_1				 (1U)
#define COLOR_BITS					 COLOR_BITS_32
#if COLOR_BITS == COLOR_BITS_32
	#define COLOR_SET	(0X00000000U) //黑色
	#define COLOR_CLR	(0X00FFFFFFU) //白色
#elif COLOR_BITS == COLOR_BITS_16
	#define COLOR_SET	(0X0000U) //黑色
	#define COLOR_CLR	(0XFFFFU) //白色
#elif COLOR_BITS == COLOR_BITS_1
	#define COLOR_SET	(1U) //黑色
	#define COLOR_CLR	(0U) //白色
#endif

#define TEXTAREA_POS_Y (16U)
#define TEXTAREA_POS_X (0U)
#define TEXTAREA_SIZE_Y (CRAPHICS_DEVICE_SCREENSIZE_Y-TEXTAREA_POS_Y)
#define TEXTAREA_SIZE_X (CRAPHICS_DEVICE_SCREENSIZE_X)

#define MENUBAR_POS_Y (0U)
#define MENUBAR_POS_X (0U)
#define MENUBAR_SIZE_Y (TEXTAREA_POS_Y)
#define MENUBAR_SIZE_X (CRAPHICS_DEVICE_SCREENSIZE_X)

#define ITEM_SIZE_Y		(16U)
#define ITEM_SIZE_X		(160U)
#define MAX_ITEM_NUM	(TEXTAREA_SIZE_Y/ITEM_SIZE_Y)


#define USE_CHINESE		(1U)

#define SUB_HZ_STACK_150  (150U)
#define SUB_HZ_STACK_1000 (1000U)
#define SUB_HZ_STACK_3000 (3000U)
#define SUB_HZ_STACK_5000 (5000U)
#define SUB_HZ_STACK_ALL  (0U)
#define SUB_HZ_STACK_SIZE SUB_HZ_STACK_ALL

#if USE_CHINESE == 1
	#if SUB_HZ_STACK_SIZE == SUB_HZ_STACK_150
		#include "./font/SubHZStack150.h"
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_1000
		#include "./font/SubHZStack1000.h"
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_3000
		#include "./font/SubHZStack3000.h"
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_5000
		#include "./font/SubHZStack5000.h"
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_ALL
		#include "./font/SubHZStack_all.h"
	#endif
#endif
	


#define LG_MEM_CUSTOM     1
#if LG_MEM_CUSTOM == 0

#else       /*LV_MEM_CUSTOM*/

#include <stdlib.h>
#include <string.h>

#if 0
	#define lg_malloc(x)	os_malloc(x)
	#define lg_free(x)		os_free(x)
	#define lg_strlen(x)	os_strlen(x)
//	#define lg_unilen(x)
	#define lg_strcpy(des, src, len)	os_memcpy(des, src, len)
	#define lg_memset(des, cont,len)	os_memset(des, cont,len)
#else
	#define lg_malloc(x)	malloc(x)
	#define lg_free(x)		free(x)
	#define lg_strlen(x)	strlen(x)
	//	#define lg_unilen(x)
	#define lg_strcpy(des, src, len)	memcpy(des, src, len)
	#define lg_memset(des, cont,len)	memset(des, cont,len)
#endif
#endif

#endif /* APP_INCLUDE_PUBLIC_LIST_GUI_LIST_GUI_CONFIG_H_ */
