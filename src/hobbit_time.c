/*
 
 Hobbit Time
 
 https://github.com/keelanc/hobbit_time
 
 */

#include "pebble.h"
#include "hobbit_meals.h"


Window *window;
TextLayer *text_hobbit_layer;

static char hobbit_hour[] = "a quite long placeholder";
//static char dummy_text[] = "\n00";


static void update_watchface(struct tm* t) {
	
	hobbit_time(t->tm_hour, hobbit_hour);
//	hobbit_time(t->tm_sec, hobbit_hour);
//	strftime(dummy_text, sizeof(dummy_text), "\n%S", t);
//    strcat(hobbit_hour, dummy_text);
	text_layer_set_text(text_hobbit_layer, hobbit_hour);
    
}


static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
	// doing something on the hour
	
	update_watchface(tick_time);
}


static void handle_init(void) {
	// initializing app
	
    window = window_create();
	window_stack_push(window, true /* Animated */);
	window_set_background_color(window, GColorBlack);
	
	// init the hobbit text layer
    text_hobbit_layer = text_layer_create(GRect(0, 25, 144, 168 - 40));
	text_layer_set_font(text_hobbit_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GOTHAM_LIGHT_36)));
//	text_layer_set_font(&text_hobbit_layer, fonts_load_custom_font(fonts_get_system_font(FONT_KEY_GOTHAM_42_LIGHT)));
	text_layer_set_text_color(text_hobbit_layer, GColorWhite);
	text_layer_set_background_color(text_hobbit_layer, GColorClear);
    Layer *root_layer = window_get_root_layer(window);
    layer_add_child(root_layer, text_layer_get_layer(text_hobbit_layer));
	
	// load watchface immediately
	time_t now = time(NULL);
    struct tm * t = localtime(&now);
	update_watchface(t);
    
    tick_timer_service_subscribe(HOUR_UNIT, &handle_tick);
}


static void handle_deinit(void) {
    text_layer_destroy(text_hobbit_layer);
    window_destroy(window);
}

int main(void) {
    handle_init();
	app_event_loop();
    handle_deinit();
}
