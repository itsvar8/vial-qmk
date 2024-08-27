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
					rgb_matrix_set_color(i, RGB_CORAL);
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