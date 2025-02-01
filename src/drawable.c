#include <openwm/drawable.h>
#include <openwm/context.h>

openwm_drawable_t* openwm_create_drawable(openwm_context_t* ctx, openwm_point2i_t pos, openwm_point2i_t size, openwm_drawable_draw_t draw, void* custom_data)
{
    if (ctx == NULL)
        return NULL;

    openwm_drawable_t* drawable = ctx->allocate(sizeof(openwm_drawable_t));
    if (drawable == NULL)
        return NULL;

    *drawable = (openwm_drawable_t){
        .pos = pos,
        .size = size,
        .draw = draw,
        .enabled = 1,
        .focussed = 0,
        .hidden = 0,
        .reserved = 0,
        .custom_data = custom_data,
        .draw_index = -1,
        .children_start = NULL,
        .children_end = NULL,
        .on_event_handle = NULL,
        .on_mouse_scroll = NULL,
        .on_mouse_button = NULL,
        .on_mouse_move = NULL,
        .on_key_press = NULL,
        .ctx = ctx,
        .prev = NULL,
        .next = NULL,
    };

    return drawable;
}

uint8_t openwm_drawable_overlapping(openwm_drawable_t* drawable1, openwm_drawable_t* drawable2)
{
    openwm_point2i_t pos1 = drawable1->pos;
    openwm_point2i_t size1 = drawable1->size;
    openwm_point2i_t pos2 = drawable2->pos;
    openwm_point2i_t size2 = drawable2->size;

    if (pos1.x < pos2.x + size2.x &&
        pos1.x + size1.x > pos2.x &&
        pos1.y < pos2.y + size2.y &&
        pos1.y + size1.y > pos2.y)
    {
        return 1;
    }
    return 0;
}

uint8_t openwm_drawable_is_visible(openwm_context_t* ctx, openwm_drawable_t* drawable)
{
    openwm_point2i_t pos = drawable->pos;
    openwm_point2i_t size = drawable->size;

    for (openwm_drawable_t* other = ctx->drawlist_start; other != NULL; other = other->next)
    {
        if (other->draw_index > drawable->draw_index && !other->hidden)
        {
            openwm_point2i_t other_pos = other->pos;
            openwm_point2i_t other_size = other->size;

            if (openwm_drawable_overlapping(other, drawable))
            {
                if (other_pos.x <= pos.x &&
                    other_pos.x + other_size.x >= pos.x + size.x &&
                    other_pos.y <= pos.y &&
                    other_pos.y + other_size.y >= pos.y + size.y)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

void openwm_drawable_add_child(openwm_drawable_t* drawable, openwm_drawable_t* child)
{
    if (drawable == NULL || child == NULL)
        return;

    if (drawable->children_start == NULL)
    {
        drawable->children_start = drawable->children_end = child;
        return;
    }

    drawable->children_end->next = child;
    child->prev = drawable->children_end;
    drawable->children_end = child;
}

void openwm_dispose_drawable(openwm_context_t* ctx, openwm_drawable_t* drawable)
{
    if (drawable == NULL)
        return;

    if (drawable->children_start != NULL)
    {
        for (openwm_drawable_t* child = drawable->children_start; child != NULL; child = child->next)
            openwm_dispose_drawable(ctx, child);
    }

    if (drawable->custom_data != NULL)
        ctx->deallocate(drawable->custom_data);

    ctx->deallocate(drawable);
}
