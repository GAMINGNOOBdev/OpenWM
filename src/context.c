#include <frostedwm/context.h>

frostedwm_context frostedwm_create_context(void* framebuffer0, void* framebuffer1, frostedwm_point2i size)
{
    frostedwm_context ctx = {
        .framebuffer = {
            .size = size,
            .address = framebuffer0,
        },
        .frontbuffer_address = framebuffer0,
        .backbuffer_address = framebuffer1,
        .draw_frame = 0,
        .set_pixel = 0,
        .set_area = 0,
    };
    return ctx;
}

#pragma GCC push_options
#pragma GCC optimize ("O0")

int _start(void){

    return 0;
}

#pragma GCC pop_options