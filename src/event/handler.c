#include <frostedwm/event/handler.h>
#include <frostedwm/context.h>

handler_list_t* frostedwm_create_handler_list(struct frostedwm_context* ctx)
{
    if (ctx == NULL)
        return NULL;

    if (ctx->allocate == NULL || ctx->deallocate == NULL)
        return NULL;

    handler_list_t* handler_list = ctx->allocate(sizeof(handler_list_t));
    if (handler_list == NULL)
        return NULL;

    void* buffer = ctx->allocate(sizeof(handle_event_t)*HANDLER_BUFFER_SIZE);
    if (buffer == NULL)
    {
        ctx->deallocate(handler_list);
        return NULL;
    }

    *handler_list = (handler_list_t){
        .buffer_size = HANDLER_BUFFER_SIZE,
        .count = 0,
        .data = buffer,
    };

    return handler_list;
}

void frostedwm_handler_list_add(struct frostedwm_context* ctx, handler_list_t* list, handle_event_t handle)
{
    if (ctx == NULL || list == NULL || handle == NULL)
        return;

    if (list->count+1 >= list->buffer_size)
    {
        list->buffer_size += HANDLER_BUFFER_SIZE;
        list->data = ctx->reallocate(list->data, sizeof(handle_event_t)*list->buffer_size);
    }

    list->data[list->count++] = handle;
}

void frostedwm_disose_handler_list(struct frostedwm_context* ctx, handler_list_t* list)
{
    if (ctx == NULL || list == NULL)
        return;

    ctx->deallocate(list->data);
    ctx->deallocate(list);
}