#ifndef __FROSTEDWM__TYPES_H_
#define __FROSTEDWM__TYPES_H_ 1

#include <stdint.h>

#define FROSTEDWM_COLOR_RGBA(red,green,blue,alpha) (frostedwm_color){.r=red,.g=green,.b=blue,.a=alpha}
#define FROSTEDWM_POINT3I(xv,yv,zv) (frostedwm_point3i){.x=xv,.y=yv,.z=zv}
#define FROSTEDWM_POINT2I(xv,yv) (frostedwm_point2i){.x=xv,.y=yv}

typedef struct
{
    int8_t r, g, b, a;
} frostedwm_color;

typedef struct
{
    int32_t x, y, z;
} frostedwm_point3i;

typedef struct
{
    int32_t x, y;
} frostedwm_point2i;

typedef struct
{
    frostedwm_point2i size;
    void* address;
} frostedwm_framebuffer;

#endif