#include "frostedwm/drawable.h"
#include "frostedwm/event/events.h"
#include <frostedwm/context.h>

void frostedwm_draw(struct frostedwm_context* ctx)
{
    if (ctx == NULL)
        return;

    if (ctx->drawlist_start == NULL)
        return;

    for (frostedwm_drawable* drawable = ctx->drawlist_start; drawable != NULL; drawable = drawable->next)
        if (drawable->enabled && drawable->draw != NULL)
            drawable->draw(ctx, drawable);
}

frostedwm_context* frostedwm_create_context(frostedwm_point2i size, uint64_t* fb_addr, uint64_t* font_addr, size_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc)
{
    frostedwm_context* ctx = alloc(sizeof(frostedwm_context));
    *ctx = (frostedwm_context){
        .framebuffer_size = {
            .x=size.x,
            .y=size.y,
        },
        .framebuffer_pitch = fb_pitch,
        .framebuffer_address = fb_addr,
        .font_address = font_addr,
        .drawlist_start = NULL,
        .drawlist_end = NULL,
        .draw = frostedwm_draw,
        .event_queue = NULL,
        .set_pixel = 0,
        .set_area = 0,
        .set_rect = 0,
        .allocate = alloc,
        .reallocate = realloc,
        .deallocate = dealloc,
    };
    ctx->event_queue = frostedwm_create_event_queue(ctx);
    return ctx;
}

void frostedwm_context_add_drawable(frostedwm_context* context, frostedwm_drawable* drawable)
{
    if (context == NULL || drawable == NULL)
        return;

    if (context->drawlist_start == NULL)
    {
        context->drawlist_start = context->drawlist_end = drawable;
        return;
    }

    context->drawlist_end->next = drawable;
    drawable->prev = context->drawlist_end;
    context->drawlist_end = drawable;
}

frostedwm_drawable* frostedwm_context_remove_drawable(frostedwm_context* context, frostedwm_drawable* drawable)
{
    if (context == NULL || drawable == NULL)
        return NULL;

    if (context->drawlist_start == NULL)
        return NULL;

    for (frostedwm_drawable* entry = context->drawlist_start; entry != NULL; entry = entry->next)
    {
        if (entry != drawable)
            continue;

        if (entry->prev)
            entry->prev->next = entry->next;
        if (entry->next)
            entry->next->prev = entry->prev;

        if (entry == context->drawlist_start)
            context->drawlist_start = context->drawlist_end = NULL;

        return entry;
    }

    return NULL;
}

void frostedwm_context_set_callbacks(frostedwm_context* context, set_pixel_t px, set_area_t area, set_rect_t rect)
{
    if (context == NULL)
        return;

    context->set_pixel = px;
    context->set_area = area;
    context->set_rect = rect;
}

void frostedwm_dispose_context(frostedwm_context* context)
{
    if (context == NULL)
        return;

    for (frostedwm_drawable* drawable = context->drawlist_start; drawable != NULL; drawable = drawable->next)
        frostedwm_dispose_drawable(context, drawable);

    frostedwm_dispose_event_queue(context, context->event_queue);
    context->deallocate(context);
}
