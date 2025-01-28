#ifndef __OPENWM__TYPES_H_
#define __OPENWM__TYPES_H_ 1

#include <stdint.h>

#define OPENWM_COLOR_RGBA(red,green,blue,alpha) (openwm_color){.r=red,.g=green,.b=blue,.a=alpha}
#define OPENWM_POINT3I(xv,yv,zv) (openwm_point3i){.x=xv,.y=yv,.z=zv}
#define OPENWM_POINT2I(xv,yv) (openwm_point2i){.x=xv,.y=yv}

typedef struct
{
    int8_t r, g, b, a;
} openwm_color;

typedef struct
{
    int32_t x, y, z;
} openwm_point3i;

typedef struct
{
    int32_t x, y;
} openwm_point2i;

typedef struct
{
    openwm_point2i size;
    void* address;
} openwm_framebuffer;

#endif