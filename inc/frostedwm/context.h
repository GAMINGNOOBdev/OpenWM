#ifndef __FROSTEDWM__CONTEXT_H_
#define __FROSTEDWM__CONTEXT_H_ 1

#include "types.h"
#include <stddef.h>

typedef void(*set_area_t)(frostedwm_point2i pos, frostedwm_point2i size, frostedwm_color col);
typedef void(*set_pixel_t)(frostedwm_point2i pos, frostedwm_color col);
typedef void*(*allocate_t)(size_t size);
typedef void(*deallocate_t)(void* ptr);
typedef void(*draw_t)(void);

typedef struct 
{
    frostedwm_framebuffer framebuffer;
    void* frontbuffer_address;
    void* backbuffer_address;

    set_pixel_t set_pixel;
    set_area_t set_area;
    draw_t draw;

    allocate_t allocate;
    deallocate_t deallocate;
} frostedwm_context;

frostedwm_context* frostedwm_create_context(void* framebuffer0, void* framebuffer1, frostedwm_point2i size);

void frostedwm_context_set_callbacks(frostedwm_context* context, set_pixel_t px, set_area_t area, allocate_t alloc, deallocate_t dealloc);

#endif