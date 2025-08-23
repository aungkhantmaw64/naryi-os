#include "msg_bus.h"

ZBUS_CHAN_DEFINE(
    msg_bus_buttons_chan,                                  /* Name */
    msg_bus_buttons_msg_t,                                 /* Message type */
    NULL,                                                  /* Validator */
    NULL,                                                  /* User Data */
    ZBUS_OBSERVERS(screen_manager_listener),               /* observers */
    ZBUS_MSG_INIT(.direction = MSG_BUS_BUTTON_DIR_UNKNOWN) /* Initial value */
);
