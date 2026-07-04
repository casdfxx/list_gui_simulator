#pragma once

#include "resource.h"
#include "../lg_list/List_GUI.h"

extern void simulator_screen_init();
extern void simulator_screen_draw_point(unsigned int x, unsigned int y, int color);
extern void fill_screen(int color);
extern void simulator_screen_repaint();

bl read_io_up();
bl read_io_down();
bl read_io_left();
bl read_io_right();
bl read_io_enter();