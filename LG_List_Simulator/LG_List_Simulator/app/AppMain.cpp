#include "../lg_list/List_GUI.h"
#include "../appTools/btn_driver.h"

void x_AppMain() {
	gpio_init();
	lg_init();
	
	lg_item_t* root		= lg_item_create(NULL, "LALAKAKA");
	lg_item_t* item1	= lg_item_create(root, "¡¢item1(123456789ABCDEF)");
	lg_item_t* item2	= lg_item_create(root, "iµÄtem2");
	lg_item_t* item3	= lg_item_create(root, "item3ÍõÂé×Ó³Ôñ®¸òó¡");
	lg_item_t* item4	= lg_item_create(root, "item4");
	lg_item_t* item5	= lg_item_create(root, "item5(123456789ABCDEF)");
	lg_item_t* item6	= lg_item_create(root, "item6");
	lg_item_t* item7	= lg_item_create(root, "item7");
	lg_item_t* item8	= lg_item_create(root, "item8(123456789ABCDEF)");
	lg_item_t* item9	= lg_item_create(root, "item9(123456789ABCDEF)");

	lg_item_t* item2_1 = lg_item_create(item2, "item2 sub item1");

	lg_item_t* item3_1 = lg_radio_create(item3, "item3 sub item1");
	lg_item_t* item3_2 = lg_radio_create(item3, "item3 sub item2");
	lg_item_t* item3_3 = lg_radio_create(item3, "item3 sub item3");
	
	lg_load(root);

}