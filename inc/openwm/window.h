#ifndef __OPENWM__WINDOW_H_
#define __OPENWM__WINDOW_H_ 1

#include "drawable.h"
#include "types.h"

#define COLOR_BORDER_BAR OPENWM_COLOR_RGBA(0x88,0x22,0x88,0xFF)
#define COLOR_TITLE_BAR OPENWM_COLOR_RGBA(0x22,0x22,0x22,0xFF)
#define COLOR_CONTENTS OPENWM_COLOR_RGBA(0x11,0x11,0x11,0xFF)
#define COLOR_TEXT OPENWM_COLOR_RGBA(0xDD,0xDD,0xDD,0xFF)
#define WINDOW_BORDER_WIDTH 2
#define WINDOW_TITLEBAR_HEIGHT 34

typedef struct openwm_window
{
    openwm_drawable drawable;
    char* title;
} openwm_window;

struct openwm_context;

openwm_window* openwm_create_window(struct openwm_context* ctx, const char* title, openwm_point2i pos, openwm_point2i size);
void openwm_window_add_child(openwm_window* window, openwm_drawable* child);
void openwm_dispose_window(struct openwm_context* ctx, openwm_window* window);

#endif