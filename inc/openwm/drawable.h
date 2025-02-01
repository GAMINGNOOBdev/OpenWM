#ifndef __OPENWM__DRAWABLE_H_
#define __OPENWM__DRAWABLE_H_ 1

#include "types.h"
#include "event/events.h"

struct openwm_context_t;
struct openwm_drawable_t;

typedef void(*openwm_drawable_draw_t)(struct openwm_drawable_t* drawable);
typedef void (*openwm_on_event_handle_t)(struct openwm_drawable_t *self, openwm_event_t event);
typedef void (*openwm_on_mouse_scroll_t)(struct openwm_drawable_t *self, openwm_event_t event);
typedef void (*openwm_on_mouse_button_t)(struct openwm_drawable_t *self, openwm_event_t event);
typedef void (*openwm_on_mouse_move_t)(struct openwm_drawable_t *self, openwm_event_t event);
typedef void (*openwm_on_key_press_t)(struct openwm_drawable_t *self, openwm_event_t event);

typedef struct openwm_drawable_t
{
    openwm_point2i_t pos;
    openwm_point2i_t size;
    openwm_drawable_draw_t draw;
    uint8_t enabled;
    void* custom_data;
    struct openwm_drawable_t *children_start;
    struct openwm_drawable_t *children_end;

    openwm_on_event_handle_t on_event_handle;
    openwm_on_mouse_scroll_t on_mouse_scroll;
    openwm_on_mouse_button_t on_mouse_button;
    openwm_on_mouse_move_t on_mouse_move;
    openwm_on_key_press_t on_key_press;
    
    struct openwm_context_t* ctx;
    struct openwm_drawable_t *prev;
    struct openwm_drawable_t *next;
} openwm_drawable_t;

openwm_drawable_t* openwm_create_drawable(struct openwm_context_t* ctx, openwm_point2i_t pos, openwm_point2i_t size, openwm_drawable_draw_t draw, void* custom_data);
void openwm_drawable_add_child(openwm_drawable_t* drawable, openwm_drawable_t* child);
void openwm_dispose_drawable(struct openwm_context_t* ctx, openwm_drawable_t* drawable);

#endif