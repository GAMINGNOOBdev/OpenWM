#include <openwm/input/keys.h>
#include <openwm/context.h>
#include <stdint.h>

extern openwm_context_t* global_context;

openwm_key_state_t openwm_keyboard_get_key(openwm_key_t key)
{
    if (global_context == NULL || key == (uint16_t)-1)
        return 0;

    return global_context->input_data.keys[key];
}