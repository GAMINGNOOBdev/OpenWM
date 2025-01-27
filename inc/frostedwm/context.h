#ifndef __FROSTEDWM__CONTEXT_H_
#define __FROSTEDWM__CONTEXT_H_ 1

#include "event/events.h"
#include "drawable.h"
#include "types.h"
#include <stddef.h>

// froward declaration
struct frostedwm_context;

typedef void(*set_area_t)(frostedwm_point2i pos, frostedwm_point2i size, frostedwm_color col);
typedef void(*set_rect_t)(frostedwm_point2i pos, frostedwm_point2i size, uint8_t width, frostedwm_color col);
typedef void(*set_pixel_t)(frostedwm_point2i pos, frostedwm_color col);
typedef void*(*allocate_t)(size_t size);
typedef void*(*reallocate_t)(void* ptr, size_t size);
typedef void(*deallocate_t)(void* ptr);
typedef void(*draw_t)(struct frostedwm_context* ctx);

typedef struct frostedwm_context
{
    frostedwm_point2i framebuffer_size;
    size_t framebuffer_pitch;

    frostedwm_drawable* drawlist_start;
    frostedwm_drawable* drawlist_end;
    frostedwm_event_queue_t* event_queue;

    set_pixel_t set_pixel;
    set_area_t set_area;
    set_rect_t set_rect;
    draw_t draw;

    allocate_t allocate;
    reallocate_t reallocate;
    deallocate_t deallocate;
} frostedwm_context;

frostedwm_context* frostedwm_create_context(frostedwm_point2i fb_size, size_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc);

void frostedwm_context_add_drawable(frostedwm_context* context, frostedwm_drawable* drawable);

// returned object needs to be disposed manually
frostedwm_drawable* frostedwm_context_remove_drawable(frostedwm_context* context, frostedwm_drawable* drawable);

void frostedwm_context_set_callbacks(frostedwm_context* context, set_pixel_t px, set_area_t area, set_rect_t rect);

void frostedwm_dispose_context(frostedwm_context* context);

#endif