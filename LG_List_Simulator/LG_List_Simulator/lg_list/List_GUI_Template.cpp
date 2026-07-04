
#include "List_GUI_Tools.h"
#include "../LG_List_Simulator.h"



void a_list_gui_drawPoint(uint16_t y, uint16_t x, int color);
void a_list_gui_fastDrawPoint(uint16_t y, uint16_t x, int color);
void a_list_gui_repaint();
void a_list_gui_sdcardRead(const char* filePath, int offset, int len, char* s8O_OutData);
void a_list_gui_FlashRead(int addr, int len, char* s8O_OutData);


void a_list_gui_drawPoint(uint16_t y, uint16_t x, int color) {
	simulator_screen_draw_point(x, y, color);
}

void a_list_gui_fastDrawPoint(uint16_t y, uint16_t x, int color) {
	simulator_screen_draw_point(x, y, color);
	//simulator_screen_repaint();
}
void a_list_gui_repaint() {
	simulator_screen_repaint();
}
void a_list_gui_sdcardRead(const char* filePath, int offset, int len, char* s8O_OutData) {

}

/********
********* @brief
* ******* len: bytes number need to be read
* *******
*/
void a_list_gui_FlashRead(int addr, int len, char* s8O_OutData) {

}