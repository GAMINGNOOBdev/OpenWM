#include <openwm/fonts/font.h>
#include <openwm/drawable.h>
#include "openwm/types.h"
#include <openwm/context.h>
#include <openwm/window.h>

void openwm_window_draw(openwm_context_t* ctx, openwm_drawable_t* drawable)
{
    openwm_window_t* window = (openwm_window_t*)drawable;

    if (window == NULL)
        return;

    openwm_point2i_t pos = window->drawable.pos;
    openwm_point2i_t size = window->drawable.size;

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
    openwm_font_t* font = openwm_context_get_font(ctx, NULL);
    if (font != NULL)
    {
        font->cursor.x = pos.x;
        font->cursor.y = pos.y;
        font->color = COLOR_TEXT;
        openwm_font_set_line_height(ctx, font, WINDOW_TITLEBAR_HEIGHT-2);
        openwm_font_draw_text(ctx, font, window->title, 0);
    }

    // draw border around (just below) the title bar
    ctx->set_area(pos, OPENWM_POINT2I(size.x, WINDOW_BORDER_WIDTH), COLOR_BORDER_BAR);
    pos.y += WINDOW_BORDER_WIDTH;
    size.y -= WINDOW_BORDER_WIDTH;

    // draw window background
    ctx->set_area(pos, size, COLOR_CONTENTS);

    // draw contents
    for (openwm_drawable_t* drawable = window->drawable.children_start; drawable != NULL; drawable = drawable->next)
        if (drawable->enabled && drawable->draw != NULL)
            drawable->draw(ctx, drawable);
}

void openwm_window_move(openwm_drawable_t* drawable, openwm_event_t event)
{
    openwm_window_t* window = (openwm_window_t*)drawable;

    if (window == NULL)
        return;

    window->drawable.pos.x += event.relative_movement.x;
    window->drawable.pos.y += event.relative_movement.y;
}

openwm_window_t* openwm_create_window(openwm_context_t* ctx, const char* title, openwm_point2i_t pos, openwm_point2i_t size)
{
    if (ctx == NULL || title == NULL)
        return NULL;

    openwm_window_t* window = ctx->allocate(sizeof(openwm_window_t));
    if (window == NULL)
        return NULL;

    window->drawable = (openwm_drawable_t){
        .pos = pos,
        .size = size,
        .draw = openwm_window_draw,
        .enabled = 1,
        .custom_data = NULL,
        .children_start = NULL,
        .children_end = NULL,
        .on_event_handle = NULL,
        .on_mouse_scroll = NULL,
        .on_mouse_button = NULL,
        .on_mouse_move = openwm_window_move,
        .on_key_press = NULL,
        .prev = NULL,
        .next = NULL,
    };
    window->title = (char*)title;

    openwm_context_add_drawable(ctx, (openwm_drawable_t*)window);

    return window;
}

void openwm_window_add_child(openwm_window_t* window, openwm_drawable_t* child)
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

void openwm_dispose_window(openwm_context_t* ctx, openwm_window_t* window)
{
    if (window == NULL)
        return;

    openwm_context_remove_drawable(ctx, (openwm_drawable_t*)window);

    if (window->drawable.children_start != NULL)
    {
        for (openwm_drawable_t* child = window->drawable.children_start; child != NULL; child = child->next)
            openwm_dispose_drawable(ctx, child);
    }

    if (window->drawable.custom_data != NULL)
        ctx->deallocate(window->drawable.custom_data);

    ctx->deallocate(window);
}
