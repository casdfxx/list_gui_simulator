#include "btn_driver.h"


void btn_evt_cb(void* arg);


uint8_t n_read_gpio_a(void*) {
	return read_io_up() ? 0 : 1;
}
uint8_t n_read_gpio_b(void*) {
	return read_io_down() ? 0 : 1;
}
uint8_t n_read_gpio_ok(void*) {
	return read_io_enter() ? 0 : 1;
}


void gpio_init() {
	static flex_button_t btn1, btn2, btn3;
	/*btn_A register*/
	btn1.id = BTN_ID_A;
	btn1.usr_button_read = n_read_gpio_a;
	btn1.cb = btn_evt_cb;
	btn1.pressed_logic_level = 0;
	btn1.short_press_start_tick = FLEX_MS_TO_SCAN_CNT(500);
	btn1.long_press_start_tick = FLEX_MS_TO_SCAN_CNT(1000);
	btn1.long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(2000);
	flex_button_register(&btn1);
	/*btn_B register*/
	btn2.id = BTN_ID_B;
	btn2.usr_button_read = n_read_gpio_b;
	btn2.cb = btn_evt_cb;
	btn2.pressed_logic_level = 0;
	btn2.short_press_start_tick = FLEX_MS_TO_SCAN_CNT(500);
	btn2.long_press_start_tick = FLEX_MS_TO_SCAN_CNT(1000);
	btn2.long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(2000);
	flex_button_register(&btn2);
	/*btn_OK register*/
	btn3.id = BTN_ID_OK;
	btn3.usr_button_read = n_read_gpio_ok;
	btn3.cb = btn_evt_cb;
	btn3.pressed_logic_level = 0;
	btn3.short_press_start_tick = FLEX_MS_TO_SCAN_CNT(500);
	btn3.long_press_start_tick = FLEX_MS_TO_SCAN_CNT(1000);
	btn3.long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(2000);
	flex_button_register(&btn3);

}


void btn_evt_cb(void* arg) {
	flex_button_t* btn = (flex_button_t*)arg;
	switch (btn->id) {
	case BTN_ID_A: {
		switch (btn->event) {
		case FLEX_BTN_PRESS_DOWN: {
			//os_printf("BTN_ID_A : FLEX_BTN_PRESS_DOWN\n");
		}
								break;
		case FLEX_BTN_PRESS_SHORT_START: {
			//os_printf("BTN_ID_A : FLEX_BTN_PRESS_SHORT_START\n");
			lg_SetBtnVal(LG_ITEM_A_LONGPRESS, 1);
		}
									   break;
		case FLEX_BTN_PRESS_LONG_START: {
			//os_printf("BTN_ID_A : FLEX_BTN_PRESS_LONG_START\n");
		}
									  break;
		case FLEX_BTN_PRESS_LONG_HOLD: {
			//os_printf("BTN_ID_A : FLEX_BTN_PRESS_LONG_HOLD\n");
		}
									 break;
		case FLEX_BTN_PRESS_CLICK: {
			//os_printf("BTN_ID_A : FLEX_BTN_PRESS_CLICK\n");
			lg_SetBtnVal(LG_ITEM_A_CLICK, 1);
		}
								 break;
		case FLEX_BTN_PRESS_DOUBLE_CLICK: {
			lg_SetBtnVal(LG_ITEM_A_CLICK, 2);
		}
										break;
		case FLEX_BTN_PRESS_REPEAT_CLICK: {
			//os_printf("BTN_ID_A : FLEX_BTN_PRESS_REPEAT_CLICK %d\n", btn->click_cnt);
			lg_SetBtnVal(LG_ITEM_A_CLICK, btn->click_cnt);
		}
										break;
		default:break;
		}
	}
				 break;
	case BTN_ID_B: {
		switch (btn->event) {
		case FLEX_BTN_PRESS_SHORT_START: {
			//os_printf("BTN_ID_B : FLEX_BTN_PRESS_SHORT_START\n");
			lg_SetBtnVal(LG_ITEM_B_LONGPRESS, 1);
		}
									   break;
		case FLEX_BTN_PRESS_LONG_START: {
			//os_printf("BTN_ID_B : FLEX_BTN_PRESS_LONG_START\n");
		}
									  break;
		case FLEX_BTN_PRESS_LONG_HOLD: {
			//os_printf("BTN_ID_B : FLEX_BTN_PRESS_LONG_HOLD\n");
		}
									 break;
		case FLEX_BTN_PRESS_CLICK: {
			//os_printf("BTN_ID_B : FLEX_BTN_PRESS_CLICK\n");
			lg_SetBtnVal(LG_ITEM_B_CLICK, 1);
		}
								 break;
		case FLEX_BTN_PRESS_DOUBLE_CLICK: {
			lg_SetBtnVal(LG_ITEM_B_CLICK, 2);
		}
										break;
		case FLEX_BTN_PRESS_REPEAT_CLICK: {
			//os_printf("BTN_ID_B : FLEX_BTN_PRESS_REPEAT_CLICK %d\n", btn->click_cnt);
			lg_SetBtnVal(LG_ITEM_B_CLICK, btn->click_cnt);
		}
										break;
		default:break;
		}
	}
				 break;
	case BTN_ID_OK: {
		switch (btn->event) {
		case FLEX_BTN_PRESS_SHORT_START: {
			//os_printf("BTN_ID_OK : FLEX_BTN_PRESS_SHORT_START\n");
		}
									   break;
		case FLEX_BTN_PRESS_LONG_START: {
			//os_printf("BTN_ID_OK : FLEX_BTN_PRESS_LONG_START\n");
			lg_SetBtnVal(LG_ITEM_OK_LONGPRESS, 1);
		}
									  break;
		case FLEX_BTN_PRESS_LONG_HOLD: {
			//os_printf("BTN_ID_OK : FLEX_BTN_PRESS_LONG_HOLD\n");
			lg_SetBtnVal(LG_ITEM_OK_LONGHOLD, 1);
		}
									 break;
		case FLEX_BTN_PRESS_CLICK: {
			//os_printf("BTN_ID_OK : FLEX_BTN_PRESS_CLICK\n");
			lg_SetBtnVal(LG_ITEM_OK_CLICK, 1);
		}
								 break;
		case FLEX_BTN_PRESS_DOUBLE_CLICK: {
			lg_SetBtnVal(LG_ITEM_OK_CLICK, 2);
		}
										break;
		case FLEX_BTN_PRESS_REPEAT_CLICK: {
			//os_printf("BTN_ID_OK : FLEX_BTN_PRESS_REPEAT_CLICK %d\n", btn->click_cnt);
			lg_SetBtnVal(LG_ITEM_OK_CLICK, btn->click_cnt);
		}
										break;

		default:break;
		}
	}
				  break;
	default:break;
	}
}
