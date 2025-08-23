#ifndef __MSG_BUS_H__
#define __MSG_BUS_H__

#include <zephyr/zbus/zbus.h>

typedef enum
{
    MSG_BUS_BUTTON_DIR_UNKNOWN = 0,
    MSG_BUS_BUTTON_DIR_LEFT,
    MSG_BUS_BUTTON_DIR_RIGHT,
    MSG_BUS_BUTTON_DIR_ENTER,
    MSG_BUS_BUTTON_DIR_BACK
} msg_bus_button_direction_t;

typedef struct msg_bus_buttons_msg
{
    msg_bus_button_direction_t direction;
} msg_bus_buttons_msg_t;

#endif
