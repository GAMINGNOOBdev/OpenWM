#include "openwm/input/input.h"
#include <openwm/drawable.h>
#include <openwm/event/events.h>
#include <openwm/fonts/font.h>
#include <openwm/types.h>
#include <openwm/context.h>
#include <string.h>

openwm_context_t* global_context = NULL;

void openwm_draw(openwm_context_t* ctx)
{
    if (ctx == NULL)
        return;

    if (ctx->drawlist_start == NULL)
        return;

    openwm_handle_events(ctx);

    // clear screen
    if (ctx->clear_screen)
        ctx->clear_screen(OPENWM_COLOR_RGBA(0, 0, 0, 1));

    for (openwm_drawable_t* drawable = ctx->drawlist_start; drawable != NULL; drawable = drawable->next)
    {
        if (drawable->draw != NULL && !drawable->hidden)
            drawable->draw(drawable);
    }
}

openwm_context_t* openwm_create_context(openwm_point2i_t size, allocate_t alloc, reallocate_t realloc, deallocate_t dealloc)
{
    if (global_context != NULL)
        return global_context;

    openwm_context_t* ctx = alloc(sizeof(openwm_context_t));
    if (ctx == NULL)
        return NULL;

    global_context = ctx;

    *ctx = (openwm_context_t){
        .framebuffer_size = {
            .x=size.x,
            .y=size.y,
        },
        .style = {
            .border = OPENWM_COLOR_RGB(0x88,0x22,0x88),
            .border_unfocussed = OPENWM_COLOR_RGB(0x44,0x22,0x44),
            .border_width = 2,
            .title_bar = OPENWM_COLOR_RGB(0x22,0x22,0x22),
            .title_bar_height = 20,
            .contents = OPENWM_COLOR_RGB(0x11,0x11,0x11),
            .text = OPENWM_COLOR_WHITE,
            .text_height = 12,
            .title_text = OPENWM_COLOR_WHITE,
            .title_text_height = 14
        },
        .drawlist_start = NULL,
        .drawlist_end = NULL,
        .drawlist_size = 0,
        .draw = openwm_draw,
        .event_queue = NULL,
        .clear_screen = 0,
        .set_pixel = 0,
        .set_area = 0,
        .set_rect = 0,
        .allocate = alloc,
        .reallocate = realloc,
        .deallocate = dealloc,
        .api_callbacks = {
            .ceil = 0,
            .fmod = 0,
            .acos = 0,
            .cos = 0,
            .pow = 0,
            .sqrt = 0,
            .floor = 0,
        },
    };
    memset(&ctx->input_data, 0, sizeof(openwm_input_data_t));
    ctx->event_queue = openwm_create_event_queue(ctx);
    return ctx;
}

void openwm_context_add_font(openwm_context_t* context, const char* name, int line_height, void* filedata)
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

void openwm_context_remove_font(openwm_context_t* context, const char* name)
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

openwm_font_t* openwm_context_get_font(openwm_context_t* context, const char* name)
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

void openwm_context_add_drawable(openwm_context_t* context, openwm_drawable_t* drawable)
{
    if (context == NULL || drawable == NULL)
        return;

    drawable->draw_index = context->drawlist_size;
    context->drawlist_size++;

    if (context->drawlist_start == NULL)
    {
        context->drawlist_start = context->drawlist_end = drawable;
        return;
    }

    context->drawlist_end->next = drawable;
    drawable->prev = context->drawlist_end;
    context->drawlist_end = drawable;
}

openwm_drawable_t* openwm_context_remove_drawable(openwm_context_t* context, openwm_drawable_t* drawable)
{
    if (context == NULL || drawable == NULL)
        return NULL;

    if (context->drawlist_start == NULL)
        return NULL;

    for (openwm_drawable_t* entry = context->drawlist_start; entry != NULL; entry = entry->next)
    {
        if (entry != drawable)
            continue;

        context->drawlist_size--;

        if (entry->prev)
            entry->prev->next = entry->next;
        if (entry->next)
            entry->next->prev = entry->prev;

        if (entry == context->drawlist_start)
            context->drawlist_start = context->drawlist_end = NULL;

        entry->draw_index = -1;
        for (openwm_drawable_t* sentry = entry->next; sentry != NULL; sentry = sentry->next)
            entry->draw_index--;

        return entry;
    }

    return NULL;
}

void openwm_context_set_callbacks(openwm_context_t* context, set_pixel_t px, set_area_t area, set_rect_t rect, clear_screen_t clear)
{
    if (context == NULL)
        return;

    context->clear_screen = clear;
    context->set_pixel = px;
    context->set_area = area;
    context->set_rect = rect;
}

void openwm_context_set_api_callbacks(openwm_context_t* context, openwm_api_callbacks_t cb)
{
    if (context == NULL)
        return;

    context->api_callbacks = cb;
}

void openwm_dispose_context(openwm_context_t* context)
{
    if (context == NULL)
        return;

    for (openwm_drawable_t* drawable = context->drawlist_start; drawable != NULL; drawable = drawable->next)
        openwm_dispose_drawable(context, drawable);

    openwm_dispose_event_queue(context, context->event_queue);
    context->deallocate(context);
}
