#ifndef __OPENWM__CONTEXT_H_
#define __OPENWM__CONTEXT_H_ 1

#include "event/events.h"
#include "drawable.h"
#include "types.h"
#include <stddef.h>

// froward declaration
struct openwm_context;

typedef void(*set_area_t)(openwm_point2i pos, openwm_point2i size, openwm_color col);
typedef void(*set_rect_t)(openwm_point2i pos, openwm_point2i size, uint8_t width, openwm_color col);
typedef void(*set_pixel_t)(openwm_point2i pos, openwm_color col);
typedef void*(*allocate_t)(size_t size);
typedef void*(*reallocate_t)(void* ptr, size_t size);
typedef void(*deallocate_t)(void* ptr);
typedef void(*draw_t)(struct openwm_context* ctx);

typedef struct openwm_context
{
    openwm_point2i framebuffer_size;
    uint64_t* framebuffer_address;
    uint64_t* font_address;
    size_t framebuffer_pitch;

    openwm_drawable* drawlist_start;
    openwm_drawable* drawlist_end;
    openwm_event_queue_t* event_queue;

    set_pixel_t set_pixel;
    set_area_t set_area;
    set_rect_t set_rect;
    draw_t draw;

    allocate_t allocate;
    reallocate_t reallocate;
    deallocate_t deallocate;
} openwm_context;

openwm_context* openwm_create_context(openwm_point2i fb_size, uint64_t* fb_addr, uint64_t* font_addr, size_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc);

void openwm_context_add_drawable(openwm_context* context, openwm_drawable* drawable);

// returned object needs to be disposed manually
openwm_drawable* openwm_context_remove_drawable(openwm_context* context, openwm_drawable* drawable);

void openwm_context_set_callbacks(openwm_context* context, set_pixel_t px, set_area_t area, set_rect_t rect);

void openwm_dispose_context(openwm_context* context);

#endif