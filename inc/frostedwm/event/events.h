#ifndef __FROSTEDWM__EVENTS_H_
#define __FROSTEDWM__EVENTS_H_ 1

#include "../types.h"
#include "../input/keys.h"
#include "../input/mouse.h"

typedef uint16_t event_type_t;

#define EVENT_TYPE_GENERAL  (0)
#define EVENT_TYPE_WINDOW   (1)
#define EVENT_TYPE_MOUSE    (2)
#define EVENT_TYPE_KEY      (3)

typedef struct
{
    event_type_t type;

    // Keyboard info
    key_state_t key_state;
    key_t key;

    // Mouse info
    mouse_button_state_t mouse_button_state;
    frostedwm_point2i mouse_position;
    mouse_button_t mouse_button;

    // General event info
    uint32_t info;
} event_t;

#endif