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

//! Maximum number of apps
#define APP_MANAGER_MAX_APPS (4)

/**
 * @enum app_manager_app_type_t
 * @brief Enumeration defining the types of applications managed by the
 * application manager.
 *
 * This enumeration lists all the application types that can be handled by the
 * application manager.
 */
typedef enum
{
    /**< Minimum value for application types. */
    APP_MANAGER_APP_TYPE_MINIMUM = 0,
    /**< Watchface application type. */
    APP_MANAGER_APP_TYPE_WATCHFACE = APP_MANAGER_APP_TYPE_MINIMUM,
    /**< Settings application type. */
    APP_MANAGER_APP_TYPE_SETTINGS,
    /**< Music application type. */
    APP_MANAGER_APP_TYPE_MUSIC,
    /**< Maximum value for application types. */
    APP_MANAGER_APP_TYPE_MAXIMUM = APP_MANAGER_APP_TYPE_MUSIC,
} app_manager_app_type_t;

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

/**
 * @brief Callback function for handling events from the zbus channel.
 *
 * This function is invoked when a message is received on the specified channel.
 *
 * @param chan Pointer to the zbus channel that triggered the callback.
 */
static void app_manager_listener_callback(const struct zbus_channel* chan);

/**
 * @brief Initializes the application manager.
 *
 * This function sets up the application manager, preparing it to manage
 * application modules and handle navigation between them.
 *
 * @return 0 on success, or a negative error code on failure.
 */
static int app_manager_init(void);

/**
 * @brief Handles navigation between applications based on button messages.
 *
 * This function processes button messages and switches between applications
 * accordingly.
 *
 * @param p_msg Pointer to the button message structure.
 * @return 0 on success, or a negative error code on failure.
 */
static int app_manager_navigate_apps(const msg_bus_buttons_msg_t* p_msg);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! Registered Apps
static app_api_t* g_apps[APP_MANAGER_MAX_APPS] = {0};

//! Variable to track the currently active app
static app_manager_app_type_t g_current_app = APP_MANAGER_APP_TYPE_WATCHFACE;

//! Module registration for logging
LOG_MODULE_REGISTER(screen_manager, CONFIG_LOG_DEFAULT_LEVEL);

/* @brief Declares a zbus channel for button messages.
 *        This channel is used for communication between modules.
 */
ZBUS_CHAN_DECLARE(msg_bus_buttons_chan);

/*
 * @brief Defines a zbus listener for the application manager.
 *        This listener is triggered when messages are received on the
 * associated channel.
 */
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
            app_enter(g_apps[g_current_app]);
            break;
        case MSG_BUS_BUTTON_DIR_LEFT:
            if (g_current_app > APP_MANAGER_APP_TYPE_MINIMUM)
            {
                g_current_app--;
            }
            break;
        case MSG_BUS_BUTTON_DIR_RIGHT:
            if (g_current_app < APP_MANAGER_APP_TYPE_MAXIMUM)
            {
                g_current_app++;
            }
            break;
        case MSG_BUS_BUTTON_DIR_BACK:
            break;
        case MSG_BUS_BUTTON_DIR_UNKNOWN:
            break;
        default:
            break;
    }

    return 0;
}

SYS_INIT_NAMED(app_manager_init, app_manager_init, APPLICATION,
               CONFIG_APPLICATION_INIT_PRIORITY);
