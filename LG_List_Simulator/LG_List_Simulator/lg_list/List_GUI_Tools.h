#ifndef _LIST_GUI_TOOLS_H_
#define _LIST_GUI_TOOLS_H_


#include <stdint.h>
#include "List_GUI_Config.h"


typedef enum LG_DIR_{
  LG_DIR_UP 	= 0,
  LG_DIR_DOWN,
  LG_DIR_LEFT,
  LG_DIR_RIGHT,
  LG_DIR_NONE
}LG_DIR;

typedef struct {
  void (*pf_DrawPoint)(uint16_t y, uint16_t x, int color);
  void (*pf_FastDrawPoint)(uint16_t y, uint16_t x, int color);
  int  (*pf_ReadPoint)(uint16_t y, uint16_t x);
#if COLOR_BITS == COLOR_BITS_32
  uint32_t* GDDRAM;
#elif COLOR_BITS == COLOR_BITS_16
  uint16_t* GDDRAM;
#elif COLOR_BITS == COLOR_BITS_1
  uint8_t* GDDRAM;
#endif
  
  void (*pf_MoveRect)(LG_DIR dir,int step, int y,int x,int ySize, int xSize);
  void (*pf_dispHzFromSD)(uint16_t y, uint16_t x,char* dat);
  void (*pf_dispTextArea)(const char* dat);
  void (*pf_loadFullPicture)(unsigned char* filePath, uint32_t pos);
  void (*pf_loadBitIcon)(uint16_t y, uint16_t x,unsigned char* filePath);
  void (*pf_loadBitIconFromFlash)(uint16_t y, uint16_t x,const char* content);
  void (*pf_ReverseRect)(uint16_t y, uint16_t x, uint16_t ySize, uint16_t xSize);
  void (*pf_ClearTextArea)(void);
  void (*pf_ClearMenuBarArea)(void);
  void (*pf_Repaint)(void);
}LGToolsDef;

extern LGToolsDef LGTools;
void lg_init();

#endif 
