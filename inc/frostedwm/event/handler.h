#ifndef __FROSTEDWM__EVENTS__HANDLER_H_
#define __FROSTEDWM__EVENTS__HANDLER_H_ 1

#include "events.h"
#include <stddef.h>

typedef void(*handle_event_t)(event_t event);

#define HANDLER_BUFFER_SIZE 0x100

typedef struct handler_list_t
{
    handle_event_t* data;
    size_t buffer_size;
    size_t count;
} handler_list_t;

struct frostedwm_context;
handler_list_t* frostedwm_create_handler_list(struct frostedwm_context* ctx);
void frostedwm_handler_list_add(struct frostedwm_context* ctx, handler_list_t* list, handle_event_t handle);
void frostedwm_disose_handler_list(struct frostedwm_context* ctx, handler_list_t* list);

#endif