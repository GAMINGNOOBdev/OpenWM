/**
 * @file fonts.h
 * @author Pradosh (pradoshgame@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __FROSTEDWM__FONTS_H_
#define __FROSTEDWM__FONTS_H_ 1

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

void init_ssfn(uint64_t* ptr, int w, int h, uint64_t pitch, int fonts_loaded, ...);
void ssfn_set_fg_color(uint32_t* fg);
void ssfn_print(const char* msg);
void _ssfn_select(int family, char* name, int style, int size);
void _ssfn_free();

#endif