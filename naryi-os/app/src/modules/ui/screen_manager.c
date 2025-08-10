#include "screen_manager.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

#include "screen_api.h"

//! Size of the stack memory allocated for screen_manager thread
#define SCREEN_MANAGER_STACK_SIZE (12000)
//! Priority for screen_manager task
#define SCREEN_MANAGER_PRIORITY (5)
//! Screen count limit
#define SCREEN_MANAGER_MAX_SCREEN_COUNT (3)
//! Index of the screens that will be displayed at the start up
#define SCREEN_MANAGER_STARTING_SCREEN_INDEX (0)

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

/**
 * @brief Screen manager thread's entry point.
 */
static void screen_manager_thread_entry_point(void*, void*, void*);

//! Module registration for logging
LOG_MODULE_REGISTER(screen_manager);

//! Stack allocation for screen manager thread
K_THREAD_STACK_DEFINE(screen_manager_stack, SCREEN_MANAGER_STACK_SIZE);

//! Screen manager thread id
static k_tid_t g_thread_id = {0};

//! Screen manager thread context
static struct k_thread g_thread_data = {0};

//! Number of added screens
static uint8_t g_screen_count = 0;

//! Added screens
static screen_api_t* g_screens[SCREEN_MANAGER_MAX_SCREEN_COUNT] = {0};

static const struct device* g_display_dev = {0};

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/

int screen_manager_init(void)
{
    return 0;
}

int screen_manager_push_screen(screen_api_t* api)
{
    LOG_INF("pushing a screen.");
    g_screens[g_screen_count++] = api;
    LOG_INF("pushed a screen.");
    return 0;
}

int screen_manager_start(void)
{
    LOG_INF("starting screen manager.");
    g_display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

    if (!device_is_ready(g_display_dev))
    {
        LOG_ERR("device not ready, aborting screen_manager.");
        return -ENODEV;
    }
    LOG_INF("display is ready.");

    display_blanking_off(g_display_dev);

    LOG_INF("screen manager has initialized succesfully.");
    screen_enter(g_screens[SCREEN_MANAGER_STARTING_SCREEN_INDEX]);

    g_thread_id = k_thread_create(&g_thread_data, screen_manager_stack,
                                  K_THREAD_STACK_SIZEOF(screen_manager_stack),
                                  screen_manager_thread_entry_point, NULL, NULL,
                                  NULL, SCREEN_MANAGER_PRIORITY, 0, K_NO_WAIT);

    LOG_INF("screen manager has been started.");
    return 0;
}

int screen_manager_deinit(void)
{
    k_thread_abort(g_thread_id);
    return 0;
}

/********************************************************************************************************************
 *
 *                                         Private Function Definitions
 *
 ********************************************************************************************************************/

static void screen_manager_thread_entry_point(void*, void*, void*)
{
    int current_screen = 0;
    while (true)
    {
        if (g_screen_count <= 0)
        {
            // No screen to show
            LOG_WRN("Screen loading..");
            k_msleep(1000);
            continue;
        }
        screen_refresh(g_screens[current_screen]);
        k_msleep(5);
    }
}

//! Initialize screen manager before calling main()
SYS_INIT_NAMED(screen_manager_init, screen_manager_init, APPLICATION,
               CONFIG_APPLICATION_INIT_PRIORITY);
