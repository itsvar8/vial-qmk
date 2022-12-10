#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
{
// Key Matrix to LED Index
  { 0, 5 },
  { 1, 4 },
  { 2, 3 }
}, {
// LED Index to Physical Position
    { 0, 0},
	{ 0, 32},
	{ 0, 64},
	
	{ 224,64 },
	{ 224,32 },
	{ 224, 0}
}, {
// LED Index to Flag
  4, 4, 4, 4, 4, 4
}
};

#endif