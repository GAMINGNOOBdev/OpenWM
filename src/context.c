#include "openwm/drawable.h"
#include "openwm/event/events.h"
#include "openwm/fonts/font.h"
#include <openwm/context.h>

void openwm_draw(struct openwm_context* ctx)
{
    if (ctx == NULL)
        return;

    if (ctx->drawlist_start == NULL)
        return;

    for (openwm_drawable* drawable = ctx->drawlist_start; drawable != NULL; drawable = drawable->next)
        if (drawable->enabled && drawable->draw != NULL)
            drawable->draw(ctx, drawable);
}

openwm_context* openwm_create_context(openwm_point2i size, uint64_t* fb_addr, uint64_t* font_addr, size_t fb_pitch, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc)
{
    openwm_context* ctx = alloc(sizeof(openwm_context));
    *ctx = (openwm_context){
        .framebuffer_size = {
            .x=size.x,
            .y=size.y,
        },
        .framebuffer_pitch = fb_pitch,
        .framebuffer_address = fb_addr,
        .font_address = font_addr,
        .drawlist_start = NULL,
        .drawlist_end = NULL,
        .draw = openwm_draw,
        .event_queue = NULL,
        .set_pixel = 0,
        .set_area = 0,
        .set_rect = 0,
        .allocate = alloc,
        .reallocate = realloc,
        .deallocate = dealloc,
    };
    ctx->event_queue = openwm_create_event_queue(ctx);
    // init_ssfn(ctx->framebuffer_address, ctx->framebuffer_size.x, ctx->framebuffer_size.y, ctx->framebuffer_pitch, 1, ctx->font_address);
    return ctx;
}

void openwm_context_add_font(openwm_context* context, const char* name, int line_height, void* filedata)
{
    if (context == NULL || name == NULL || filedata == NULL)
        return;

    openwm_font_t* font = openwm_create_font(context, name, line_height, filedata);
    if (font == NULL)
        return;

    if (context->fontlist_start == NULL)
    {
        context->fontlist_start = context->fontlist_end = font;
        return;
    }

    context->fontlist_end->next = font;
    font->prev = context->fontlist_end;
    context->fontlist_end = font;
}

// i don't want to use any outside dependencies for this one, seriously
int dummy_strcmp(const char* str0, const char* str1)
{
    char* s0 = (char*)str0;
    char* s1 = (char*)str1;
    while (*s0 != 0 && *s1 != 0 && *s0 == *s1)
    {
        s0++;
        s1++;
    }
    return *s0 - *s1;
}

void openwm_context_remove_font(openwm_context* context, const char* name)
{
    if (context == NULL || name == NULL)
        return;

    if (context->fontlist_start == NULL)
        return;

    for (openwm_font_t* entry = context->fontlist_start; entry != NULL; entry = entry->next)
    {
        if (dummy_strcmp(entry->name, name))
            continue;

        if (entry->prev)
            entry->prev->next = entry->next;
        if (entry->next)
            entry->next->prev = entry->prev;

        if (entry == context->fontlist_start)
            context->fontlist_start = context->fontlist_end = NULL;

        openwm_dispose_font(context, entry);

        break;
    }

    return;
}

openwm_font_t* openwm_context_get_font(openwm_context* context, const char* name)
{
    if (context == NULL)
        return NULL;

    if (context->fontlist_start == NULL)
        return NULL;

    if (name == NULL)
        return context->fontlist_start;

    for (openwm_font_t* entry = context->fontlist_start; entry != NULL; entry = entry->next)
    {
        if (dummy_strcmp(entry->name, name))
            continue;

        return entry;
    }

    return NULL;
}

void openwm_context_add_drawable(openwm_context* context, openwm_drawable* drawable)
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

openwm_drawable* openwm_context_remove_drawable(openwm_context* context, openwm_drawable* drawable)
{
    if (context == NULL || drawable == NULL)
        return NULL;

    if (context->drawlist_start == NULL)
        return NULL;

    for (openwm_drawable* entry = context->drawlist_start; entry != NULL; entry = entry->next)
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

void openwm_context_set_callbacks(openwm_context* context, set_pixel_t px, set_area_t area, set_rect_t rect)
{
    if (context == NULL)
        return;

    context->set_pixel = px;
    context->set_area = area;
    context->set_rect = rect;
}

void openwm_dispose_context(openwm_context* context)
{
    if (context == NULL)
        return;

    for (openwm_drawable* drawable = context->drawlist_start; drawable != NULL; drawable = drawable->next)
        openwm_dispose_drawable(context, drawable);

    openwm_dispose_event_queue(context, context->event_queue);
    context->deallocate(context);
}
