#ifndef __OPENWM__EVENTS__EVENTS_H_
#define __OPENWM__EVENTS__EVENTS_H_ 1

#include "../types.h"
#include "../input/keys.h"
#include "../input/mouse.h"
#include <stddef.h>

typedef uint16_t event_type_t;

#define OPENWM_EVENT_TYPE_GENERAL  (0)
#define OPENWM_EVENT_TYPE_MOUSE    (1)
#define OPENWM_EVENT_TYPE_SCROLL   (2)
#define OPENWM_EVENT_TYPE_BUTTON   (3)
#define OPENWM_EVENT_TYPE_KEY      (4)

#define OPENWM_EVENT_QUEUE_BUFFER  0x100

#define OPENWM_MOUSE_EVENT(movex, movey) (openwm_event_t){.type=OPENWM_EVENT_TYPE_MOUSE,.relative_movement=OPENWM_POINT2I(movex,movey)}
#define OPENWM_SCROLL_EVENT(scroll) (openwm_event_t){.type=OPENWM_EVENT_TYPE_SCROLL,.scroll=scroll}
#define OPENWM_BUTTON_EVENT(buttonstate, button) (openwm_event_t){.type=OPENWM_EVENT_TYPE_BUTTON,.mouse_button_state=buttonstate,.mouse_button=button}
#define OPENWM_KEY_EVENT(keystate, keyb) (openwm_event_t){.type=OPENWM_EVENT_TYPE_KEY,.key_state=keystate,.key=keyb}

typedef struct
{
    event_type_t type;

    // Keyboard info
    openwm_key_state_t key_state;
    openwm_key_t key;

    // Mouse info
    openwm_mouse_button_state_t mouse_button_state;
    openwm_point2i_t relative_movement;
    openwm_point2i_t mouse_position;
    openwm_mouse_button_t mouse_button;
    float scroll;

    // General event info
    uint32_t info0;
    uint32_t info1;
} openwm_event_t;

typedef struct
{
    size_t events_buffer_size;
    openwm_event_t* events;
    size_t count;
} openwm_event_queue_t;

struct openwm_context_t;

openwm_event_queue_t* openwm_create_event_queue(struct openwm_context_t* ctx);
void openwm_dispose_event_queue(struct openwm_context_t* ctx, openwm_event_queue_t* queue);

// 1 on success, 0 on failure
int openwm_send_event(openwm_event_queue_t* queue, openwm_event_t event);
void openwm_handle_events(struct openwm_context_t* ctx);
#endif