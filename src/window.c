#include "frostedwm/drawable.h"
#include "frostedwm/types.h"
#include <frostedwm/context.h>
#include <frostedwm/window.h>
#include <frostedwm/fonts/fonts.h>

void frostedwm_window_draw(struct frostedwm_context* ctx, struct frostedwm_drawable* drawable)
{
    frostedwm_window* window = (frostedwm_window*)drawable;

    if (window == NULL)
        return;

    frostedwm_point2i pos = window->drawable.pos;
    frostedwm_point2i size = window->drawable.size;

    // draw border
    ctx->set_rect(pos, size, WINDOW_BORDER_WIDTH, COLOR_BORDER_BAR);
    pos.x += WINDOW_BORDER_WIDTH;
    pos.y += WINDOW_BORDER_WIDTH;
    size.x -= WINDOW_BORDER_WIDTH*2;
    size.y -= WINDOW_BORDER_WIDTH*2;

    // draw title bar (also display text later)
    ctx->set_area(pos, FROSTEDWM_POINT2I(size.x, WINDOW_TITLEBAR_HEIGHT), COLOR_TITLE_BAR_1);
    pos.y += WINDOW_TITLEBAR_HEIGHT/2;
    size.y -= WINDOW_TITLEBAR_HEIGHT/2;

    // init_ssfn(ctx->framebuffer_address, ctx->framebuffer_size.x, ctx->framebuffer_size.y, ctx->framebuffer_pitch, 1, ctx->font_address);
    // ssfn_print(window->title);

    ctx->set_area(pos, FROSTEDWM_POINT2I(size.x, WINDOW_TITLEBAR_HEIGHT), COLOR_TITLE_BAR_2);
    pos.y += WINDOW_TITLEBAR_HEIGHT/2;
    size.y -= WINDOW_TITLEBAR_HEIGHT/2;

    // draw border around (just below) the title bar
    // ctx->set_area(pos, FROSTEDWM_POINT2I(size.x, WINDOW_BORDER_WIDTH), COLOR_BORDER_BAR);
    // pos.y += WINDOW_BORDER_WIDTH;
    // size.y -= WINDOW_BORDER_WIDTH;

    // draw window background
    ctx->set_area(pos, size, COLOR_CONTENTS);

    // draw contents
    for (frostedwm_drawable* drawable = window->drawable.children_start; drawable != NULL; drawable = drawable->next)
        if (drawable->enabled && drawable->draw != NULL)
            drawable->draw(ctx, drawable);
}

frostedwm_window* frostedwm_create_window(struct frostedwm_context* ctx, const char* title, frostedwm_point2i pos, frostedwm_point2i size)
{
    if (ctx == NULL || title == NULL)
        return NULL;

    frostedwm_window* window = ctx->allocate(sizeof(frostedwm_window));
    if (window == NULL)
        return NULL;

    window->drawable = (frostedwm_drawable){
        .pos = pos,
        .size = size,
        .draw = frostedwm_window_draw,
        .enabled = 1,
        .custom_data = NULL,
        .children_start = NULL,
        .children_end = NULL,
        .prev = NULL,
        .next = NULL,
    };
    window->title = (char*)title;

    frostedwm_context_add_drawable(ctx, (frostedwm_drawable*)window);

    return window;
}

void frostedwm_window_add_child(frostedwm_window* window, frostedwm_drawable* child)
{
    if (window == NULL || child == NULL)
        return;

    if (window->drawable.children_start == NULL)
    {
        window->drawable.children_start = window->drawable.children_end = child;
        return;
    }

    window->drawable.children_end->next = child;
    child->prev = window->drawable.children_end;
    window->drawable.children_end = child;
}

void frostedwm_dispose_window(struct frostedwm_context* ctx, frostedwm_window* window)
{
    if (window == NULL)
        return;

    frostedwm_context_remove_drawable(ctx, (frostedwm_drawable*)window);

    if (window->drawable.children_start != NULL)
    {
        for (frostedwm_drawable* child = window->drawable.children_start; child != NULL; child = child->next)
            frostedwm_dispose_drawable(ctx, child);
    }

    if (window->drawable.custom_data != NULL)
        ctx->deallocate(window->drawable.custom_data);

    ctx->deallocate(window);
}
