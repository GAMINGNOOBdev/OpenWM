#include "openwm/event/events.h"
#include "openwm/input/mouse.h"
#include <openwm/fonts/font.h>
#include <openwm/drawable.h>
#include <openwm/style.h>
#include <openwm/types.h>
#include <openwm/context.h>
#include <openwm/window.h>

void openwm_window_draw(openwm_drawable_t* drawable)
{
    openwm_window_t* window = (openwm_window_t*)drawable;

    if (window == NULL)
        return;

    openwm_context_t* ctx = window->drawable.ctx;
    openwm_point2i_t pos = window->drawable.pos;
    openwm_point2i_t size = window->drawable.size;
    openwm_style_t style = ctx->style;

    // draw border
    ctx->set_rect(pos, size, style.border_width, style.border);
    pos.x += style.border_width;
    pos.y += style.border_width;
    size.x -= style.border_width*2;
    size.y -= style.border_width*2;

    // draw title bar
    ctx->set_area(pos, OPENWM_POINT2I(size.x, style.title_bar_height), style.title_bar);
    pos.y += style.title_bar_height/2 + (style.title_bar_height%2); // simple fix to accomodate for uneven tile bar heights
    size.y -= style.title_bar_height;

    // draw text
    openwm_font_t* font = openwm_context_get_font(ctx, NULL);
    if (font != NULL)
    {
        font->cursor.x = pos.x;
        font->cursor.y = pos.y;
        font->color = style.title_text;
        openwm_font_set_line_height(ctx, font, style.text_height);
        openwm_font_draw_text(ctx, font, window->title, 0);
    }
    pos.y += style.title_bar_height/2;

    // draw border around (just below) the title bar
    ctx->set_area(pos, OPENWM_POINT2I(size.x, style.border_width), style.border);
    pos.y += style.border_width;
    size.y -= style.border_width;

    // draw window background
    ctx->set_area(pos, size, style.contents);

    // draw contents
    for (openwm_drawable_t* drawable = window->drawable.children_start; drawable != NULL; drawable = drawable->next)
        if (drawable->enabled && drawable->draw != NULL)
            drawable->draw(drawable);
}

void openwm_window_on_mouse_button(openwm_drawable_t* drawable, openwm_event_t event)
{
    openwm_window_t* window = (openwm_window_t*)drawable;

    if (window == NULL)
        return;

    openwm_point2i_t pos = window->drawable.pos;
    openwm_point2i_t size = window->drawable.size;
    openwm_style_t style = window->drawable.ctx->style;

    if (event.type == OPENWM_EVENT_TYPE_BUTTON && event.mouse_button_state == OPENWM_MOUSE_BUTTON_STATE_PRESS && event.mouse_button == OPENWM_MOUSE_BUTTON_LEFT)
    {
        // check if the click is within the title bar area
        if (event.mouse_position.x >= pos.x + style.border_width &&
            event.mouse_position.x <= pos.x + size.x - style.border_width &&
            event.mouse_position.y >= pos.y + style.border_width &&
            event.mouse_position.y <= pos.y + style.border_width + style.title_bar_height)
        {
            window->dragging = 1;
        }
    }
    else if (event.type == OPENWM_EVENT_TYPE_BUTTON && event.mouse_button_state == OPENWM_MOUSE_BUTTON_STATE_RELEASE && event.mouse_button == OPENWM_MOUSE_BUTTON_LEFT)
    {
        window->dragging = 0;
    }
}

void openwm_window_on_mouse_move(openwm_drawable_t* drawable, openwm_event_t event)
{
    openwm_window_t* window = (openwm_window_t*)drawable;

    if (window == NULL)
        return;

    if (window->dragging)
    {
        // Move the window based on the drag offset
        window->drawable.pos.x += event.relative_movement.x;
        window->drawable.pos.y += event.relative_movement.y;
    }
    else
    {
        // Handle regular movement if not dragging
        /*window->drawable.pos.x += event.relative_movement.x;
        window->drawable.pos.y += event.relative_movement.y;*/
    }
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
        .on_mouse_button = openwm_window_on_mouse_button,
        .on_mouse_move = openwm_window_on_mouse_move,
        .on_key_press = NULL,
        .ctx = ctx,
        .prev = NULL,
        .next = NULL,
    };
    window->title = (char*)title;
    window->dragging = 0;

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
