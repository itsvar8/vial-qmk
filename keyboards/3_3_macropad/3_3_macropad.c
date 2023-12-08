// Copyright 2022 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	for (uint8_t i = 3; i < led_max; i++) {
		switch(get_highest_layer(layer_state)) {
			case 1:
				rgb_matrix_set_color(i, RGB_RED);
				break;
			case 2:
				rgb_matrix_set_color(i, RGB_YELLOW);
				break;
			case 3:
				rgb_matrix_set_color(i, RGB_BLUE);
				break;
			case 4:
				rgb_matrix_set_color(i, RGB_MAGENTA);
				break;
			case 5:
				rgb_matrix_set_color(i, RGB_TEAL);
				break;
			case 6:
				rgb_matrix_set_color(i, RGB_ORANGE);
				break;
			case 7:
				rgb_matrix_set_color(i, RGB_PURPLE);
				break;

			default:
				break;
		}
    }
	return false;
}

uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}