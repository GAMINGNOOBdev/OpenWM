#include <frostedwm/drawable.h>
#include <frostedwm/context.h>
#include <string.h>

frostedwm_drawable* frostedwm_create_drawable(struct frostedwm_context* ctx, frostedwm_point2i pos, frostedwm_point2i size, frostedwm_drawable_draw_t draw, void* custom_data)
{
    if (ctx == NULL)
        return NULL;

    frostedwm_drawable* drawable = ctx->allocate(sizeof(frostedwm_drawable));
    if (drawable == NULL)
        return NULL;

    *drawable = (frostedwm_drawable){
        .pos = pos,
        .size = size,
        .draw = draw,
        .enabled = 1,
        .custom_data = custom_data,
        .children_start = NULL,
        .children_end = NULL,
        .prev = NULL,
        .next = NULL,
    };


    return drawable;
}

void frostedwm_drawable_add_child(frostedwm_drawable* drawable, frostedwm_drawable* child)
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

void frostedwm_dispose_drawable(struct frostedwm_context* ctx, frostedwm_drawable* drawable)
{
    if (drawable == NULL)
        return;

    if (drawable->children_start != NULL)
    {
        for (frostedwm_drawable* child = drawable->children_start; child != NULL; child = child->next)
            frostedwm_dispose_drawable(ctx, child);
    }

    if (drawable->custom_data != NULL)
        ctx->deallocate(drawable->custom_data);

    ctx->deallocate(drawable);
}
