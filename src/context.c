#include <frostedwm/event/handler.h>
#include <frostedwm/context.h>

frostedwm_context* frostedwm_create_context(frostedwm_point2i size, uint8_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc)
{
    frostedwm_context* ctx = alloc(sizeof(frostedwm_context));
    *ctx = (frostedwm_context){
        .framebuffer_size = {
            .x=size.x,
            .y=size.y,
        },
        .framebuffer_pitch = fb_pitch,
        .handlers = NULL,
        .draw = 0,
        .set_pixel = 0,
        .set_area = 0,
        .allocate = alloc,
        .reallocate = realloc,
        .deallocate = dealloc,
    };
    handler_list_t* handlers = frostedwm_create_handler_list(ctx);
    ctx->handlers = handlers;
    return ctx;
}

void frostedwm_context_set_callbacks(frostedwm_context* context, set_pixel_t px, set_area_t area)
{
    if (context == NULL)
        return;

    context->set_pixel = px;
    context->set_area = area;
}
