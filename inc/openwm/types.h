#ifndef __OPENWM__TYPES_H_
#define __OPENWM__TYPES_H_ 1

#include <stdint.h>

#define OPENWM_COLOR_RGBA(red,green,blue,alpha) (openwm_color_t){.r=red,.g=green,.b=blue,.a=alpha}
#define OPENWM_COLOR_RGB(red,green,blue) (openwm_color_t){.r=red,.g=green,.b=blue,.a=0xFF}
#define OPENWM_POINT3I(xv,yv,zv) (openwm_point3i_t){.x=xv,.y=yv,.z=zv}
#define OPENWM_POINT2I(xv,yv) (openwm_point2i_t){.x=xv,.y=yv}

/*
 * Color definitions
 */
#define OPENWM_COLOR_WHITE OPENWM_COLOR_RGBA(0xff,0xff,0xff,0xff)
#define OPENWM_COLOR_BLACK OPENWM_COLOR_RGBA(0,0,0,0xff)
#define OPENWM_COLOR_RED OPENWM_COLOR_RGBA(0xff,0,0,0xff)
#define OPENWM_COLOR_GREEN OPENWM_COLOR_RGBA(0,0xff,0,0xff)
#define OPENWM_COLOR_BLUE OPENWM_COLOR_RGBA(0,0,0xff,0xff)
#define OPENWM_COLOR_PURPLE OPENWM_COLOR_RGBA(0x80,0,0x80,0xff)
#define OPENWM_COLOR_GREY OPENWM_COLOR_RGBA(0x20,0x20,0x20,0xff)

typedef struct
{
    int8_t r, g, b, a;
} openwm_color_t;

typedef struct
{
    int32_t x, y, z;
} openwm_point3i_t;

typedef struct
{
    int32_t x, y;
} openwm_point2i_t;

#endif
