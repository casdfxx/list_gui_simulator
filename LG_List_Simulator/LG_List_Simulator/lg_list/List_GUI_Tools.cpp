#include "List_GUI_Tools.h"
#include "List_GUI.h"
#include "List_GUI_Template.h"

#ifndef bl
#define bl bool
#endif


void 	    x_GraphicsDeviceDrawPoint(uint16_t y, uint16_t x, int dat);
int         x_GraphicsDeviceReadPoint(uint16_t y, uint16_t x);
void 	    x_GraphicsDeviceFastDrawPoint(uint16_t y, uint16_t x, int dat);

void		n_ShowChar(uint8_t y, uint8_t x, uint8_t dat);
void		n_OLED_ShowString(uint8_t y, uint8_t x, uint8_t* dat);

void 	    n_dispHzFromSD(uint16_t y, uint16_t x, char* dat);
void 	    n_dispTextArea(const char* dat);
void 	    x_loadFullPicture(unsigned char* filePath, uint32_t pos);
void 	    x_ClearTextArea(void);
void 	    x_ClearMenuBarArea(void);
void 	    n_loadBitIcon(uint16_t charI_y, uint16_t charI_x, uint8_t* filePath);
void 	    n_loadBitIconFromFlash(uint16_t charI_y, uint16_t u8I_x, const char* content);
void 	    x_MoveRect(LG_DIR dir, int step, int y, int x, int ySize, int xSize);
void 	    x_ReverseRect(uint16_t y, uint16_t x, uint16_t ySize, uint16_t xSize);

#if COLOR_BITS == COLOR_BITS_32
static uint32_t   GDDRAM[CRAPHICS_DEVICE_SCREENSIZE_Y][CRAPHICS_DEVICE_SCREENSIZE_X];
#elif COLOR_BITS == COLOR_BITS_16
static uint16_t   GDDRAM[CRAPHICS_DEVICE_SCREENSIZE_Y][CRAPHICS_DEVICE_SCREENSIZE_X];
#elif COLOR_BITS == COLOR_BITS_1
static uint8_t   GDDRAM[CRAPHICS_DEVICE_SCREENSIZE_Y / 8][CRAPHICS_DEVICE_SCREENSIZE_X];
#endif

const unsigned char Icon_Radio_Selected[] = {
	0x08, 0x08, 0x3C, 0x42, 0xBD, 0xBD, 0xBD, 0xBD, 0x42, 0x3C
};
const unsigned char Icon_Radio_Unselected[] = {
	0x08, 0x08, 0x3C, 0x42, 0xA5, 0x89, 0x91, 0xA5, 0x42, 0x3C
};
const unsigned char Icon_Combox_Selected[] = {
	0x08, 0x08, 0xFF, 0x81, 0xBD, 0xBD, 0xBD, 0xBD, 0x81, 0xFF
};
const unsigned char Icon_Combox_Unselected[] = {
	0x08, 0x08, 0xFF, 0x81, 0xA5, 0x89, 0x91, 0xA5, 0x81, 0xFF
};

const unsigned char F6x8[] =
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
//0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
0x7E, 0x99,	0xA5, 0x9D, 0xA1, 0x7E,//@
0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _
0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
0x08, 0x08, 0x36, 0x81, 0x81, 0x81,// { 
0x14, 0x14, 0x14, 0x14, 0x14, 0x14,// horiz lines
0x81, 0x81, 0x81, 0x36, 0x08, 0x08,// } 
};
LGToolsDef LGTools;

void lg_init() {
	LGTools.pf_DrawPoint		= x_GraphicsDeviceDrawPoint;
	LGTools.pf_FastDrawPoint	= x_GraphicsDeviceFastDrawPoint;
	LGTools.pf_ReadPoint		= x_GraphicsDeviceReadPoint;

	LGTools.pf_MoveRect = x_MoveRect;
	LGTools.pf_dispHzFromSD = n_dispHzFromSD;
	LGTools.pf_dispTextArea = n_dispTextArea;
	LGTools.pf_loadFullPicture = x_loadFullPicture;
	LGTools.pf_loadBitIcon = n_loadBitIcon;
	LGTools.pf_loadBitIconFromFlash = n_loadBitIconFromFlash;
	LGTools.pf_ReverseRect = x_ReverseRect;
	LGTools.pf_ClearTextArea = x_ClearTextArea;
	LGTools.pf_ClearMenuBarArea = x_ClearMenuBarArea;
	LGTools.pf_Repaint = a_list_gui_repaint;
	LGTools.GDDRAM = &GDDRAM[0][0];

	LGTools.pf_ClearTextArea();
}

int x_GraphicsDeviceReadPoint(uint16_t y, uint16_t x) {
#if COLOR_BITS == COLOR_BITS1
	unsigned char temp = GDDRAM[y / 8][x];
	if (temp & (1 << (y % 8))) {
		return 1;
	}
	else {
		return 0;
	}
#else

#endif
	uint32_t temp = GDDRAM[y][x];
	return temp;
}

void x_GraphicsDeviceDrawPoint(uint16_t y, uint16_t x, int dat) {
	if ((y < 0) || (y >= CRAPHICS_DEVICE_SCREENSIZE_Y))
		return;
	if ((x < 0) || (x >= CRAPHICS_DEVICE_SCREENSIZE_X))
		return;
	a_list_gui_drawPoint(y, x, dat);
}

void x_GraphicsDeviceFastDrawPoint(uint16_t y, uint16_t x, int color) {
	if ((y < 0) || (y >= CRAPHICS_DEVICE_SCREENSIZE_Y))
		return;
	if ((x < 0) || (x >= CRAPHICS_DEVICE_SCREENSIZE_X))
		return;

	if (COLOR_SET == color) {
		if (COLOR_SET != x_GraphicsDeviceReadPoint(y, x)) {
			a_list_gui_fastDrawPoint(y, x, COLOR_SET);
		}
	}
	else {
		if (COLOR_SET == x_GraphicsDeviceReadPoint(y, x)) {
			a_list_gui_fastDrawPoint(y, x, COLOR_CLR);
		}
	}
}

void x_ReverseRect(uint16_t y, uint16_t x, uint16_t ySize, uint16_t xSize) {
	uint8_t u8T_y = 0;
	uint8_t u8T_x = 0;
#if 0 == 0
	/*reverse*/
	for (u8T_y = y; u8T_y < y + ySize; u8T_y++) {
		for (u8T_x = x; u8T_x < x + xSize; u8T_x++) {
			if (COLOR_CLR == x_GraphicsDeviceReadPoint(u8T_y, u8T_x)) {
				x_GraphicsDeviceFastDrawPoint(u8T_y, u8T_x, COLOR_SET);
			}
			else {
				x_GraphicsDeviceFastDrawPoint(u8T_y, u8T_x, COLOR_CLR);
			}
		}
	}
#else
	/*draw rect*/
	for (u8T_y = y; u8T_y < y + ySize; u8T_y++) {
		x_GraphicsDeviceFastDrawPoint(u8T_y, x, 1);
		x_GraphicsDeviceFastDrawPoint(u8T_y, x + xSize - 1, 1);
	}
	for (u8T_x = x; u8T_x < x + xSize - 1; u8T_x++) {
		x_GraphicsDeviceFastDrawPoint(y, u8T_x, 1);
		x_GraphicsDeviceFastDrawPoint(y + ySize - 1, u8T_x, 1);
	}
#endif

};

void x_MoveRect(LG_DIR dir, int step, int y, int x, int ySize, int xSize) {
	uint8_t u8T_y = 0;
	uint8_t u8T_x = 0;
	switch (dir) {
	case LG_DIR_UP: {
		for (u8T_y = y; u8T_y < y + ySize; u8T_y++) {
			for (u8T_x = x; u8T_x < x + xSize; u8T_x++) {
				x_GraphicsDeviceDrawPoint(u8T_y - step, u8T_x, x_GraphicsDeviceReadPoint(u8T_y, u8T_x));
				x_GraphicsDeviceDrawPoint(u8T_y, u8T_x, 0);
			}
		}
	}break;
	case LG_DIR_DOWN: {
		for (u8T_y = y + ySize; u8T_y > y; u8T_y--) {
			for (u8T_x = x; u8T_x < x + xSize; u8T_x++) {
				x_GraphicsDeviceDrawPoint(u8T_y + step, u8T_x, x_GraphicsDeviceReadPoint(u8T_y, u8T_x));
				x_GraphicsDeviceDrawPoint(u8T_y, u8T_x, 0);
			}
		}
	}break;
	case LG_DIR_LEFT: {
		for (u8T_y = y; u8T_y < y + ySize; u8T_y++) {
			for (u8T_x = x; u8T_x < x + xSize; u8T_x++) {
				x_GraphicsDeviceDrawPoint(u8T_y, u8T_x - step, x_GraphicsDeviceReadPoint(u8T_y, u8T_x));
				x_GraphicsDeviceDrawPoint(u8T_y, u8T_x, 0);
			}
		}
	}break;
	case LG_DIR_RIGHT: {
		for (u8T_y = y; u8T_y < y + ySize; u8T_y++) {
			for (u8T_x = x + xSize; u8T_x > x; u8T_x--) {
				x_GraphicsDeviceDrawPoint(u8T_y, u8T_x, x_GraphicsDeviceReadPoint(u8T_y, u8T_x - step));
				x_GraphicsDeviceDrawPoint(u8T_y, u8T_x - step, 0);
			}
		}
	}break;
	default:break;
	}
}

void dispLine16(uint8_t y, uint8_t x, uint16_t data) {
	uint8_t i = 0;
	for (i = 0; i < 16; i++) {
		x_GraphicsDeviceFastDrawPoint(y, x + i, ((0x01 & data) > 0) ? COLOR_SET : COLOR_CLR);
		data = data >> 0x01;
	}
}


void dispHz(uint16_t y, uint16_t x, uint16_t* data) {
	uint8_t i = 0;
	for (i = 0; i < 16; i++) {
		dispLine16(y + i, x, *(data + i));
	}
}



bl n_loadHzFromFlash(uint32_t c, char* dat) {
	//short c0 = c / 256;
	//short c1 = c % 256;
	//short  temp1=0, temp2=0;
	uint8_t c0		= c / 256;
	uint8_t c1		= c % 256;
	uint8_t temp1	= 0, temp2 = 0;
	
	uint32_t i = 0,k;
	uint8_t j = 0;

#if USE_CHINESE == 1
	#if SUB_HZ_STACK_SIZE == SUB_HZ_STACK_150
		const char* subHZSatck_S = subHZSatck_S150;
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_1000
		const char* subHZSatck_S = subHZSatck_S1000;
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_3000
		const char* subHZSatck_S = subHZSatck_S3000;
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_5000
		const char* subHZSatck_S = subHZSatck_S5000;
	#elif SUB_HZ_STACK_SIZE == SUB_HZ_STACK_ALL
		const char* subHZSatck_S = subHZSatck_S_all;
	#endif
#endif

	if (c0 <= 127) {
		return false;
	}
	#if SUB_HZ_STACK_SIZE != SUB_HZ_STACK_ALL
	for (i = 0; i < subHZSatck_SIZE * 34; i += 34) {
		temp1 = subHZSatck_S[i + 0];
		temp2 = subHZSatck_S[i + 1];
		//temp1 &= 0x00ff;
		//temp2 &= 0x00ff;
		if ((c0 == temp1) && (c1 == temp2)) {
		//if ((c0 == subHZSatck_S[i + 0]) && (c1 == subHZSatck_S[i + 1])) {
			for (j = 0; j < 32; j++) {
				*(dat + j) = subHZSatck_S[i + 2 + j];
			}
			return true;
		}
	}
	#else
		k = ((c0 - 0xA1) * 94 + (c1 - 0xA1)) * 32;
		for (j = 0; j < 32; j++) {
			//*(dat + j) = subHZSatck_S[k + j
			temp1 = subHZSatck_S[k + j];
			*(dat + j) = temp1;
		}
		return true;
	#endif

	
	lg_memset(dat, 0, 32);
	return false;
	//a_list_gui_FlashRead(LIST_GUI_FLASH_HANZI_ADDR_BEGAN + pos, 32, dat);
	//return true;
}

void n_dispHzFromSD(uint16_t y, uint16_t x, char* dat) {
	uint8_t i = 0;
	uint32_t k = 0;
	uint8_t* data = (uint8_t*)dat;
	uint8_t a[32];
	uint16_t* fontData;
	uint32_t free = 0;
	uint8_t c0 = 0;
	uint8_t c1 = 0;

	
	while (*(data) != 0) {
		//k = (*(data)) * 32;
		c0 = *(data);
		c1 = *(data + 1);
		
		if (*(data) > 127) {
			if (false == n_loadHzFromFlash((c0 * 256 + c1), (char*)&a[0])) {
				k = ((c0 - 0xA1) * 94 + (c1 - 0xA1)) * 32;
				/*load on sd-card*/
				//.......
			}
			fontData = (uint16_t*)a;
			dispHz(y, x, fontData);
			i += 2;
			x += 16;
			data++;
		}
		else {
			n_ShowChar(y + 4, x, *(data));
			x += 8;
			i++;
		}
		data++;
		//	    //20211208:cx 
		if (*(data) > 127) {
			/*8bits not enough show a hanzi*/
			if (i >= TEXTAREA_SIZE_X / 8 - 1) {
				break;
			}
		}
		else {
			/*0bits not enough show a char*/
			if (i >= TEXTAREA_SIZE_X / 8) {
				break;
			}
		}

	}
}


void n_dispTextArea(const char* dat) {
	uint16_t i = 0;
	uint16_t j = 1;
	uint16_t k = 0;
	unsigned char* data = (unsigned char*)dat;
	char a[4] = { 0,0,0,0 };

	while (*(data) != 0) {
		a[0] = *(data) % 256;
		a[1] = *(data) / 256;
		if (*(data) > 127) {/*hanzi use 16x16 bits*/
			n_dispHzFromSD((j) * 16, k * 8, a);
			k += 2;
		}
		else {
			n_dispHzFromSD((j) * 16, k * 8, a);
			k += 1;
		}
		data++;
		//k++;
		if (*(data) > 127) {
			if (k >= TEXTAREA_SIZE_X / 8 - 1) {
				k = 0;
				j++;
			}
		}
		else {
			if (k >= TEXTAREA_SIZE_X / 8 - 1) {
				k = 0;
				j++;
			}
		}
		if (j > 3) {
			return;
		}
	}
}

void x_loadFullPicture(unsigned char* filePath, uint32_t pos) {

}

void n_loadBitIcon(uint16_t u8I_y, uint16_t u8I_x, uint8_t* filePath) {

}

void n_loadBitIconFromFlash(uint16_t u8I_y, uint16_t u8I_x, const char* content) {
	uint16_t y = u8I_y;
	uint16_t ySize = 0;
	uint16_t x = u8I_x;
	uint16_t xSize = 0;
	uint16_t k = 0;
	uint16_t kk = 0;
	uint16_t data = 0;
	uint16_t i = 0;

	ySize = *(content + i++);
	xSize = *(content + i++);

	for (y = u8I_y; y < ySize + u8I_y; y++) {
		kk = xSize;
		for (x = 0; x < xSize / 8 + (xSize % 8 > 0 ? 1 : 0); x++) {
			data = *(content + i++);
			for (k = 0; k < (kk >= 8 ? 8 : (kk % 8)); k++) {
				x_GraphicsDeviceFastDrawPoint(y, u8I_x + x * 8 + k, ((0x01 & data) > 0) ? COLOR_SET : COLOR_CLR);
				data = data >> 0x01;
			}
			kk -= 8;
		}
	}
}

void x_ClearTextArea() {
	uint8_t u8T_y = 0;
	uint8_t u8T_x = 0;

	for (u8T_y = TEXTAREA_POS_Y; u8T_y < TEXTAREA_POS_Y + TEXTAREA_SIZE_Y; u8T_y++) {
		for (u8T_x = TEXTAREA_POS_X; u8T_x < TEXTAREA_POS_X + TEXTAREA_SIZE_X; u8T_x++) {
			//if(0 != x_GraphicsDeviceReadPoint(u8T_y,u8T_x)){
			x_GraphicsDeviceFastDrawPoint(u8T_y, u8T_x, COLOR_CLR);
			//}
		}
	}
}

void x_ClearMenuBarArea() {
	uint8_t u8T_y = 0;
	uint8_t u8T_x = 0;

	for (u8T_y = MENUBAR_POS_Y; u8T_y < MENUBAR_SIZE_Y; u8T_y++) {
		for (u8T_x = MENUBAR_POS_X; u8T_x < MENUBAR_SIZE_X; u8T_x++) {
			x_GraphicsDeviceFastDrawPoint(u8T_y, u8T_x, COLOR_CLR);
		}
	}
}

void x_Repaint() {
	uint8_t u8T_y = 0;
	uint8_t u8T_x = 0;
	for (u8T_y = TEXTAREA_POS_Y; u8T_y < TEXTAREA_POS_Y + TEXTAREA_SIZE_Y; u8T_y++) {
		for (u8T_x = TEXTAREA_POS_X; u8T_x < TEXTAREA_POS_X + TEXTAREA_SIZE_X; u8T_x++) {
			//if(0 != x_GraphicsDeviceReadPoint(u8T_y,u8T_x)){
			x_GraphicsDeviceFastDrawPoint(u8T_y, u8T_x, COLOR_CLR);
			//}
		}
	}
}

void n_ShowChar(uint8_t y, uint8_t x, uint8_t dat) {
	uint8_t c = dat - ' ';
	uint8_t i = 0, j = 0;
	for (j = 0; j < 6; j++) {
		for (i = 0; i < 8; i++) {
			a_list_gui_fastDrawPoint(y + i, x + j, ((F6x8[c * 6 + j] & (1 << i)) > 0) ? COLOR_SET : COLOR_CLR);
		}
	}
}
void n_OLED_ShowString(uint8_t y, uint8_t x, uint8_t* dat) {
	uint8_t j = 0;
	while (dat[j] != '\0') {
		n_ShowChar(y, x, dat[j]);
		if (x + 6 < CRAPHICS_DEVICE_SCREENSIZE_X - 6) {
			x += 6;
		}
		else if (x + 6 >= (CRAPHICS_DEVICE_SCREENSIZE_X - 6) && y + 8 < (CRAPHICS_DEVICE_SCREENSIZE_Y - 8)) {
			x = 0;
			y += 8;
		}
		else if (x + 6 >= (CRAPHICS_DEVICE_SCREENSIZE_X - 6) && y + 8 >= (CRAPHICS_DEVICE_SCREENSIZE_Y - 8)) {
			break;
		}
		j++;
	}
}



