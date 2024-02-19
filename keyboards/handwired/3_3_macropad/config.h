// Copyright 2022 Var (@itsvar8)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#define ENCODERS_PAD_A { D3, F5, B3 }
#define ENCODERS_PAD_B { D2, F6, B1 }
#define ENCODER_RESOLUTION 4
#define ENCODER_DEFAULT_POS 0x3
#define ENCODER_DIRECTION_FLIP

//#define FORCE_NKRO

#define WS2812_DI_PIN D1
#define DRIVER_LED_TOTAL 6
#define RGB_MATRIX_LED_COUNT 6

//#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//#define RGB_MATRIX_KEYPRESSES

#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
//#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
//#define ENABLE_RGB_MATRIX_SPLASH

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_PINWHEEL
#define RGB_MATRIX_DEFAULT_SPD 50 // Sets the default animation speed, if none has been set

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT