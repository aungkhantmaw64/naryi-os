#include "settings_app.h"

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

/**
 * @brief Implementation of the app_api_t's enter function for the watchface
 * screen.
 */
static int settings_app_enter(void);

/**
 * @brief Implementation of the app_api_t's exit function for the
 * watchface screen.
 */
static int settings_app_exit(void);

/**
 * @brief Implementation of the app_api_t's is_active function for the
 * watchface screen.
 */
static bool settings_app_is_active(void);

/**
 * @brief Handles button press events for the settings application.
 *
 * This function processes button press messages received from the message bus
 * and performs the appropriate actions within the settings application.
 *
 * @param p_msg A pointer to the button message received from the message bus.
 * @return An integer indicating success (0) or failure (non-zero).
 */
static int settings_app_on_button(const msg_bus_buttons_msg_t* p_msg);

/**
 * @brief Displays the menu icon for the settings application.
 *
 * This function ensures that the menu icon for the settings application
 * is visible on the user interface.
 *
 * @return An integer indicating success (0) or failure (non-zero).
 */
static int settings_app_show_menu_icon(void);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! App API instance
static app_api_t g_app_api = {0};

//! Flag to indicate if the app is active
static bool g_is_active = false;

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/

app_api_t* settings_app_create()
{
    g_app_api.enter          = settings_app_enter;
    g_app_api.exit           = settings_app_exit;
    g_app_api.is_active      = settings_app_is_active;
    g_app_api.on_button      = settings_app_on_button;
    g_app_api.show_menu_icon = settings_app_show_menu_icon;
    return &g_app_api;
}

int settings_app_destroy(app_api_t* api)
{
    return 0;
}

/********************************************************************************************************************
 *
 *                                         Private Function Definitions
 *
 ********************************************************************************************************************/

static int settings_app_enter(void)
{
    return 0;
}

static int settings_app_exit(void)
{
    return 0;
}

static bool settings_app_is_active(void)
{
    return g_is_active;
}

static int settings_app_on_button(const msg_bus_buttons_msg_t* p_msg)
{
    return 0;
}

static int settings_app_show_menu_icon(void)
{
    return 0;
}
