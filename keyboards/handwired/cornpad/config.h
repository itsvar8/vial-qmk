// Copyright 2023 Var (@Var)
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

#define ENCODERS_PAD_A { GP5, GP7 }
#define ENCODERS_PAD_B { GP6, GP8 }
//#define ENCODER_RESOLUTION 4
#define ENCODER_DIRECTION_FLIP