#ifndef __FROSTEDWM__WINDOW_H_
#define __FROSTEDWM__WINDOW_H_ 1

#include "drawable.h"
#include "types.h"

#define COLOR_BORDER_BAR FROSTEDWM_COLOR_RGBA(0x88,0x22,0x88,0xFF)
#define COLOR_TITLE_BAR FROSTEDWM_COLOR_RGBA(0x22,0x22,0x22,0xFF)
#define COLOR_CONTENTS FROSTEDWM_COLOR_RGBA(0x11,0x11,0x11,0xFF)
#define COLOR_TEXT FROSTEDWM_COLOR_RGBA(0xDD,0xDD,0xDD,0xFF)
#define WINDOW_BORDER_WIDTH 2
#define WINDOW_TITLEBAR_HEIGHT 34

typedef struct frostedwm_window
{
    frostedwm_drawable drawable;
    char* title;
} frostedwm_window;

struct frostedwm_context;

frostedwm_window* frostedwm_create_window(struct frostedwm_context* ctx, const char* title, frostedwm_point2i pos, frostedwm_point2i size);
void frostedwm_window_add_child(frostedwm_window* window, frostedwm_drawable* child);
void frostedwm_dispose_window(struct frostedwm_context* ctx, frostedwm_window* window);

#endif