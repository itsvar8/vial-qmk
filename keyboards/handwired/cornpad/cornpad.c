// Copyright 2022 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
{
// Key Matrix to LED Index
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,         0, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED,    NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
// LED Index to Physical Position
	{ 104, 0}
}, {
// LED Index to Flag
  4
}
};

#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	for (uint8_t i = led_min; i < led_max; i++) {
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