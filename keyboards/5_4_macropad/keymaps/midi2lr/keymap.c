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
  CC_00_UP,
  CC_00_DN,
  CC_01_UP,
  CC_01_DN,
  CC_02_UP,
  CC_02_DN,
  CC_03_UP,
  CC_03_DN,
  CC_04_UP,
  CC_04_DN,
  CC_05_UP,
  CC_05_DN,
  CC_06_UP,
  CC_06_DN,
  CC_07_UP,
  CC_07_DN,
  CC_08_UP,
  CC_08_DN,
  CC_09_UP,
  CC_09_DN,
  CC_10_UP,
  CC_10_DN,
  CC_11_UP,
  CC_11_DN,
  CC_12_UP,
  CC_12_DN,
  CC_13_UP,
  CC_13_DN,
  CC_14_UP,
  CC_14_DN,
  CC_15_UP,
  CC_15_DN,
  CC_16_UP,
  CC_16_DN,
  CC_17_UP,
  CC_17_DN,
  CC_18_UP,
  CC_18_DN,
  CC_19_UP,
  CC_19_DN,
  CC_20_UP,
  CC_20_DN,
  CC_21_UP,
  CC_21_DN,
  CC_22_UP,
  CC_22_DN,
  CC_23_UP,
  CC_23_DN,
  CC_24_UP,
  CC_24_DN,
  CC_25_UP,
  CC_25_DN,
  CC_26_UP,
  CC_26_DN,
  CC_27_UP,
  CC_27_DN,
  CC_28_UP,
  CC_28_DN,
  CC_29_UP,
  CC_29_DN,
  CC_30_UP,
  CC_30_DN,
  CC_31_UP,
  CC_31_DN,
  CC_32_UP,
  CC_32_DN,
  CC_33_UP,
  CC_33_DN,
  CC_34_UP,
  CC_34_DN,
  CC_35_UP,
  CC_35_DN,
  CC_36_UP,
  CC_36_DN,
  CC_37_UP,
  CC_37_DN,
  CC_38_UP,
  CC_38_DN,
  CC_39_UP,
  CC_39_DN,
  CC_40_UP,
  CC_40_DN,
  CC_41_UP,
  CC_41_DN,
  CC_42_UP,
  CC_42_DN,
  CC_43_UP,
  CC_43_DN,
  CC_44_UP,
  CC_44_DN,
  CC_45_UP,
  CC_45_DN,
  CC_46_UP,
  CC_46_DN,
  CC_47_UP,
  CC_47_DN,
  CC_48_UP,
  CC_48_DN,
  CC_49_UP,
  CC_49_DN,
  CC_50_UP,
  CC_50_DN,
  CC_51_UP,
  CC_51_DN,
  CC_52_UP,
  CC_52_DN,
  CC_53_UP,
  CC_53_DN,
  CC_54_UP,
  CC_54_DN,
  CC_55_UP,
  CC_55_DN,
  CC_56_UP,
  CC_56_DN,
  CC_57_UP,
  CC_57_DN,
  CC_58_UP,
  CC_58_DN,
  CC_59_UP,
  CC_59_DN,
  CC_60_UP,
  CC_60_DN,
  CC_61_UP,
  CC_61_DN,
  CC_62_UP,
  CC_62_DN,
  CC_63_UP,
  CC_63_DN,
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
	case CC_00_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 0, 65);
	  } else {
	  }
	  break;
	case CC_00_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 0, 63);
	  } else {
	  }
	  break;
	case CC_01_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 1, 65);
	  } else {
	  }
	  break;
	case CC_01_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 1, 63);
	  } else {
	  }
	  break;
	case CC_02_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 2, 65);
	  } else {
	  }
	  break;
	case CC_02_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 2, 63);
	  } else {
	  }
	  break;
	case CC_03_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 3, 65);
	  } else {
	  }
	  break;
	case CC_03_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 3, 63);
	  } else {
	  }
	  break;
	case CC_04_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 4, 65);
	  } else {
	  }
	  break;
	case CC_04_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 4, 63);
	  } else {
	  }
	  break;
	case CC_05_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 5, 65);
	  } else {
	  }
	  break;
	case CC_05_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 5, 63);
	  } else {
	  }
	  break;
	case CC_06_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 6, 65);
	  } else {
	  }
	  break;
	case CC_06_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 6, 63);
	  } else {
	  }
	  break;
	case CC_07_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 7, 65);
	  } else {
	  }
	  break;
	case CC_07_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 7, 63);
	  } else {
	  }
	  break;
	case CC_08_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 8, 65);
	  } else {
	  }
	  break;
	case CC_08_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 8, 63);
	  } else {
	  }
	  break;
	case CC_09_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 9, 65);
	  } else {
	  }
	  break;
	case CC_09_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 9, 63);
	  } else {
	  }
	  break;
	case CC_10_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 10, 65);
	  } else {
	  }
	  break;
	case CC_10_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 10, 63);
	  } else {
	  }
	  break;
	case CC_11_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 11, 65);
	  } else {
	  }
	  break;
	case CC_11_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 11, 63);
	  } else {
	  }
	  break;
	case CC_12_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 12, 65);
	  } else {
	  }
	  break;
	case CC_12_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 12, 63);
	  } else {
	  }
	  break;
	case CC_13_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 13, 65);
	  } else {
	  }
	  break;
	case CC_13_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 13, 63);
	  } else {
	  }
	  break;
	case CC_14_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 14, 65);
	  } else {
	  }
	  break;
	case CC_14_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 14, 63);
	  } else {
	  }
	  break;
	case CC_15_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 15, 65);
	  } else {
	  }
	  break;
	case CC_15_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 15, 63);
	  } else {
	  }
	  break;
	case CC_16_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 16, 65);
	  } else {
	  }
	  break;
	case CC_16_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 16, 63);
	  } else {
	  }
	  break;
	case CC_17_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 17, 65);
	  } else {
	  }
	  break;
	case CC_17_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 17, 63);
	  } else {
	  }
	  break;
	case CC_18_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 18, 65);
	  } else {
	  }
	  break;
	case CC_18_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 18, 63);
	  } else {
	  }
	  break;
	case CC_19_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 19, 65);
	  } else {
	  }
	  break;
	case CC_19_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 19, 63);
	  } else {
	  }
	  break;
	case CC_20_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 20, 65);
	  } else {
	  }
	  break;
	case CC_20_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 20, 63);
	  } else {
	  }
	  break;
	case CC_21_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 21, 65);
	  } else {
	  }
	  break;
	case CC_21_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 21, 63);
	  } else {
	  }
	  break;
	case CC_22_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 22, 65);
	  } else {
	  }
	  break;
	case CC_22_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 22, 63);
	  } else {
	  }
	  break;
	case CC_23_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 23, 65);
	  } else {
	  }
	  break;
	case CC_23_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 23, 63);
	  } else {
	  }
	  break;
	case CC_24_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 24, 65);
	  } else {
	  }
	  break;
	case CC_24_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 24, 63);
	  } else {
	  }
	  break;
	case CC_25_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 25, 65);
	  } else {
	  }
	  break;
	case CC_25_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 25, 63);
	  } else {
	  }
	  break;
	case CC_26_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 26, 65);
	  } else {
	  }
	  break;
	case CC_26_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 26, 63);
	  } else {
	  }
	  break;
	case CC_27_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 27, 65);
	  } else {
	  }
	  break;
	case CC_27_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 27, 63);
	  } else {
	  }
	  break;
	case CC_28_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 28, 65);
	  } else {
	  }
	  break;
	case CC_28_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 28, 63);
	  } else {
	  }
	  break;
	case CC_29_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 29, 65);
	  } else {
	  }
	  break;
	case CC_29_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 29, 63);
	  } else {
	  }
	  break;
	case CC_30_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 30, 65);
	  } else {
	  }
	  break;
	case CC_30_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 30, 63);
	  } else {
	  }
	  break;
	case CC_31_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 31, 65);
	  } else {
	  }
	  break;
	case CC_31_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 31, 63);
	  } else {
	  }
	  break;
	case CC_32_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 32, 65);
	  } else {
	  }
	  break;
	case CC_32_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 32, 63);
	  } else {
	  }
	  break;
	case CC_33_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 33, 65);
	  } else {
	  }
	  break;
	case CC_33_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 33, 63);
	  } else {
	  }
	  break;
	case CC_34_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 34, 65);
	  } else {
	  }
	  break;
	case CC_34_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 34, 63);
	  } else {
	  }
	  break;
	case CC_35_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 35, 65);
	  } else {
	  }
	  break;
	case CC_35_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 35, 63);
	  } else {
	  }
	  break;
	case CC_36_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 36, 65);
	  } else {
	  }
	  break;
	case CC_36_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 36, 63);
	  } else {
	  }
	  break;
	case CC_37_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 37, 65);
	  } else {
	  }
	  break;
	case CC_37_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 37, 63);
	  } else {
	  }
	  break;
	case CC_38_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 38, 65);
	  } else {
	  }
	  break;
	case CC_38_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 38, 63);
	  } else {
	  }
	  break;
	case CC_39_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 39, 65);
	  } else {
	  }
	  break;
	case CC_39_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 39, 63);
	  } else {
	  }
	  break;
	case CC_40_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 40, 65);
	  } else {
	  }
	  break;
	case CC_40_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 40, 63);
	  } else {
	  }
	  break;
	case CC_41_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 41, 65);
	  } else {
	  }
	  break;
	case CC_41_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 41, 63);
	  } else {
	  }
	  break;
	case CC_42_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 42, 65);
	  } else {
	  }
	  break;
	case CC_42_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 42, 63);
	  } else {
	  }
	  break;
	case CC_43_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 43, 65);
	  } else {
	  }
	  break;
	case CC_43_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 43, 63);
	  } else {
	  }
	  break;
	case CC_44_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 44, 65);
	  } else {
	  }
	  break;
	case CC_44_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 44, 63);
	  } else {
	  }
	  break;
	case CC_45_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 45, 65);
	  } else {
	  }
	  break;
	case CC_45_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 45, 63);
	  } else {
	  }
	  break;
	case CC_46_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 46, 65);
	  } else {
	  }
	  break;
	case CC_46_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 46, 63);
	  } else {
	  }
	  break;
	case CC_47_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 47, 65);
	  } else {
	  }
	  break;
	case CC_47_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 47, 63);
	  } else {
	  }
	  break;
	case CC_48_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 48, 65);
	  } else {
	  }
	  break;
	case CC_48_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 48, 63);
	  } else {
	  }
	  break;
	case CC_49_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 49, 65);
	  } else {
	  }
	  break;
	case CC_49_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 49, 63);
	  } else {
	  }
	  break;
	case CC_50_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 50, 65);
	  } else {
	  }
	  break;
	case CC_50_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 50, 63);
	  } else {
	  }
	  break;
	case CC_51_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 51, 65);
	  } else {
	  }
	  break;
	case CC_51_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 51, 63);
	  } else {
	  }
	  break;
	case CC_52_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 52, 65);
	  } else {
	  }
	  break;
	case CC_52_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 52, 63);
	  } else {
	  }
	  break;
	case CC_53_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 53, 65);
	  } else {
	  }
	  break;
	case CC_53_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 53, 63);
	  } else {
	  }
	  break;
	case CC_54_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 54, 65);
	  } else {
	  }
	  break;
	case CC_54_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 54, 63);
	  } else {
	  }
	  break;
	case CC_55_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 55, 65);
	  } else {
	  }
	  break;
	case CC_55_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 55, 63);
	  } else {
	  }
	  break;
	case CC_56_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 56, 65);
	  } else {
	  }
	  break;
	case CC_56_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 56, 63);
	  } else {
	  }
	  break;
	case CC_57_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 57, 65);
	  } else {
	  }
	  break;
	case CC_57_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 57, 63);
	  } else {
	  }
	  break;
	case CC_58_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 58, 65);
	  } else {
	  }
	  break;
	case CC_58_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 58, 63);
	  } else {
	  }
	  break;
	case CC_59_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 59, 65);
	  } else {
	  }
	  break;
	case CC_59_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 59, 63);
	  } else {
	  }
	  break;
	case CC_60_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 60, 65);
	  } else {
	  }
	  break;
	case CC_60_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 60, 63);
	  } else {
	  }
	  break;
	case CC_61_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 61, 65);
	  } else {
	  }
	  break;
	case CC_61_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 61, 63);
	  } else {
	  }
	  break;
	case CC_62_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 62, 65);
	  } else {
	  }
	  break;
	case CC_62_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 62, 63);
	  } else {
	  }
	  break;
	case CC_63_UP:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 63, 65);
	  } else {
	  }
	  break;
	case CC_63_DN:
	  if (record->event.pressed) {
          midi_send_cc(&midi_device, 0, 63, 63);
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
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [2] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [3] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [4] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [5] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [6] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [7] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [8] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      KC_TRNS,      KC_TRNS
  //`----------------------------------------'|
  ),
    [9] = LAYOUT_default(                                                                                                                 
  //,----------------------------------------.
          KC_TRNS,      CLR_EPR,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      QK_BOOT,      KC_TRNS,
  //|------------+-------------+-------------|
          KC_TRNS,      CLR_KBD,      KC_TRNS
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