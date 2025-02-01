#include "openwm/types.h"
#include <openwm/input/mouse.h>
#include <openwm/context.h>
#include <stdint.h>

extern openwm_context_t* global_context;

openwm_point2i_t openwm_mouse_get_position(void)
{
    if (global_context == NULL)
        return OPENWM_POINT2I(0, 0);

    return global_context->input_data.mouse_position;
}

openwm_mouse_button_state_t openwm_mouse_get_button(openwm_mouse_button_t button)
{
    if (global_context == NULL || button == OPENWM_MOUSE_BUTTON_NONE)
        return 0;

    return global_context->input_data.buttons[button];
}