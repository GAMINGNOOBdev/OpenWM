#ifndef __OPENWM__CONTEXT_H_
#define __OPENWM__CONTEXT_H_ 1

#include "event/events.h"
#include "fonts/font.h"
#include "drawable.h"
#include "types.h"
#include <stddef.h>

// froward declaration
struct openwm_context_t;

typedef void(*set_area_t)(openwm_point2i_t pos, openwm_point2i_t size, openwm_color_t col);
typedef void(*set_rect_t)(openwm_point2i_t pos, openwm_point2i_t size, uint8_t width, openwm_color_t col);
typedef void(*set_pixel_t)(openwm_point2i_t pos, openwm_color_t col);
typedef void*(*allocate_t)(size_t size);
typedef void*(*reallocate_t)(void* ptr, size_t size);
typedef void(*deallocate_t)(void* ptr);
typedef void(*draw_t)(struct openwm_context_t* ctx);

typedef struct openwm_context_t
{
    openwm_point2i_t framebuffer_size;
    uint64_t* framebuffer_address;
    uint64_t* font_address;
    size_t framebuffer_pitch;

    openwm_drawable_t* drawlist_start;
    openwm_drawable_t* drawlist_end;
    openwm_font_t* fontlist_start;
    openwm_font_t* fontlist_end;
    openwm_event_queue_t* event_queue;

    set_pixel_t set_pixel;
    set_area_t set_area;
    set_rect_t set_rect;
    draw_t draw;

    allocate_t allocate;
    reallocate_t reallocate;
    deallocate_t deallocate;
} openwm_context_t;

openwm_context_t* openwm_create_context(openwm_point2i_t fb_size, uint64_t* fb_addr, uint64_t* font_addr, size_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc);

void openwm_context_add_font(openwm_context_t* context, const char* name, int line_height, void* filedata);

void openwm_context_remove_font(openwm_context_t* context, const char* name);

// passing null as name gives the first available font
openwm_font_t* openwm_context_get_font(openwm_context_t* context, const char* name);

void openwm_context_add_drawable(openwm_context_t* context, openwm_drawable_t* drawable);

// returned object needs to be disposed manually
openwm_drawable_t* openwm_context_remove_drawable(openwm_context_t* context, openwm_drawable_t* drawable);

void openwm_context_set_callbacks(openwm_context_t* context, set_pixel_t px, set_area_t area, set_rect_t rect);

void openwm_dispose_context(openwm_context_t* context);

#endif