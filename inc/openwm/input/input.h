#ifndef __OPENWM__INPUT__INPUT_H_
#define __OPENWM__INPUT__INPUT_H_ 1

#include "../types.h"
#include "mouse.h"
#include "keys.h"

typedef struct openwm_input_data_t
{
    openwm_key_state_t keys[OPENWM_KEY_LAST];
    openwm_mouse_button_state_t buttons[OPENWM_MOUSE_BUTTON_LAST];
    openwm_point2i_t relative_movement;
    openwm_point2i_t mouse_position;
    float mouse_scroll;

    // misc data that can be used for events
    uint64_t info0, info1;
} openwm_input_data_t;

#endif