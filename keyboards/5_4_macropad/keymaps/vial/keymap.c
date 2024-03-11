// Copyright 2024 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

extern MidiDevice midi_device;

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
  MIDI_UP,
  MIDI_DN,
  CC_RST,
  CC_UP,
  CC_DN,
};

#define MIDI_CYCLE_START 0
#define MIDI_CYCLE_END   63

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   9

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
	case MIDI_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, current_MIDI_cc, 65);
	  } else {
	  }
	  break;
	case MIDI_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, current_MIDI_cc, 63);
	  } else {
	  }
	  break;
	case CC_RST:
      if (record->event.pressed) {
          current_MIDI_cc = MIDI_CYCLE_START;
      } else {
      }
      break;
	case CC_UP:
      if (record->event.pressed) {
          if (current_MIDI_cc > MIDI_CYCLE_END || current_MIDI_cc < MIDI_CYCLE_START) {
            return false;
          } else {
			  current_MIDI_cc++;
          }
	  }
	  if (current_MIDI_cc > MIDI_CYCLE_END) {
          current_MIDI_cc = MIDI_CYCLE_START;
      }
      break;
	case CC_DN:
      if (record->event.pressed) {
          if (current_MIDI_cc > MIDI_CYCLE_END || current_MIDI_cc < MIDI_CYCLE_START) {
            return false;
          } else {
			  current_MIDI_cc--;
          }
	  }
	  if (current_MIDI_cc < MIDI_CYCLE_START) {
          current_MIDI_cc = MIDI_CYCLE_END;
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

void keyboard_post_init_user(void) {
    vial_tap_dance_entry_t td = { KC_NO,
                                  KC_NO,
                                  KC_NO,
                                  KC_NO,
                                  TAPPING_TERM };
    dynamic_keymap_set_tap_dance(0, &td); // the first value corresponds to the TD(i) slot
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_default(
  //,----------------------------------------.
             XPLR,        KC_UP,      ALT_ESC,
  //|------------+-------------+-------------|
          KC_LEFT,       KC_TAB,      KC_RGHT,
  //|------------+-------------+-------------|
           KC_ESC,      KC_DOWN,   NEXT_LAYER
  //`----------------------------------------'|
  ),
    [1] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [2] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [3] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [4] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [5] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [6] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [7] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [8] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //`----------------------------------------'|
  ),
    [9] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      CLR_EPR,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      QK_BOOT,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      CLR_KBD,      KC_TRNS,
  //`----------------------------------------'|
  ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {  ENCODER_CCW_CW(    UNDO,    REDO ), ENCODER_CCW_CW( INV_ALT_TAB, ALT_TAB ), ENCODER_CCW_CW( KC_PGUP, KC_PGDN ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[1] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[2] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[3] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[4] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[5] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[6] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[7] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[8] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
	[9] = {  ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW(     KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( KC_TRNS, KC_TRNS ), ENCODER_CCW_CW( PREV_LAYER, NEXT_LAYER )  },
};
#endif