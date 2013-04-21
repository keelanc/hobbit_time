/*
 
 Hobbit Time
 
 https://github.com/keelanc/hobbit_time
 
 */

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "hobbit_meals.h"


#define MY_UUID { 0xF0, 0xBF, 0xE0, 0x0D, 0x55, 0x08, 0x44, 0xDA, 0xA7, 0xAA, 0xFF, 0xB2, 0x8A, 0x3A, 0xC4, 0xE8 }
PBL_APP_INFO(MY_UUID,
             "Hobbit Time", "keelanchufor.com",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
Layer display_layer;
TextLayer text_hobbit_layer;

static char hobbit_hour[] = "a quite long placeholder";


void update_watchface(PblTm* t) {
	
	hobbit_time(t->tm_hour, hobbit_hour);
//	hobbit_time(t->tm_sec, hobbit_hour);
	text_layer_set_text(&text_hobbit_layer, hobbit_hour);
	
}


void handle_init(AppContextRef ctx) {
	// initializing app
	
	(void)ctx;
	
	window_init(&window, "Hobbit Time watch");
	window_stack_push(&window, true /* Animated */);
	window_set_background_color(&window, GColorBlack);
	
	resource_init_current_app(&APP_RESOURCES);
	
	// init the hobbit text layer
	text_layer_init(&text_hobbit_layer, GRect(0, 25, 144, 168 - 40));
	text_layer_set_font(&text_hobbit_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GOTHAM_LIGHT_36)));
//	text_layer_set_font(&text_hobbit_layer, fonts_load_custom_font(fonts_get_system_font(FONT_KEY_GOTHAM_42_LIGHT)));
	text_layer_set_text_color(&text_hobbit_layer, GColorWhite);
	text_layer_set_background_color(&text_hobbit_layer, GColorClear);
	layer_add_child(&window.layer, &text_hobbit_layer.layer);
	
	// load watchface immediately
	PblTm t;
	get_time(&t);
	update_watchface(&t);
}


void handle_tick(AppContextRef ctx, PebbleTickEvent *t) {
	// doing something on the hour
	
	(void)ctx;
	
	update_watchface(t->tick_time);
	
}


void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &handle_init,
		.tick_info = {
			.tick_handler = &handle_tick,
			.tick_units = HOUR_UNIT
		}
	};
	app_event_loop(params, &handlers);
}
