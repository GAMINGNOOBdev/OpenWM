#ifndef __FROSTEDWM__CONTEXT_H_
#define __FROSTEDWM__CONTEXT_H_ 1

#include "types.h"

typedef struct 
{
    frostedwm_framebuffer framebuffer;
    void* frontbuffer_address;
    void* backbuffer_address;

    void (*set_pixel)(frostedwm_point2i pos, frostedwm_color col);
    void (*set_area)(frostedwm_point2i pos, frostedwm_point2i size, frostedwm_color col);

    void (*draw_frame)();
} frostedwm_context;

frostedwm_context frostedwm_create_context(void* framebuffer0, void* framebuffer1, frostedwm_point2i size);

#endif