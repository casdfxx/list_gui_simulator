#ifndef _LIST_GUI_H_
#define _LIST_GUI_H_

#include <stdint.h>
#include <stdbool.h>
#include "List_GUI_Config.h"
#include "List_GUI_Tools.h"

#ifndef bl
	#define bl bool
#endif

typedef enum LG_Event_TypeDef {
	//LG_ITEM_IN		= 0,
	//LG_ITEM_OUT,
	LG_ITEM_NONE = 0,
	LG_ITEM_A_CLICK = 1,
	LG_ITEM_A_LONGPRESS = 2,
	LG_ITEM_B_CLICK = 4,
	LG_ITEM_B_LONGPRESS = 8,
	LG_ITEM_OK_CLICK = 16,
	LG_ITEM_OK_LONGPRESS = 32,
	LG_ITEM_OK_LONGHOLD = 64,
}LG_Event_Type;

typedef struct LG_Cb_ParamDef {
	LG_Event_Type type;
	void* param;
	void* self;
}LG_Cb_ParamDef;

typedef enum LG_Type_TypeDef {
	LG_TYPE_NORMAL = 0,	/*add nothing to the head of item*/
	LG_TYPE_RADIO = 1,	/*add radio  icon to the head of item*/
	LG_TYPE_COMBOX = 2,	/*add combox icon to the head of item*/
	LG_TYPE_NOSELECTED = 3,
	LG_TYPE_READERITEM = 4,	/*不显示*/
}LG_Type;

typedef struct LG_ItemDef {
	void* father;
	void* children;
	void* Last;
	void* Next;
	void* info;

	uint16_t 	WinPos;
	uint16_t	RelativePos;
	uint16_t	AbsolutePos;
	char* content;
	bl	  		status;//true=selected
	LG_Type		type;
	bl(*cb)(LG_Cb_ParamDef* arg);
}lg_item_t;

void lg_load(lg_item_t* root);
void lg_task_handler();
lg_item_t* lg_item_create(lg_item_t* father, const char* content);
lg_item_t* lg_radio_create(lg_item_t* father, const char* content);
void lg_delete_item(lg_item_t* item);
void lg_delete_children(lg_item_t* item);
void lg_SetBtnVal(LG_Event_Type dI_Val, uint8_t u8I_Cnt);
uint16_t lg_unilen(char* str);
lg_item_t* lg_current_item();

#endif
