#ifndef __FROSTEDWM__DRAWABLE_H_
#define __FROSTEDWM__DRAWABLE_H_ 1

#include "types.h"
#include "event/events.h"

struct frostedwm_context;
struct frostedwm_drawable;

typedef void(*frostedwm_drawable_draw_t)(struct frostedwm_context* ctx, struct frostedwm_drawable* drawable);
typedef void (*frostedwm_on_event_handle_t)(struct frostedwm_drawable *self, frostedwm_event_t event);
typedef void (*frostedwm_on_mouse_scroll_t)(struct frostedwm_drawable *self, frostedwm_event_t event);
typedef void (*frostedwm_on_mouse_button_t)(struct frostedwm_drawable *self, frostedwm_event_t event);
typedef void (*frostedwm_on_mouse_move_t)(struct frostedwm_drawable *self, frostedwm_event_t event);
typedef void (*frostedwm_on_key_press_t)(struct frostedwm_drawable *self, frostedwm_event_t event);

typedef struct frostedwm_drawable
{
    frostedwm_point2i pos;
    frostedwm_point2i size;
    frostedwm_drawable_draw_t draw;
    uint8_t enabled;
    void* custom_data;
    struct frostedwm_drawable *children_start;
    struct frostedwm_drawable *children_end;

    frostedwm_on_event_handle_t on_event_handle;
    frostedwm_on_mouse_scroll_t on_mouse_scroll;
    frostedwm_on_mouse_button_t on_mouse_button;
    frostedwm_on_mouse_move_t on_mouse_move;
    frostedwm_on_key_press_t on_key_press;
    
    struct frostedwm_drawable *prev;
    struct frostedwm_drawable *next;
} frostedwm_drawable;

frostedwm_drawable* frostedwm_create_drawable(struct frostedwm_context* ctx, frostedwm_point2i pos, frostedwm_point2i size, frostedwm_drawable_draw_t draw, void* custom_data);
void frostedwm_drawable_add_child(frostedwm_drawable* drawable, frostedwm_drawable* child);
void frostedwm_dispose_drawable(struct frostedwm_context* ctx, frostedwm_drawable* drawable);

#endif