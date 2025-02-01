#ifndef __OPENWM__STYLE_H_
#define __OPENWM__STYLE_H_ 1

#include "types.h"

typedef struct openwm_style_t
{
    openwm_color_t border;
    openwm_color_t title_bar;
    openwm_color_t title_text;
    openwm_color_t contents;
    openwm_color_t text;
    uint16_t border_width;
    uint16_t title_bar_height;
    uint16_t title_text_height;
    uint16_t text_height;
}  openwm_style_t;

#endif
