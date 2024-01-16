// Copyright 2022 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
{
// Key Matrix to LED Index
  { NO_LED, NO_LED,      3,      2,      1,         0, NO_LED, NO_LED,     20,        19,     18,     17, NO_LED, NO_LED },
  { NO_LED, NO_LED,      4,     31,     32,        33, NO_LED, NO_LED,     21,        22,     23,     16, NO_LED, NO_LED },
  { NO_LED, NO_LED,      5,     30,     29,        28, NO_LED,     27,     26,        25,     24,     15, NO_LED, NO_LED },
  { NO_LED, NO_LED,      6,      7,      8,         9,     10, NO_LED,     11,        12,     13,     14, NO_LED, NO_LED }
}, {
// LED Index to Physical Position
	{ 90, 11}, { 67, 9}, { 45, 7}, { 23, 3}, { 7, 17}, { 8, 35}, { 14, 53}, { 38, 57}, { 63, 60}, { 87, 61}, { 112, 62}, { 137, 61}, { 161, 60}, { 186, 57}, { 210, 53}, { 216, 35}, { 217, 17}, { 201, 3}, { 179, 7}, { 157, 9}, { 134, 11}, { 138, 28}, { 165, 26}, { 191, 22}, { 190, 39}, { 164, 42}, { 138, 44}, { 112, 45}, { 86, 44}, { 60, 42}, { 34, 39}, { 33, 22}, { 59, 26}, { 86, 28}
}, {
// LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
}
};

#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	for (uint8_t i = led_min; i < led_max; i++) {
		if (g_led_config.flags[i] & LED_FLAG_MODIFIER) {
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