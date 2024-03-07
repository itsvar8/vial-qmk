// Copyright 2024 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
{
// Key Matrix to LED Index
  { 2,     1,     0 },
  { 3,     4,     5 },
  { 8,     7,     6 }
}, {
// LED Index to Physical Position
  { 135, 9}, { 112, 14}, { 89, 9}, { 94, 32}, { 112, 32}, { 130, 32}, { 135, 55}, { 112, 50}, { 89, 55}
}, {
// LED Index to Flag
  1, 4, 1, 4, 4, 4, 1, 4, 1
}
};

#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	switch(get_highest_layer(layer_state)) {
		case 1:
			rgb_matrix_set_color(2, RGB_WHITE);
			break;
		case 2:
			rgb_matrix_set_color(1, RGB_WHITE);
			break;
		case 3:
			rgb_matrix_set_color(0, RGB_WHITE);
			break;
		case 4:
			rgb_matrix_set_color(3, RGB_WHITE);
			break;
		case 5:
			rgb_matrix_set_color(4, RGB_WHITE);
			break;
		case 6:
			rgb_matrix_set_color(5, RGB_WHITE);
			break;
		case 7:
			rgb_matrix_set_color(8, RGB_WHITE);
			break;
		case 8:
			rgb_matrix_set_color(7, RGB_WHITE);
			break;
		case 9:
			rgb_matrix_set_color(6, RGB_WHITE);
			break;
		default:
			break;
	}
	return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	setPinOutput(25);
    if (get_highest_layer(state) > 0) {
        writePinHigh(25);
    } else {
        writePinLow(25);
	}
  return state;
}