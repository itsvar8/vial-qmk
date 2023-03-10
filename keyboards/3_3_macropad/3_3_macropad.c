#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
{
// Key Matrix to LED Index
  { 0, 5 },
  { 1, 4 },
  { 2, 3 }
}, {
// LED Index to Physical Position
    { 0, 0},
	{ 0, 32},
	{ 0, 64},
	
	{ 224,64 },
	{ 224,32 },
	{ 224, 0}
}, {
// LED Index to Flag
  4, 4, 4, 4, 4, 4
}
};

#endif

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state)) {
        case 1:
            rgb_matrix_set_color(3, RGB_RED);
			rgb_matrix_set_color(4, RGB_RED);
			rgb_matrix_set_color(5, RGB_RED);
            break;
        case 2:
            rgb_matrix_set_color(3, RGB_YELLOW);
			rgb_matrix_set_color(4, RGB_YELLOW);
			rgb_matrix_set_color(5, RGB_YELLOW);			
            break;
        case 3:
            rgb_matrix_set_color(3, RGB_BLUE);
			rgb_matrix_set_color(4, RGB_BLUE);
			rgb_matrix_set_color(5, RGB_BLUE);
            break;
        default:
            break;
    }
}