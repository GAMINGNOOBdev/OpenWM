#include <openwm/fonts/font.h>
#include <openwm/context.h>
#include <stddef.h>
#include <malloc.h>

#define STBTT_malloc(x,u)  ((void)(u),malloc(x))
#define STBTT_free(x,u)    ((void)(u),free(x))

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>

openwm_font_t* openwm_create_font(struct openwm_context* ctx, const char* name, int line_height, void* filedata)
{
    if (ctx == NULL || name == NULL || filedata == NULL)
        return NULL;

    openwm_font_t* font = ctx->allocate(sizeof(openwm_font_t));
    if (font == NULL)
        return NULL;

    if (!stbtt_InitFont(&font->info, filedata, 0))
    {
        ctx->deallocate(font);
        return NULL;
    }

    font->name = (char*)name;
    font->line_height = line_height;
    font->ascent = 0;
    font->descent = 0;
    font->line_spacing = 0;
    font->color = OPENWM_COLOR_RGBA(0xFF, 0xFF, 0xFF, 0xFF);
    font->cursor = (openwm_point2i){
        .x = 0,
        .y = 0,
    };
    font->scale = stbtt_ScaleForPixelHeight(&font->info, line_height);
    stbtt_GetFontVMetrics(&font->info, &font->ascent, &font->descent, &font->line_spacing);
    font->glyphcache = ctx->allocate(font->info.numGlyphs * sizeof(uint8_t*));
    font->glyph_positions = ctx->allocate(font->info.numGlyphs * sizeof(openwm_point2i));
    font->glyph_sizes = ctx->allocate(font->info.numGlyphs * sizeof(openwm_point2i));

    if (font->glyphcache == NULL || font->glyph_positions == NULL || font->glyph_sizes == NULL)
    {
        ctx->deallocate(font);
        return NULL;
    }

    for (int i = 0; i < font->info.numGlyphs; i++)
    {
        font->glyphcache[i] = NULL;
        font->glyph_sizes[i] = (openwm_point2i){
            .x=0,
            .y=0,
        };
        font->glyph_positions[i] = (openwm_point2i){
            .x=0,
            .y=0,
        };
    }

    for (int i = 0; i < font->info.numGlyphs; i++)
    {
        int idx = stbtt_FindGlyphIndex(&font->info, i);
        if (idx == 0)
            continue;

        int advance, lsb;
        stbtt_GetGlyphHMetrics(&font->info, idx, &advance, &lsb);

        int x0, y0, x1, y1;
        stbtt_GetGlyphBitmapBox(&font->info, idx, font->scale, font->scale, &x0, &y0, &x1, &y1);

        int width = x1 - x0;
        int height = y1 - y0;

        unsigned char* bitmap = (unsigned char*)ctx->allocate(width * height);
        stbtt_MakeGlyphBitmap(&font->info, bitmap, font->scale, font->scale, 0, width, height, idx);

        font->glyphcache[i] = bitmap;
        font->glyph_sizes[i] = (openwm_point2i){
            .x=width,
            .y=height,
        };

        font->glyph_positions[i] = (openwm_point2i){
            .x=x0,
            .y=y0,
        };
    }

    return font;
}

void openwm_font_set_line_height(openwm_font_t* font, int line_height)
{
    if (font == NULL)
        return;

    font->scale = stbtt_ScaleForPixelHeight(&font->info, line_height);
}

void openwm_font_draw_char(struct openwm_context* ctx, openwm_font_t* font, const char chr, int style)
{
    if (ctx == NULL || font == NULL)
        return;

    size_t idx = chr;

    if (!font->glyphcache[idx]) return; // Glyph not available

    int width = font->glyph_sizes[idx].x;
    int height = font->glyph_sizes[idx].y;
    int x = font->cursor.x + font->glyph_positions[idx].x;
    int y = font->cursor.y + font->glyph_positions[idx].y;
    uint8_t* bitmap = font->glyphcache[idx];

    float x_shear = 0.0f;
    if (style & OPENWM_FONT_STYLE_ITALIC)
        x_shear = -0.3f; ///TODO: actually use this thing

    int bold_offset = 0;
    if (style & OPENWM_FONT_STYLE_BOLD)
        bold_offset = 2;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            uint8_t pixel = bitmap[j * width + i];
            if (pixel > 0)
            {
                ctx->set_pixel(OPENWM_POINT2I(x + i, y + j), font->color);
                if (bold_offset)
                    ctx->set_pixel(OPENWM_POINT2I(x + i + bold_offset, y + j), font->color);
            }
        }
    }

    if(style & OPENWM_FONT_STYLE_UNDERLINE)
    {
        int underlineY = y + (int)(font->scale * -font->descent);
        int underlineHeight = (int)(font->scale * 0.1f);
        for(int i = x; i < x + font->glyph_sizes[idx].x * font->scale; i++)
            for(int j = 0; j < underlineHeight; j++)
                ctx->set_pixel(OPENWM_POINT2I(i, underlineY + j), font->color);
    }
}

void openwm_font_draw_text(struct openwm_context* ctx, openwm_font_t* font, const char* text, int style)
{
    if (ctx == NULL || font == NULL || text == NULL)
        return;

    int x0 = font->cursor.x;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];
        if (c == '\n')
        {
            font->cursor.x = x0;
            font->cursor.y += (font->scale * (font->ascent - font->descent + font->line_height));
            continue;
        }
        else if (c == '\t')
        {
            font->cursor.x += font->scale * 4 * 8;
            continue;
        }

        openwm_font_draw_char(ctx, font, text[i], style);
        int advance;
        stbtt_GetGlyphHMetrics(&font->info, stbtt_FindGlyphIndex(&font->info, text[i]), &advance, 0);
        font->cursor.x += advance * font->scale;
    }
}

void openwm_dispose_font(struct openwm_context* ctx, openwm_font_t* font)
{
    if (ctx == NULL || font == NULL)
        return;

    for(int i = 0; i < font->info.numGlyphs; i++)
        if(font->glyphcache[i] != NULL)
            ctx->deallocate(font->glyphcache[i]);

    ctx->deallocate(font->glyphcache);
    ctx->deallocate(font->glyph_sizes);
    ctx->deallocate(font->glyph_positions);
    ctx->deallocate(font);
}