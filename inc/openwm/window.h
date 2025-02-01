#ifndef __OPENWM__WINDOW_H_
#define __OPENWM__WINDOW_H_ 1

#include "drawable.h"
#include "types.h"

typedef struct openwm_window_t
{
    openwm_drawable_t drawable;
    char* title;
    uint8_t dragging;
} openwm_window_t;

struct openwm_context_t;

openwm_window_t* openwm_create_window(struct openwm_context_t* ctx, const char* title, openwm_point2i_t pos, openwm_point2i_t size);
void openwm_window_add_child(openwm_window_t* window, openwm_drawable_t* child);
void openwm_dispose_window(struct openwm_context_t* ctx, openwm_window_t* window);

#endif
