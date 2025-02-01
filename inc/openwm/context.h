#ifndef __OPENWM__CONTEXT_H_
#define __OPENWM__CONTEXT_H_ 1

#include "event/events.h"
#include "input/input.h"
#include "fonts/font.h"
#include "drawable.h"
#include "style.h"
#include "types.h"
#include <stddef.h>

// froward declaration
struct openwm_context_t;

typedef void(*set_area_t)(openwm_point2i_t pos, openwm_point2i_t size, openwm_color_t col);
typedef void(*set_rect_t)(openwm_point2i_t pos, openwm_point2i_t size, uint16_t width, openwm_color_t col);
typedef void(*set_pixel_t)(openwm_point2i_t pos, openwm_color_t col);
typedef void(*clear_screen_t)(openwm_color_t col);
typedef void*(*allocate_t)(size_t size);
typedef void*(*reallocate_t)(void* ptr, size_t size);
typedef void(*deallocate_t)(void* ptr);
typedef double(*ceil_t)(double x);
typedef double(*fmod_t)(double x, double y);
typedef double(*acos_t)(double x);
typedef double(*cos_t)(double x);
typedef double(*pow_t)(double x, double y);
typedef double(*sqrt_t)(double x);
typedef double(*floor_t)(double x);
typedef void(*draw_t)(struct openwm_context_t* ctx);

typedef struct openwm_api_callbacks_t
{
    ceil_t ceil;
    fmod_t fmod;
    acos_t acos;
    cos_t cos;
    pow_t pow;
    sqrt_t sqrt;
    floor_t floor;
} openwm_api_callbacks_t;

typedef struct openwm_context_t
{
    openwm_point2i_t framebuffer_size;
    openwm_style_t style;

    openwm_drawable_t* drawlist_start;
    openwm_drawable_t* drawlist_end;
    size_t drawlist_size;
    openwm_font_t* fontlist_start;
    openwm_font_t* fontlist_end;
    openwm_event_queue_t* event_queue;

    clear_screen_t clear_screen;
    set_pixel_t set_pixel;
    set_area_t set_area;
    set_rect_t set_rect;
    draw_t draw;

    allocate_t allocate;
    reallocate_t reallocate;
    deallocate_t deallocate;
    openwm_api_callbacks_t api_callbacks;
    openwm_input_data_t input_data;
} openwm_context_t;

openwm_context_t* openwm_create_context(openwm_point2i_t fb_size, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc);

void openwm_context_add_font(openwm_context_t* context, const char* name, int line_height, void* filedata);

void openwm_context_remove_font(openwm_context_t* context, const char* name);

// passing null as name gives the first available font
openwm_font_t* openwm_context_get_font(openwm_context_t* context, const char* name);

void openwm_context_add_drawable(openwm_context_t* context, openwm_drawable_t* drawable);

// returned object needs to be disposed manually
openwm_drawable_t* openwm_context_remove_drawable(openwm_context_t* context, openwm_drawable_t* drawable);

void openwm_context_set_callbacks(openwm_context_t* context, set_pixel_t px, set_area_t area, set_rect_t rect, clear_screen_t clear);

void openwm_context_set_api_callbacks(openwm_context_t* context, openwm_api_callbacks_t cb);

void openwm_dispose_context(openwm_context_t* context);

#endif
