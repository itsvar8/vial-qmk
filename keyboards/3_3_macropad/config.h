// Copyright 2022 Var (@.)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define ENCODERS_PAD_A { D3, F5, B3 }
#define ENCODERS_PAD_B { D2, F6, B1 }
#define ENCODER_RESOLUTION 4
#define ENCODER_DIRECTION_FLIP

//#define FORCE_NKRO

#define RGB_DI_PIN D1
#define DRIVER_LED_TOTAL 6

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_SPLASH