#ifndef __FROSTEDWM__CONTEXT_H_
#define __FROSTEDWM__CONTEXT_H_ 1

#include "types.h"
#include <stddef.h>

typedef void(*set_area_t)(frostedwm_point2i pos, frostedwm_point2i size, frostedwm_color col);
typedef void(*set_pixel_t)(frostedwm_point2i pos, frostedwm_color col);
typedef void*(*allocate_t)(size_t size);
typedef void*(*reallocate_t)(void* ptr, size_t size);
typedef void(*deallocate_t)(void* ptr);
typedef void(*draw_t)(void);

// froward declaration
struct handler_list_t;

typedef struct frostedwm_context
{
    frostedwm_point2i framebuffer_size;
    uint8_t framebuffer_pitch;

    struct handler_list_t* handlers;

    set_pixel_t set_pixel;
    set_area_t set_area;
    draw_t draw;

    allocate_t allocate;
    reallocate_t reallocate;
    deallocate_t deallocate;
} frostedwm_context;

frostedwm_context* frostedwm_create_context(frostedwm_point2i fb_size, uint8_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc);

void frostedwm_context_set_callbacks(frostedwm_context* context, set_pixel_t px, set_area_t area);

#endif