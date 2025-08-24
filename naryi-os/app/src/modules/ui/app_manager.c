#include "app_manager.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/zbus/zbus.h>

#include "app.h"
#include "msg_bus.h"
#include "music_app.h"
#include "settings_app.h"
#include "watchface_app.h"

#define APP_MANAGER_MAX_APPS (4)

typedef enum
{
    APP_MANAGER_APP_TYPE_MINIMUM   = 0,
    APP_MANAGER_APP_TYPE_WATCHFACE = APP_MANAGER_APP_TYPE_MINIMUM,
    APP_MANAGER_APP_TYPE_SETTINGS,
    APP_MANAGER_APP_TYPE_MUSIC,
    APP_MANAGER_APP_TYPE_MAXIMUM = APP_MANAGER_APP_TYPE_MUSIC,
} app_manager_app_type_t;

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

static void app_manager_listener_callback(const struct zbus_channel* chan);

static int app_manager_init(void);

static int app_manager_navigate_apps(const msg_bus_buttons_msg_t* p_msg);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

static app_api_t* g_apps[APP_MANAGER_MAX_APPS] = {0};

static app_manager_app_type_t g_current_app = APP_MANAGER_APP_TYPE_WATCHFACE;

//! Module registration for logging
LOG_MODULE_REGISTER(screen_manager, CONFIG_LOG_DEFAULT_LEVEL);

ZBUS_CHAN_DECLARE(msg_bus_buttons_chan);

ZBUS_LISTENER_DEFINE(app_manager_listener, app_manager_listener_callback);

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/

int app_manager_start(void)
{
    LOG_INF("screen manager has been started.");

    app_enter(g_apps[g_current_app]);

    return 0;
}

int app_manager_stop(void)
{
    return 0;
}

/********************************************************************************************************************
 *
 *                                         Private Function Definitions
 *
 ********************************************************************************************************************/

static int app_manager_init(void)
{
    g_apps[APP_MANAGER_APP_TYPE_WATCHFACE] = watchface_app_create();

    g_apps[APP_MANAGER_APP_TYPE_SETTINGS] = settings_app_create();

    g_apps[APP_MANAGER_APP_TYPE_MUSIC] = music_app_create();
    return 0;
}

static void app_manager_listener_callback(const struct zbus_channel* chan)
{
    if (&msg_bus_buttons_chan == chan)
    {
        const msg_bus_buttons_msg_t* p_buttons_msg = zbus_chan_const_msg(chan);

        LOG_DBG("Button pressed: %d.", p_buttons_msg->direction);

        if (app_is_active(g_apps[g_current_app]))
        {
            // APP MODE
            app_on_button(g_apps[g_current_app], p_buttons_msg);
        }
        else
        {
            // MENU MODE
            // Navigate between APPS
            app_manager_navigate_apps(p_buttons_msg);
        }
    }
}

static int app_manager_navigate_apps(const msg_bus_buttons_msg_t* p_msg)
{
    switch (p_msg->direction)
    {
        case MSG_BUS_BUTTON_DIR_ENTER:
            LOG_INF("Pressed ENTER!");
            app_enter(g_apps[g_current_app]);
            break;
        case MSG_BUS_BUTTON_DIR_LEFT:
            LOG_INF("Pressed LEFT!");
            if (g_current_app > APP_MANAGER_APP_TYPE_MINIMUM)
            {
                g_current_app--;
            }
            break;
        case MSG_BUS_BUTTON_DIR_RIGHT:
            LOG_INF("Pressed RIGHT!");
            if (g_current_app < APP_MANAGER_APP_TYPE_MAXIMUM)
            {
                g_current_app++;
            }
            break;
        case MSG_BUS_BUTTON_DIR_BACK:
            LOG_INF("Pressed EXIT!");
            break;
        case MSG_BUS_BUTTON_DIR_UNKNOWN:
            break;
        default:
            break;
    }
    LOG_INF("Current app: %d", g_current_app);
    return 0;
}

SYS_INIT_NAMED(app_manager_init, app_manager_init, APPLICATION,
               CONFIG_APPLICATION_INIT_PRIORITY);
