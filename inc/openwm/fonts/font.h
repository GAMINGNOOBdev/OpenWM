#ifndef __OPENWM__FONTS__FONT_H_
#define __OPENWM__FONTS__FONT_H_ 1

#include <stddef.h>
#include "../types.h"
#include <stb/stb_truetype.h>

#define OPENWM_FONT_STYLE_NORMAL    0b000
#define OPENWM_FONT_STYLE_BOLD      0b001
#define OPENWM_FONT_STYLE_ITALIC    0b010
#define OPENWM_FONT_STYLE_UNDERLINE 0b100

typedef struct openwm_font_t
{
    stbtt_fontinfo info;
    float scale;
    int ascent;
    int descent;
    int line_spacing;
    int line_height;
    openwm_color_t color;
    openwm_point2i_t cursor;

    char* name;
    uint8_t** glyphcache;
    openwm_point2i_t* glyph_sizes;
    openwm_point2i_t* glyph_positions;

    struct openwm_font_t* prev;
    struct openwm_font_t* next;
} openwm_font_t;

struct openwm_context_t;

openwm_font_t* openwm_create_font(struct openwm_context_t* ctx, const char* name, int line_height, void* filedata);
void openwm_font_set_line_height(struct openwm_context_t* ctx, openwm_font_t* font, int line_height);
void openwm_font_draw_text(struct openwm_context_t* ctx, openwm_font_t* font, const char* text, int style);
void openwm_dispose_font(struct openwm_context_t* ctx, openwm_font_t* font);

#endif