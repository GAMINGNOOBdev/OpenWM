#include <frostedwm/context.h>

frostedwm_context ctx = {
    .framebuffer = {
        .size = {0,0},
        .address = NULL,
    },
    .frontbuffer_address = NULL,
    .backbuffer_address = NULL,
    .draw = 0,
    .set_pixel = 0,
    .set_area = 0,
    .allocate = 0,
    .deallocate = 0,
};

frostedwm_context* frostedwm_create_context(void* framebuffer0, void* framebuffer1, frostedwm_point2i size)
{
    ctx = (frostedwm_context){
        .framebuffer = {
            .size = size,
            .address = framebuffer0,
        },
        .frontbuffer_address = framebuffer0,
        .backbuffer_address = framebuffer1,
        .draw = 0,
        .set_pixel = 0,
        .set_area = 0,
        .allocate = 0,
        .deallocate = 0,
    };
    return &ctx;
}

void frostedwm_context_set_callbacks(frostedwm_context* context, set_pixel_t px, set_area_t area, allocate_t alloc, deallocate_t dealloc)
{
    if (context == NULL)
        return;

    context->set_pixel = px;
    context->set_area = area;
    context->allocate = alloc;
    context->deallocate = dealloc;
}

int _start()
{
    
    return 0x10;
}
