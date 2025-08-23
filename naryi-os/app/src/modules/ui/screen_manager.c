#include "screen_manager.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/zbus/zbus.h>

#include "msg_bus.h"
#include "screen_api.h"

//! Screen count limit
#define SCREEN_MANAGER_MAX_SCREEN_COUNT (3)
//! Index of the screens that will be displayed at the start up
#define SCREEN_MANAGER_STARTING_SCREEN_INDEX (0)

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

static void screen_manager_listener_callback(const struct zbus_channel* chan);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! Number of added screens
static uint8_t g_screen_count = 0;

//! Added screens
static screen_api_t* g_screens[SCREEN_MANAGER_MAX_SCREEN_COUNT] = {0};

//! Module registration for logging
LOG_MODULE_REGISTER(screen_manager, CONFIG_LOG_DEFAULT_LEVEL);

ZBUS_CHAN_DECLARE(msg_bus_buttons_chan);
ZBUS_LISTENER_DEFINE(screen_manager_listener, screen_manager_listener_callback);

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/

int screen_manager_push_screen(screen_api_t* api)
{
    __ASSERT(api != NULL, "Invalid screen API!");

    g_screens[g_screen_count++] = api;

    return 0;
}

int screen_manager_start(void)
{
    screen_enter(g_screens[SCREEN_MANAGER_STARTING_SCREEN_INDEX]);

    LOG_INF("screen manager has been started.");

    return 0;
}

int screen_manager_deinit(void)
{
    return 0;
}

/********************************************************************************************************************
 *
 *                                         Private Function Definitions
 *
 ********************************************************************************************************************/

static void screen_manager_listener_callback(const struct zbus_channel* chan)
{
    const msg_bus_buttons_msg_t* buttons_msg;

    if (&msg_bus_buttons_chan == chan)
    {
        buttons_msg = zbus_chan_const_msg(chan); // Direct message access
        LOG_INF("Button pressed: %d.", buttons_msg->direction);
    }
}
