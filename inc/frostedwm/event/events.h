#ifndef __FROSTEDWM__EVENTS__EVENTS_H_
#define __FROSTEDWM__EVENTS__EVENTS_H_ 1

#include "../types.h"
#include "../input/keys.h"
#include "../input/mouse.h"

typedef uint16_t event_type_t;

#define EVENT_TYPE_GENERAL  (0)
#define EVENT_TYPE_WINDOW   (1)
#define EVENT_TYPE_MOUSE    (2)
#define EVENT_TYPE_BUTTON   (3)
#define EVENT_TYPE_KEY      (4)

#define WINDOW_MAXIMISE     (0)
#define WINDOW_MINIMISE     (1)
#define WINDOW_RESIZE       (1)

typedef struct
{
    event_type_t type;

    // Keyboard info
    key_state_t key_state;
    key_t key;

    // Mouse info
    mouse_button_state_t mouse_button_state;
    frostedwm_point2i relative_movement;
    frostedwm_point2i mouse_position;
    mouse_button_t mouse_button;
    float scroll;

    // General event info
    uint32_t info0;
    uint32_t info1;
} event_t;

struct frostedwm_context;
void frostedwm_send_event(struct frostedwm_context* ctx, event_t event);

#endif