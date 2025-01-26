#ifndef __FROSTEDWM__DRAWABLE_H_
#define __FROSTEDWM__DRAWABLE_H_ 1

#include "types.h"

struct frostedwm_context;
struct frostedwm_drawable;

typedef void(*frostedwm_drawable_draw_t)(struct frostedwm_context* ctx, struct frostedwm_drawable* drawable);

typedef struct frostedwm_drawable
{
    frostedwm_point2i pos;
    frostedwm_point2i size;
    frostedwm_drawable_draw_t draw;
    uint8_t enabled;
    void* custom_data;
    struct frostedwm_drawable *children_start;
    struct frostedwm_drawable *children_end;

    struct frostedwm_drawable *prev;
    struct frostedwm_drawable *next;
} frostedwm_drawable;

frostedwm_drawable* frostedwm_create_drawable(struct frostedwm_context* ctx, frostedwm_point2i pos, frostedwm_point2i size, frostedwm_drawable_draw_t draw, void* custom_data);
void frostedwm_drawable_add_child(frostedwm_drawable* drawable, frostedwm_drawable* child);
void frostedwm_dispose_drawable(struct frostedwm_context* ctx, frostedwm_drawable* drawable);

#endif