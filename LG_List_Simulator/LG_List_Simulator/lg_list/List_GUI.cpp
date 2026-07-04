/*
 * List_GUI.c
 *
 *  Created on: 2022��6��4��
 *      Author: nisag
 */

#include "List_GUI.h"



#include <stdint.h>
#include "List_GUI_Config.h"
#include "List_GUI_Tools.h"


const char Icon_Radio_Selected[]	 = {	0x08, 0x08, 0x3C, 0x42, 0xBD, 0xBD, 0xBD, 0xBD, 0x42, 0x3C};
const char Icon_Radio_Unselected[]  = {	0x08, 0x08, 0x3C, 0x42, 0xA5, 0x89, 0x91, 0xA5, 0x42, 0x3C};
const char Icon_Combox_Selected[]	 = {	0x08, 0x08, 0xFF, 0x81, 0xBD, 0xBD, 0xBD, 0xBD, 0x81, 0xFF};
const char Icon_Combox_Unselected[] = {	0x08, 0x08, 0xFF, 0x81, 0xA5, 0x89, 0x91, 0xA5, 0x81, 0xFF};

void n_MoveItem(LG_DIR dir, lg_item_t* fatherItem);
void lg_load(lg_item_t* root);
lg_item_t* n_get_tail(lg_item_t* item);

static lg_item_t* dS_CurrentItem;/*current hover item that you can see*/
static lg_item_t* dS_WinItem;/*first item in the window you can see*/
static LG_Event_Type dS_BtnVal;
static uint8_t		u8S_Cnt;
static uint8_t		u8S_DispBusy = 0;

void n_SetCurrentItem(lg_item_t* dI_Item){
	u8S_DispBusy++;
	dS_CurrentItem = dI_Item;
	u8S_DispBusy--;
}
lg_item_t* n_GetCurrentItem(){
	return dS_CurrentItem;
}
void n_SetWinItem(lg_item_t* dI_Item){
	u8S_DispBusy++;
	dS_WinItem = dI_Item;
	u8S_DispBusy--;
}
lg_item_t* n_GetWinItem(){
	return dS_WinItem;
}

uint16_t lg_unilen(char* str){
	u8S_DispBusy++;
	uint16_t* u16T_Temp = (uint16_t*)str;
	uint16_t u16O_Ret = 0;
	while('\0' != *u16T_Temp){
		u16T_Temp++;
		u16O_Ret = u16O_Ret + 2;
	}
	u8S_DispBusy--;
	return u16O_Ret;
}

lg_item_t* lg_item_create(lg_item_t* father, const char* content){
	lg_item_t* newItem;
	lg_item_t* lastItem;
	int i = 0;

	newItem	= (lg_item_t*)lg_malloc(sizeof(lg_item_t));
	if (NULL == newItem) {
		return NULL;
	}
	u8S_DispBusy++;
	/*first node*/
	newItem->father 		= father;
	newItem->children		= NULL;
	newItem->Last			= NULL;
	newItem->Next			= NULL;
	newItem->info			= NULL;
	newItem->WinPos			= 0;	
	newItem->RelativePos	= 0;
	newItem->AbsolutePos	= 0;

	if(NULL != content){
		newItem->content = (char*)lg_malloc(lg_strlen(content) + 2);
		if (0 != newItem->content) {
			lg_memset(newItem->content, '\0', lg_strlen(content) + 2);
			lg_strcpy(newItem->content, content, lg_strlen(content));
		}
		//newItem->content = (char*)lg_malloc(2*lg_strlen(content)+2);
		//lg_memset(newItem->content, '\0', 2*lg_strlen(content)+2);
		//utf8ToUnicode(content, (unsigned short*)newItem->content, 2*lg_strlen(content)+2);/*IDE use utf8*/
	}else{
		newItem->content		= NULL;
	}
	newItem->status			= false;	
	newItem->type			= LG_TYPE_NORMAL;
	newItem->cb				= NULL;

	if(NULL == father){
		newItem->Last			= NULL;
	}else{
		if(NULL == father->children){
			/*first child*/
			father->children 	= newItem;
		}else{
			lastItem			= (lg_item_t*)father->children;
			lastItem 			= n_get_tail(lastItem);
			lastItem->Next 		= newItem;
			newItem->Last		= lastItem;
		}
	}
	u8S_DispBusy--;
	return newItem;
}

lg_item_t* lg_radio_create(lg_item_t* father, const char* content) {
	lg_item_t* ret = lg_item_create(father, content);
	ret->type = LG_TYPE_RADIO;
	return ret;
}

lg_item_t* n_get_tail(lg_item_t* item){
	lg_item_t* tailItem = item;
	u8S_DispBusy++;
	if(NULL == item){
		u8S_DispBusy--;
		return NULL;
	}
	while(NULL != tailItem->Next){
		tailItem = (lg_item_t*)tailItem->Next;
	}
	u8S_DispBusy--;
	return tailItem;
}
lg_item_t* n_get_first(lg_item_t* item){
	lg_item_t* firstItem = item;
	u8S_DispBusy++;
	if(NULL == item){
		u8S_DispBusy--;
		return NULL;
	}
	while(NULL != firstItem->Last){
		firstItem = (lg_item_t*)firstItem->Last;
	}
	u8S_DispBusy--;
	return item;
}
/**
 * param: item: first item
 */
uint16_t n_item_counts(lg_item_t* item){
	uint16_t u16O_Counts = 1;
	lg_item_t* tailItem = item;
	u8S_DispBusy++;
	if(NULL == item){
		u8S_DispBusy--;
		return 0;
	}
	while(NULL != tailItem->Next){
		tailItem = (lg_item_t*)tailItem->Next;
		u16O_Counts++;
	}
	u8S_DispBusy--;
	return u16O_Counts;
}
lg_item_t* n_getItemByAbsolutePos(lg_item_t* item, uint16_t pos){
	uint16_t u16O_Counts = 1;
	lg_item_t* dO_Item;
	dO_Item = n_get_first(item);
	u8S_DispBusy++;
	if(NULL == item){
		u8S_DispBusy--;
		return NULL;
	}
	if(pos+1 > n_item_counts(item)){
		u8S_DispBusy--;
		return NULL;
	}
	while(pos-- > 0){
		dO_Item = (lg_item_t*)dO_Item->Next;
	}
	u8S_DispBusy--;
	return dO_Item;
}
lg_item_t* n_getItemByRelativePos(lg_item_t* winItem, uint16_t pos){
	uint16_t u16O_Counts = 1;
	lg_item_t* dO_Item = winItem;
	u8S_DispBusy++;
	if(NULL == winItem){
		u8S_DispBusy--;
		return NULL;
	}
	if(pos+1 > MAX_ITEM_NUM){
		u8S_DispBusy--;
		return NULL;
	}
	while(pos-- > 0){
		dO_Item = (lg_item_t*)dO_Item->Next;
	}
	u8S_DispBusy--;
	return dO_Item;
}
void lg_delete_item(lg_item_t* item){
	lg_item_t* last	   = item;
	lg_item_t* tail	   = n_get_tail(item);
	lg_item_t* dT_Item;
	u8S_DispBusy++;
	//Serial.println("lg_delete_item 1");
	while(NULL != tail){
		if(NULL == tail->children){
			//Serial.println("lg_delete_item 2");
			if(NULL != tail->Last){
				last = (lg_item_t*)tail->Last;
				last->Next = NULL;
			}else{
				if(NULL != tail->father){
					dT_Item = (lg_item_t*)tail->father;
					dT_Item->children = NULL;
				}
			}
			//Serial.println("lg_delete_item 3");
			if(NULL != tail->content){
				//Serial.println("lg_delete_item 4");
				lg_free(tail->content);
				//Serial.println("lg_delete_item 5");
			}
			if(NULL != tail->info){
				//Serial.println("lg_delete_item 6");
				lg_free(tail->info);
				//Serial.println("lg_delete_item 7");
			}
			lg_free(tail);
		}else{
			lg_delete_item((lg_item_t*)tail->children);
			continue;
		}
		if(tail != item){
			tail = n_get_tail(item);
		}else{
			break;
		}
	}
	u8S_DispBusy--;
}
void lg_delete_children(lg_item_t* item){
	lg_item_t* tail	   = n_get_tail((lg_item_t*)item->children);
	u8S_DispBusy++;
	while(NULL != tail){
		lg_delete_item(tail);
		tail = n_get_tail((lg_item_t*)item->children);
	}
	item->WinPos		= 0;
	item->RelativePos	= 0;
	item->AbsolutePos	= 0;

	u8S_DispBusy--;
}

void n_DefaultActionCb(LG_Cb_ParamDef* arg){
	lg_item_t* dT_CurrentItem;
	lg_item_t* dT_Item;
	uint8_t	u8I_ClickCnt;
	u8S_DispBusy++;
	dT_CurrentItem = n_GetCurrentItem();
	if(NULL != dT_CurrentItem->cb){
		if(false == dT_CurrentItem->cb(arg)){
			u8S_DispBusy--;
			return;
		}
	}
	switch(arg->type){
	case LG_ITEM_A_CLICK:{
		n_MoveItem(LG_DIR_UP, (lg_item_t*)dT_CurrentItem->father);
	}
		break;
	case LG_ITEM_A_LONGPRESS:{
		dT_Item	= (lg_item_t*)dT_CurrentItem->father;
		if(NULL != dT_Item->father){/*back to last menu*/
			dT_Item = (lg_item_t*)dT_Item->father;
			lg_load(dT_Item);
		}else{/*load root menu*/
			lg_load(dT_Item);
		}
	}
		break;
	case LG_ITEM_B_CLICK:{
		n_MoveItem(LG_DIR_DOWN, (lg_item_t*)dT_CurrentItem->father);
	}
		break;
	case LG_ITEM_B_LONGPRESS:{
		//lg_load(n_getItemByRelativePos(n_GetWinItem(), dT_CurrentItem->RelativePos));
		lg_load(n_GetCurrentItem());
	}
		break;
	case LG_ITEM_OK_CLICK:{
		u8I_ClickCnt	= u8S_Cnt;
		if(1 == u8I_ClickCnt){
			lg_load(n_GetCurrentItem());
		}
	}
		break;
	case LG_ITEM_OK_LONGPRESS:{
		dT_Item	= (lg_item_t*)dT_CurrentItem->father;
		if(NULL != dT_Item->father){/*back to last menu*/
			dT_Item = (lg_item_t*)dT_Item->father;
			lg_load(dT_Item);
		}else{/*load root menu*/
			lg_load(dT_Item);
		}
	}
		break;
	default:break;
	}
	u8S_DispBusy--;
}

/**
 * look items through father's eyes
 */
void n_MoveItem(LG_DIR dir, lg_item_t* fatherItem){
	uint16_t u16T_I = 0,u16T_J = 0;
	lg_item_t* dT_item;
	u8S_DispBusy++;
	switch(dir){
	case LG_DIR_DOWN:{
	if(fatherItem->AbsolutePos < n_item_counts((lg_item_t*)fatherItem->children)-1){
		if(fatherItem->RelativePos < MAX_ITEM_NUM-1){
			fatherItem->RelativePos++;
		}else{
			fatherItem->WinPos++;
		}
		fatherItem->AbsolutePos++;
	}
	}break;
	case LG_DIR_UP:{
	if(fatherItem->AbsolutePos > 0){
		if(fatherItem->RelativePos > 0){
			fatherItem->RelativePos--;
		}else{
			fatherItem->WinPos--;
		}
		fatherItem->AbsolutePos--;
	}
	}break;
	default:break;
	}
	n_SetCurrentItem(n_getItemByAbsolutePos((lg_item_t*)fatherItem->children, fatherItem->AbsolutePos));
	n_SetWinItem(n_getItemByAbsolutePos((lg_item_t*)fatherItem->children, fatherItem->WinPos));
	/*下面专门用于readerItem*/
	dT_item	= n_getItemByRelativePos(n_GetWinItem(), u16T_I);
	if(LG_TYPE_READERITEM != dT_item->type){
		LGTools.pf_ClearTextArea();
	}
	/*上面专门用于readerItem*/
	u16T_I = 0;
	u16T_J = (n_item_counts((lg_item_t*)fatherItem->children)>MAX_ITEM_NUM)?MAX_ITEM_NUM:n_item_counts((lg_item_t*)fatherItem->children);
	while(u16T_I < u16T_J){
		dT_item	= n_getItemByRelativePos(n_GetWinItem(), u16T_I);
		if(NULL != dT_item->content){
			switch(dT_item->type){
			case LG_TYPE_NORMAL:{
				/*show normal list item*/
				LGTools.pf_dispHzFromSD(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y, TEXTAREA_POS_X, dT_item->content);
				if(u16T_I == fatherItem->RelativePos){
					LGTools.pf_ReverseRect(TEXTAREA_POS_Y+(fatherItem->RelativePos)*ITEM_SIZE_Y, TEXTAREA_POS_X, ITEM_SIZE_Y, ITEM_SIZE_X);
				}
			}break;
			case LG_TYPE_NOSELECTED:{
				/*show normal list item*/
				LGTools.pf_dispHzFromSD(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y, TEXTAREA_POS_X, dT_item->content);
			}break;
			case LG_TYPE_RADIO:{
				/*show radio list item*/
				if(true == dT_item->status){/*selected*/
					LGTools.pf_loadBitIconFromFlash(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y+(ITEM_SIZE_Y-8)/2, TEXTAREA_POS_X, Icon_Radio_Selected);
				}else{/*unselected*/
					LGTools.pf_loadBitIconFromFlash(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y+(ITEM_SIZE_Y-8)/2, TEXTAREA_POS_X, Icon_Radio_Unselected);
				}
				LGTools.pf_dispHzFromSD(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y, TEXTAREA_POS_X+8, dT_item->content);
				if(u16T_I == fatherItem->RelativePos){
					LGTools.pf_ReverseRect(TEXTAREA_POS_Y+(fatherItem->RelativePos)*ITEM_SIZE_Y, TEXTAREA_POS_X, ITEM_SIZE_Y, ITEM_SIZE_X);
				}
			}break;
			case LG_TYPE_COMBOX:{
				/*show combox list item*/
				if(true == dT_item->status){/*selected*/
					LGTools.pf_loadBitIconFromFlash(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y+(ITEM_SIZE_Y-8)/2, TEXTAREA_POS_X, Icon_Combox_Selected);
				}else{/*unselected*/
					LGTools.pf_loadBitIconFromFlash(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y+(ITEM_SIZE_Y-8)/2, TEXTAREA_POS_X, Icon_Combox_Unselected);
				}
				LGTools.pf_dispHzFromSD(TEXTAREA_POS_Y+u16T_I*ITEM_SIZE_Y, TEXTAREA_POS_X+8, dT_item->content);
				if(u16T_I == fatherItem->RelativePos){
					LGTools.pf_ReverseRect(TEXTAREA_POS_Y+(fatherItem->RelativePos)*ITEM_SIZE_Y, TEXTAREA_POS_X, ITEM_SIZE_Y, ITEM_SIZE_X);
				}
			}break;
			case LG_TYPE_READERITEM:{
				
			}break;
			default:break;
			}

		}
		u16T_I++;
	}
	u8S_DispBusy--;
}

void lg_load(lg_item_t* root){
	lg_item_t* item ;//= n_GetCurrentItem();
	u8S_DispBusy++;
	if(root != NULL){
		if(NULL != root->children){/*root node*/
//			os_printf("lg_load: %s\n", root->content);
			n_SetCurrentItem((lg_item_t*)root->children);
			n_SetWinItem((lg_item_t*)root->children);

			item = n_GetCurrentItem();
//			os_printf("lg_load %s\n", item->content);
//			os_printf("lg_load %d\n", n_item_counts(root->children));
			n_MoveItem(LG_DIR_NONE, root);
		}
	}
	u8S_DispBusy--;
}

void lg_SetBtnVal(LG_Event_Type dI_Val, uint8_t u8I_Cnt){
	dS_BtnVal	= dI_Val;
	u8S_Cnt		= u8I_Cnt;
}
void lg_task_handler(){
	lg_item_t* item = n_GetCurrentItem();
	static LG_Cb_ParamDef par;
	//Serial.println("lg_task_handler 0");
	if(LG_ITEM_NONE != dS_BtnVal){
		//Serial.println("lg_task_handler 1");
		par.type	= dS_BtnVal;
		par.param	= &u8S_Cnt;
		par.self	= item;

		dS_BtnVal	= LG_ITEM_NONE;
//		u8S_Cnt		= 0;
		n_DefaultActionCb(&par);
	}
}

lg_item_t* lg_current_item(){
	return n_GetCurrentItem();
}
