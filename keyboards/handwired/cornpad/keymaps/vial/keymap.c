// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {          // Make sure have the awesome keycode ready
  CYCLE_LAYERS = QK_KB_0,
  ALT_TAB,
  INV_ALT_TAB,
  ALT_ESC,
  XPLR,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   7

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
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
	case CYCLE_LAYERS:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

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
      return false;

    // Process other keycodes normally
    default:
      return true;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 800) {
      is_alt_tab_active = false;
	  unregister_code(KC_LALT);
    }
  }
}

void keyboard_post_init_user(void) {
    vial_tap_dance_entry_t td = { CYCLE_LAYERS,
                                  TO(0),
                                  KC_NO,
                                  KC_NO,
                                  TAPPING_TERM };
    dynamic_keymap_set_tap_dance(0, &td); // the first value corresponds to the TD(i) slot
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_default(
  //,---------------------------------------------------------------.            ,----------------------------------.            ,-------------------------------------------------------------------.
             KC_Q,         KC_W,         KC_E,         KC_R,    KC_T,               KC_P7,   KC_P8,   KC_P9, KC_PSLS,                 KC_Y,         KC_U,         KC_I,         KC_O,            KC_P,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
     LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),    KC_G,               KC_P4,   KC_P5,   KC_P6, KC_PAST,                 KC_H, LGUI_T(KC_J), LALT_T(KC_K), LCTL_T(KC_L), LSFT_T(KC_SCLN),
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
             KC_Z,         KC_X,         KC_C,         KC_V,    KC_B,               KC_P1,   KC_P2,   KC_P3, KC_PMNS,                 KC_N,         KC_M,      KC_COMM,       KC_DOT,         KC_SLSH,
  //|------------+-------------+-------------+-------------+--------+--------|   +-------+--------+--------+--------+   |--------+--------+-------------+-------------+-------------+----------------|
                                      QK_GESC,      TL_LOWR,  KC_SPC,    XPLR,      KC_P0, KC_PDOT, KC_PENT, KC_PPLS,     ALT_ESC, KC_BSPC,      TL_UPPR,       KC_ENT
                                   //`---------------------------------------'   `----------------------------------'   `---------------------------------------------'|
  ),
    [1] = LAYOUT_default(
  //,---------------------------------------------------------------.            ,----------------------------------.            ,-------------------------------------------------------------------.
           KC_DEL,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------+--------|   +-------+--------+--------+--------+   |--------+--------+-------------+-------------+-------------+----------------|
                                      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,      KC_TRNS,      KC_TRNS
                                   //`---------------------------------------'   `----------------------------------'   `---------------------------------------------'|
  ),
    [2] = LAYOUT_default(
  //,---------------------------------------------------------------.            ,----------------------------------.            ,-------------------------------------------------------------------.
          KC_TRNS,        KC_UP,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
          KC_LEFT,      KC_DOWN,     KC_RIGHT,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------+--------|   +-------+--------+--------+--------+   |--------+--------+-------------+-------------+-------------+----------------|
                                      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,      KC_TRNS,      KC_TRNS
                                   //`---------------------------------------'   `----------------------------------'   `---------------------------------------------'|
  ),
    [3] = LAYOUT_default(
  //,---------------------------------------------------------------.            ,----------------------------------.            ,-------------------------------------------------------------------.
          QK_BOOT,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------|            +-------+--------+--------+--------+            |--------+-------------+-------------+-------------+----------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_TRNS,
  //|------------+-------------+-------------+-------------+--------+--------|   +-------+--------+--------+--------+   |--------+--------+-------------+-------------+-------------+----------------|
                                      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,      KC_TRNS,      KC_TRNS
                                   //`---------------------------------------'   `----------------------------------'   `---------------------------------------------'|
  ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(INV_ALT_TAB, ALT_TAB)  },
	[1] = {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(INV_ALT_TAB, ALT_TAB)  },
	[2] = {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(INV_ALT_TAB, ALT_TAB)  },
	[3] = {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(INV_ALT_TAB, ALT_TAB)  },
};
#endif