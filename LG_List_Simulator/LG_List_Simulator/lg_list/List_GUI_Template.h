#ifndef _LIST_GUI_TEMPLATE_H_
#define _LIST_GUI_TEMPLATE_H_

#include "List_GUI.h"

void a_list_gui_drawPoint(uint16_t y, uint16_t x, int color);
void a_list_gui_fastDrawPoint(uint16_t y, uint16_t x, int color);
void a_list_gui_repaint();
void a_list_gui_sdcardRead(const char* filePath, int offset, int len, char* s8O_OutData);
void a_list_gui_FlashRead(int addr, int len, char* s8O_OutData);

#endif

