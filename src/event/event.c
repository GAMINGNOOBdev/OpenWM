#include "openwm/drawable.h"
#include <openwm/event/events.h>
#include <openwm/context.h>

openwm_event_queue_t* openwm_create_event_queue(openwm_context_t* ctx)
{
    if (ctx == NULL)
        return NULL;

    if (ctx->allocate == NULL || ctx->deallocate == NULL)
        return NULL;

    openwm_event_queue_t* queue = ctx->allocate(sizeof(openwm_event_queue_t));
    if (queue == NULL)
        return NULL;

    void* buffer = ctx->allocate(sizeof(openwm_event_t)*EVENT_QUEUE_BUFFER);
    if (buffer == NULL)
    {
        ctx->deallocate(queue);
        return NULL;
    }

    *queue = (openwm_event_queue_t){
        .events_buffer_size = EVENT_QUEUE_BUFFER,
        .count = 0,
        .events = buffer,
    };

    return queue;
}

void openwm_dispose_event_queue(openwm_context_t* ctx, openwm_event_queue_t* queue)
{
    if (ctx == NULL || queue == NULL)
        return;

    ctx->deallocate(queue->events);
    ctx->deallocate(queue);
}

int openwm_send_event(openwm_event_queue_t* queue, openwm_event_t event)
{
    if (queue == NULL)
        return 0;

    if (queue->count+1 >= queue->events_buffer_size)
        return 0;

    queue->events[queue->count++] = event;

    return 1;
}

void openwm_handle_event(openwm_drawable_t* drawable, openwm_event_t event)
{
    if ((event.type == EVENT_TYPE_GENERAL || event.type == EVENT_TYPE_WINDOW) && drawable->on_event_handle != NULL)
    {
        drawable->on_event_handle(drawable, event);
    }
    else if (event.type == EVENT_TYPE_MOUSE && drawable->on_mouse_move != NULL)
    {
        drawable->on_mouse_move(drawable, event);
    }
    else if (event.type == EVENT_TYPE_SCROLL && drawable->on_mouse_scroll != NULL)
    {
        drawable->on_mouse_scroll(drawable, event);
    }
    else if (event.type == EVENT_TYPE_BUTTON && drawable->on_mouse_button != NULL)
    {
        drawable->on_mouse_button(drawable, event);
    }
    else if (event.type == EVENT_TYPE_KEY && drawable->on_key_press != NULL)
    {
        drawable->on_key_press(drawable, event);
    }
}

openwm_drawable_t* openwm_find_drawable(openwm_context_t* ctx)
{
    openwm_drawable_t* drawable = NULL;
    for (openwm_drawable_t* entry = ctx->drawlist_start; entry != NULL; entry = entry->next)
    {
        // add some sort of focus system
    }
    return drawable;
}

void openwm_handle_events(openwm_context_t* ctx)
{
    if (ctx == NULL)
        return;
    if (ctx->drawlist_start == NULL)
        return;
    if (ctx->event_queue == NULL)
        return;

    for (size_t i = 0; i < ctx->event_queue->count; i++)
    {
        openwm_drawable_t* drawable = openwm_find_drawable(ctx);
        openwm_handle_event(drawable, ctx->event_queue->events[i]);
    }
    ctx->event_queue->count=0;
}