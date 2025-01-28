#include "openwm/drawable.h"
#include "openwm/types.h"
#include <openwm/context.h>
#include <openwm/window.h>
#include <openwm/fonts/fonts.h>

void openwm_window_draw(struct openwm_context* ctx, struct openwm_drawable* drawable)
{
    openwm_window* window = (openwm_window*)drawable;

    if (window == NULL)
        return;

    openwm_point2i pos = window->drawable.pos;
    openwm_point2i size = window->drawable.size;

    // draw border
    ctx->set_rect(pos, size, WINDOW_BORDER_WIDTH, COLOR_BORDER_BAR);
    pos.x += WINDOW_BORDER_WIDTH;
    pos.y += WINDOW_BORDER_WIDTH;
    size.x -= WINDOW_BORDER_WIDTH*2;
    size.y -= WINDOW_BORDER_WIDTH*2;

    // draw title bar
    ctx->set_area(pos, OPENWM_POINT2I(size.x, WINDOW_TITLEBAR_HEIGHT), COLOR_TITLE_BAR);
    pos.y += WINDOW_TITLEBAR_HEIGHT;
    size.y -= WINDOW_TITLEBAR_HEIGHT;

    // draw text
    // ssfn_print(window->title);

    // draw border around (just below) the title bar
    ctx->set_area(pos, OPENWM_POINT2I(size.x, WINDOW_BORDER_WIDTH), COLOR_BORDER_BAR);
    pos.y += WINDOW_BORDER_WIDTH;
    size.y -= WINDOW_BORDER_WIDTH;

    // draw window background
    ctx->set_area(pos, size, COLOR_CONTENTS);

    // draw contents
    for (openwm_drawable* drawable = window->drawable.children_start; drawable != NULL; drawable = drawable->next)
        if (drawable->enabled && drawable->draw != NULL)
            drawable->draw(ctx, drawable);
}

openwm_window* openwm_create_window(struct openwm_context* ctx, const char* title, openwm_point2i pos, openwm_point2i size)
{
    if (ctx == NULL || title == NULL)
        return NULL;

    openwm_window* window = ctx->allocate(sizeof(openwm_window));
    if (window == NULL)
        return NULL;

    window->drawable = (openwm_drawable){
        .pos = pos,
        .size = size,
        .draw = openwm_window_draw,
        .enabled = 1,
        .custom_data = NULL,
        .children_start = NULL,
        .children_end = NULL,
        .prev = NULL,
        .next = NULL,
    };
    window->title = (char*)title;

    openwm_context_add_drawable(ctx, (openwm_drawable*)window);

    return window;
}

void openwm_window_add_child(openwm_window* window, openwm_drawable* child)
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

void openwm_dispose_window(struct openwm_context* ctx, openwm_window* window)
{
    if (window == NULL)
        return;

    openwm_context_remove_drawable(ctx, (openwm_drawable*)window);

    if (window->drawable.children_start != NULL)
    {
        for (openwm_drawable* child = window->drawable.children_start; child != NULL; child = child->next)
            openwm_dispose_drawable(ctx, child);
    }

    if (window->drawable.custom_data != NULL)
        ctx->deallocate(window->drawable.custom_data);

    ctx->deallocate(window);
}
