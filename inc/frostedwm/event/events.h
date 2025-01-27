#ifndef __FROSTEDWM__EVENTS__EVENTS_H_
#define __FROSTEDWM__EVENTS__EVENTS_H_ 1

#include "../types.h"
#include "../input/keys.h"
#include "../input/mouse.h"
#include <stddef.h>

typedef uint16_t event_type_t;

#define EVENT_TYPE_GENERAL  (0)
#define EVENT_TYPE_WINDOW   (1)
#define EVENT_TYPE_MOUSE    (2)
#define EVENT_TYPE_SCROLL   (3)
#define EVENT_TYPE_BUTTON   (4)
#define EVENT_TYPE_KEY      (5)

#define WINDOW_MAXIMISE     (0)
#define WINDOW_MINIMISE     (1)
#define WINDOW_RESIZE       (1)

#define EVENT_QUEUE_BUFFER  0x100

typedef struct
{
    event_type_t type;

    // Keyboard info
    frostedwm_key_state_t key_state;
    frostedwm_key_t key;

    // Mouse info
    frostedwm_mouse_button_state_t mouse_button_state;
    frostedwm_point2i relative_movement;
    frostedwm_point2i mouse_position;
    frostedwm_mouse_button_t mouse_button;
    float scroll;

    // General event info
    uint32_t info0;
    uint32_t info1;
} frostedwm_event_t;

typedef struct
{
    size_t events_buffer_size;
    frostedwm_event_t* events;
    size_t count;
} frostedwm_event_queue_t;

struct frostedwm_context;

frostedwm_event_queue_t* frostedwm_create_event_queue(struct frostedwm_context* ctx);
void frostedwm_dispose_event_queue(struct frostedwm_context* ctx, frostedwm_event_queue_t* queue);

// 1 on success, 0 on failure
int frostedwm_send_event(frostedwm_event_queue_t* queue, frostedwm_event_t event);
void frostedwm_handle_events(struct frostedwm_context* ctx);
#endif