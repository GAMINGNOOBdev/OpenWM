/**
 * @file fonts.c
 * @author Pradosh (pradoshgame@gmail.com)
 * @brief A wrapper function for loading ssfn fonts.
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <frostedwm/fonts/fonts.h>
#define SSFN_IMPLEMENTATION

ssfn_t ssfn_ctx = { 0 };
ssfn_buf_t ssfn_buf;

void init_ssfn(uint64_t* ptr, int w, int h, uint64_t pitch, int fonts_loaded, ...){
    ssfn_buf = (ssfn_buf_t) {
        .ptr = (uint8_t*)ptr,
        .w = w,
        .h = h,
        .p = pitch,
        .x = 0,
        .y = 0,
        .fg = 0xFFffffff
    };
    
    _ssfn_select(SSFN_FAMILY_SERIF, NULL, SSFN_STYLE_REGULAR, 26);

    va_list args;
    va_start(args, fonts_loaded);

    for (int i = 0; i < fonts_loaded; i++) {
        uint64_t* num = va_arg(args, uint64_t*);
        ssfn_load(&ssfn_ctx, num);
    }

    va_end(args);
}

void ssfn_set_fg_color(uint32_t* fg){
    ssfn_buf.fg = fg;
}

void ssfn_print(const char* msg){
    ssfn_render(&ssfn_ctx, &ssfn_buf, msg);
}

void _ssfn_select(int family, char* name, int style, int size){
    ssfn_select(&ssfn_ctx, family, name, style, size);
    
}

void _ssfn_free(){
    ssfn_free(&ssfn_ctx);
}