#ifndef __OPENWM__INPUT__MOUSE_H_
#define __OPENWM__INPUT__MOUSE_H_ 1

#include <stdint.h>
#include "../types.h"

typedef uint8_t openwm_mouse_button_state_t;
typedef uint8_t openwm_mouse_cursor_state_t;
typedef uint8_t openwm_mouse_button_t;

#define OPENWM_MOUSE_CURSOR_DISABLED       (openwm_mouse_cursor_state_t)0
#define OPENWM_MOUSE_CURSOR_HIDDEN         (openwm_mouse_cursor_state_t)1
#define OPENWM_MOUSE_CURSOR_VISIBLE        (openwm_mouse_cursor_state_t)2

#define OPENWM_MOUSE_BUTTON_STATE_NONE     (openwm_mouse_button_state_t)0
#define OPENWM_MOUSE_BUTTON_STATE_PRESS    (openwm_mouse_button_state_t)1
#define OPENWM_MOUSE_BUTTON_STATE_RELEASE  (openwm_mouse_button_state_t)2

#define OPENWM_MOUSE_BUTTON_NONE           (openwm_mouse_button_t)-1
#define OPENWM_MOUSE_BUTTON_LEFT           (openwm_mouse_button_t)0
#define OPENWM_MOUSE_BUTTON_RIGHT          (openwm_mouse_button_t)1
#define OPENWM_MOUSE_BUTTON_MIDDLE         (openwm_mouse_button_t)2
#define OPENWM_MOUSE_BUTTON_ONE            MOUSE_BUTTON_LEFT
#define OPENWM_MOUSE_BUTTON_TWO            MOUSE_BUTTON_RIGHT
#define OPENWM_MOUSE_BUTTON_THREE          MOUSE_BUTTON_MIDDLE
#define OPENWM_MOUSE_BUTTON_FOUR           (openwm_mouse_button_t)3
#define OPENWM_MOUSE_BUTTON_FIVE           (openwm_mouse_button_t)4
#define OPENWM_MOUSE_BUTTON_SIX            (openwm_mouse_button_t)5
#define OPENWM_MOUSE_BUTTON_SEVEN          (openwm_mouse_button_t)6
#define OPENWM_MOUSE_BUTTON_EIGHT          (openwm_mouse_button_t)7
#define OPENWM_MOUSE_BUTTON_LAST           OPENWM_MOUSE_BUTTON_EIGHT

#define OPENWM_MOUSE_SCROLL_UP             (0)
#define OPENWM_MOUSE_SCROLL_DOWN           (1)
#define OPENWM_MOUSE_SCROLL_LEFT           (2)
#define OPENWM_MOUSE_SCROLL_RIGHT          (3)

/**
 * Get the current mouse position
*/
openwm_point2i_t openwm_mouse_get_position(void);

/**
 * Set the current mouse cursor
*/
void openwm_mouse_set_cursor(openwm_mouse_cursor_state_t cursor);

/**
 * Get the state of a given mouse button
*/
openwm_mouse_button_state_t openwm_mouse_get_button(openwm_mouse_button_t button);

#endif