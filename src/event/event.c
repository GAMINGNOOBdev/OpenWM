#include <frostedwm/event/handler.h>
#include <frostedwm/event/events.h>
#include <frostedwm/context.h>

void frostedwm_send_event(struct frostedwm_context* ctx, event_t event)
{
    if (ctx == NULL)
        return;
    if (ctx->handlers == NULL)
        return;
    if (ctx->handlers->data == NULL)
        return;

    for (int i = 0; i < ctx->handlers->count; i++)
        ctx->handlers->data[i](event);
}