#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┐
     * │ A │ D │
     * ├───┼───┤
     * │ B │ E │
     * ├───┼───┤
     * │ C │ F │
     * └───┴───┘
     */
    [0] = LAYOUT_default(
        KC_A,    KC_D,
        KC_B,    KC_E,
        KC_C,    TO(1)
	),
	[1] = LAYOUT_default(
        KC_A,    KC_D,
        KC_B,    KC_E,
        KC_C,    TO(2)
	),
	[2] = LAYOUT_default(
        KC_A,    KC_D,
        KC_B,    KC_E,
        KC_C,    TO(3)
	),
	[3] = LAYOUT_default(
        KC_A,    KC_D,
        KC_B,    KC_E,
        KC_C,    TO(0)
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = {  ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [2] = {  ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [3] = {  ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_RIGHT, KC_LEFT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
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
