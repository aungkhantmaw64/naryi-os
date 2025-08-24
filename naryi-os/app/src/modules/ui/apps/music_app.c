#include "music_app.h"

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

/**
 * @brief Implementation of the app_api_t's enter function for the watchface
 * screen.
 */
static int music_app_enter(void);

/**
 * @brief Implementation of the app_api_t's exit function for the
 * watchface screen.
 */
static int music_app_exit(void);

/**
 * @brief Implementation of the app_api_t's is_active function for the
 * watchface screen.
 */
static bool music_app_is_active(void);

static int music_app_on_button(const msg_bus_buttons_msg_t* p_msg);

static int music_app_show_menu_icon(void);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! Watchface screen API instance
static app_api_t g_app_api = {0};

static bool g_is_active = false;

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/
app_api_t* music_app_create()
{
    g_app_api.enter          = music_app_enter;
    g_app_api.exit           = music_app_exit;
    g_app_api.is_active      = music_app_is_active;
    g_app_api.on_button      = music_app_on_button;
    g_app_api.show_menu_icon = music_app_show_menu_icon;
    return &g_app_api;
}

int music_app_destroy(app_api_t* api) {}

static int music_app_enter(void) {}

static int music_app_exit(void) {}

static bool music_app_is_active(void)
{
    return g_is_active;
}

static int music_app_on_button(const msg_bus_buttons_msg_t* p_msg) {}

static int music_app_show_menu_icon(void) {}
