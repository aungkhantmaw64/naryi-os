#ifndef __MSG_BUS_H__
#define __MSG_BUS_H__

#include <zephyr/zbus/zbus.h>

/**
 * @enum msg_bus_button_direction_t
 * @brief Enumeration for button directions in the message bus.
 */
typedef enum
{
    //! Unknown button direction.
    MSG_BUS_BUTTON_DIR_UNKNOWN = 0,
    //! Button pressed in the left direction. */
    MSG_BUS_BUTTON_DIR_LEFT,
    //! Button pressed in the right direction.
    MSG_BUS_BUTTON_DIR_RIGHT,
    //! Button pressed to enter/select.
    MSG_BUS_BUTTON_DIR_ENTER,
    //! Button pressed to go back.
    MSG_BUS_BUTTON_DIR_BACK,
} msg_bus_button_direction_t;

/**
 * @struct msg_bus_buttons_msg_t
 * @brief Structure representing a button message in the message bus.
 */
typedef struct msg_bus_buttons_msg
{
    msg_bus_button_direction_t direction; /**< Direction of the button press. */
} msg_bus_buttons_msg_t;

#endif
