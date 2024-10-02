// Copyright 2022 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <raw_hid.h>

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_layer_move_active = false;
uint16_t layer_move_timer = 0;

int8_t current_MIDI_cc = 0;

enum custom_keycodes {
  NEXT_LAYER = QK_KB_0,
  PREV_LAYER,
  ALT_TAB,
  INV_ALT_TAB,
  ALT_ESC,
  XPLR,
  UNDO,
  REDO,
  REDO_Y,
  SCR_REC,
  CLR_EPR,
  CLR_KBD,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   7

// Add the behaviour of this new keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NEXT_LAYER:
      if (record->event.pressed) {
		if (!is_layer_move_active) {
		is_layer_move_active = true;
		}
	  layer_move_timer = timer_read();
      } else {
		  if (is_layer_move_active) {
		  uint8_t current_layer = get_highest_layer(layer_state);
	      
          // Check if we are within the range, if not quit
          if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
            return false;
          }
	      
          uint8_t next_layer = current_layer + 1;
          if (next_layer > LAYER_CYCLE_END) {
              next_layer = LAYER_CYCLE_START;
          }
          layer_move(next_layer);
		  is_layer_move_active = false;
		  }
	  }
      break;
	case PREV_LAYER:
      if (record->event.pressed) {
		if (!is_layer_move_active) {
		is_layer_move_active = true;
		}
	  layer_move_timer = timer_read();
      } else {
		  if (is_layer_move_active) {
		  int8_t current_layer2 = get_highest_layer(layer_state);

          // Check if we are within the range, if not quit
          if (current_layer2 > LAYER_CYCLE_END || current_layer2 < LAYER_CYCLE_START) {
            return false;
          }

          int8_t prev_layer = current_layer2 - 1;
          if (prev_layer < LAYER_CYCLE_START) {
              prev_layer = LAYER_CYCLE_END;
          }
          layer_move(prev_layer);
		  is_layer_move_active = false;
		  }
	  }
      break;
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
	case INV_ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
		register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_LSFT);
        unregister_code(KC_TAB);
      }
      break;
	case ALT_ESC:
	  if (record->event.pressed) {
		  register_code(KC_LALT);
		  tap_code(KC_ESC);
	  } else {
		unregister_code(KC_LALT);
	  }
	  break;
	case XPLR:
	  if (record->event.pressed) {
		  register_code(KC_LGUI);
		  tap_code(KC_E);
	  } else {
		unregister_code(KC_LGUI);
	  }
	  break;
	case UNDO:
	  if (record->event.pressed) {
		  register_code(KC_LCTL);
		  tap_code(KC_Z);
	  } else {
		unregister_code(KC_LCTL);
	  }
	  break;
	case REDO:
	  if (record->event.pressed) {
		  register_code(KC_LCTL);
		  register_code(KC_LSFT);
		  tap_code(KC_Z);
	  } else {
		unregister_code(KC_LCTL);
		unregister_code(KC_LSFT);
	  }
	  break;
	case REDO_Y:
	  if (record->event.pressed) {
		  register_code(KC_LCTL);
		  tap_code(KC_Y);
	  } else {
		unregister_code(KC_LCTL);
	  }
	  break;
	case SCR_REC:
	  if (record->event.pressed) {
		  register_code(KC_LCTL);
		  register_code(KC_LSFT);
		  tap_code(KC_E);
	  } else {
		unregister_code(KC_LCTL);
		unregister_code(KC_LSFT);
	  }
	  break;
	case CLR_EPR:
	  if (record->event.pressed) {
		  eeconfig_init();
	  } else {
	  }
	  break;
	case CLR_KBD:
	  if (record->event.pressed) {
		  clear_keyboard();
	  } else {
	  }
	  break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 800) {
      is_alt_tab_active = false;
	  unregister_code(KC_LALT);
    }
  }
  if (is_layer_move_active) {
    if (timer_elapsed(layer_move_timer) > 250) {
	  is_layer_move_active = false;
	  layer_move(0);
	}
  }
}

enum my_command_id {
	id_current_layer   = 0x40,
	id_layer_0         = 0x30,
	id_layer_1         = 0x31,
	id_layer_2         = 0x32,
	id_layer_3         = 0x33,
	id_layer_4         = 0x34,
	id_layer_5         = 0x35,
	id_layer_6         = 0x36,
	id_layer_7         = 0x37,
	id_layer_8         = 0x38,
	id_layer_9         = 0x39,
};

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
	uint8_t *command_id   = &(data[0]);
	switch (*command_id) {
		case id_current_layer: {
            uint8_t response[length];
			memset(response, 0, length);
			
			/* count number of digits */
			int c = 0; /* digit position */
			int n = get_highest_layer(layer_state);

			while (n != 0)
			{
				n /= 10;
				c++;
			}

			int numberArray[c];

			c = 0;    
			n = get_highest_layer(layer_state);

			/* extract each digit */
			while (n != 0)
			{
				numberArray[c] = n % 10;
				n /= 10;
				c++;
			}
			
			int i;
			size_t max = sizeof(numberArray)/sizeof(numberArray[0]);
			for (i = 0; i < max; i++) {
				response[i] = numberArray[i];
			}

			raw_hid_send(response, length);
            break;
        }
		case id_layer_0: {
            layer_move(0);
            break;
        }
		case id_layer_1: {
            layer_move(1);
            break;
        }
		case id_layer_2: {
            layer_move(2);
            break;
        }
		case id_layer_3: {
            layer_move(3);
            break;
        }
		case id_layer_4: {
            layer_move(4);
            break;
        }
		case id_layer_5: {
            layer_move(5);
            break;
        }
		case id_layer_6: {
			layer_move(6);
            break;
        }
		case id_layer_7: {
            layer_move(7);
            break;
        }
		case id_layer_8: {
            layer_move(8);
            break;
        }
		case id_layer_9: {
            layer_move(9);
            break;
        }
	}
}

//void keyboard_post_init_user(void) {
//    vial_tap_dance_entry_t td = { KC_NO,
//                                  KC_NO,
//                                  KC_NO,
//                                  KC_NO,
//                                  TAPPING_TERM };
//    dynamic_keymap_set_tap_dance(0, &td); // the first value corresponds to the TD(i) slot
//}

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
        KC_A,       KC_D,
        KC_B,       KC_E,
        KC_C,       NEXT_LAYER
	),
	[1] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
	),
	[2] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
	),
	[3] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
    ),
	[4] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
    ),
	[5] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
    ),
	[6] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
    ),
	[7] = LAYOUT_default(
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [2] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [3] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [4] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [5] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [6] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [7] = {  ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
};
#endif