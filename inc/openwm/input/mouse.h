#ifndef __OPENWM__INPUT__MOUSE_H_
#define __OPENWM__INPUT__MOUSE_H_ 1

#include <stdint.h>
#include "../types.h"

typedef uint8_t openwm_mouse_button_state_t;
typedef uint8_t openwm_mouse_button_t;

#define MOUSE_BUTTON_STATE_NONE     (0)
#define MOUSE_BUTTON_STATE_PRESS    (1)
#define MOUSE_BUTTON_STATE_DRAG     (2)
#define MOUSE_BUTTON_STATE_RELEASE  (3)

#define MOUSE_BUTTON_NONE           (0)
#define MOUSE_BUTTON_LEFT           (1)
#define MOUSE_BUTTON_RIGHT          (2)
#define MOUSE_BUTTON_MIDDLE         (3)
#define MOUSE_BUTTON_ONE            MOUSE_BUTTON_LEFT
#define MOUSE_BUTTON_TWO            MOUSE_BUTTON_RIGHT
#define MOUSE_BUTTON_THREE          MOUSE_BUTTON_MIDDLE
#define MOUSE_BUTTON_FOUR           (4)
#define MOUSE_BUTTON_FIVE           (5)
#define MOUSE_BUTTON_SIX            (6)
#define MOUSE_BUTTON_SEVEN          (7)
#define MOUSE_BUTTON_EIGHT          (8)

#define MOUSE_SCROLL_UP             (0)
#define MOUSE_SCROLL_DOWN           (1)
#define MOUSE_SCROLL_LEFT           (2)
#define MOUSE_SCROLL_RIGHT          (3)

/**
 * Get the current mouse position
*/
openwm_point2i_t openwm_mouse_get_position(void);

/**
 * Get the state of a given mouse button
*/
openwm_mouse_button_state_t openwm_mouse_get_button(openwm_mouse_button_t button);

#endif