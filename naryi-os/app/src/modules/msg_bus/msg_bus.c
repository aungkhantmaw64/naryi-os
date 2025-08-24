#include "msg_bus.h"

/**
 * @brief Message bus channel definition for button events.
 *
 * This channel is used to handle button press events in the system. It defines
 * the message type, observers, and the initial state of the channel.
 *
 * - Name: msg_bus_buttons_chan
 * - Message Type: msg_bus_buttons_msg_t
 * - Observers: app_manager_listener
 * - Initial Value: direction set to MSG_BUS_BUTTON_DIR_UNKNOWN
 */
ZBUS_CHAN_DEFINE(
    msg_bus_buttons_chan,                                  /* Name */
    msg_bus_buttons_msg_t,                                 /* Message type */
    NULL,                                                  /* Validator */
    NULL,                                                  /* User Data */
    ZBUS_OBSERVERS(app_manager_listener),                  /* observers */
    ZBUS_MSG_INIT(.direction = MSG_BUS_BUTTON_DIR_UNKNOWN) /* Initial value */
);
