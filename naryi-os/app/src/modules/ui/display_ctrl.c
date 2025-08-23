#include "display_ctrl.h"

#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#define DISPLAY_PERIOD_AFTER_REFRESH_MS (50)

typedef enum
{
    DISPLAY_CTRL_WORK_TYPE_UNKNOWN = 0,
    DISPLAY_CTRL_WORK_TYPE_REFRESH,
} display_ctrl_work_type_t;

typedef struct
{
    display_ctrl_work_type_t type;
    struct k_work_delayable  timed_work;
} display_ctrl_delayable_work_t;

/********************************************************************************************************************
 *
 *                                         Private Function Prototypes
 *
 ********************************************************************************************************************/

/**
 * @brief Initializes the display controller.
 *
 * This function prepares the display controller for operation by
 * initializing necessary resources and configurations.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
static int display_ctrl_init(void);

/**
 * @brief Work handler for display control tasks.
 *
 * This function is executed when the associated work item is processed.
 * It performs tasks related to display control operations.
 *
 * @param work Pointer to the work structure associated with this handler.
 */
static void display_ctrl_work_handler(struct k_work* work);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! LCD device instance
static const struct device* g_display_dev = {0};

//! Module registration for logging
LOG_MODULE_REGISTER(display_ctrl, CONFIG_LOG_DEFAULT_LEVEL);

//! General schedulable work item for display controller
static display_ctrl_delayable_work_t g_work = {0};

int display_ctrl_start(void)
{
    g_display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

    if (!device_is_ready(g_display_dev))
    {
        LOG_ERR("device not ready, aborting screen_manager.");
        return -ENODEV;
    }
    LOG_DBG("display is ready.");

    display_blanking_off(g_display_dev);

    k_work_schedule(&g_work.timed_work, K_MSEC(1000));

    LOG_INF("display-ctrl has started.");

    return 0;
}

static int display_ctrl_init(void)
{
    k_work_init_delayable(&g_work.timed_work, display_ctrl_work_handler);

    g_work.type = DISPLAY_CTRL_WORK_TYPE_REFRESH;

    return 0;
}

static void display_ctrl_work_handler(struct k_work* work)
{
    struct k_work_delayable* dwork = k_work_delayable_from_work(work);

    display_ctrl_delayable_work_t* ctx =
        CONTAINER_OF(dwork, display_ctrl_delayable_work_t, timed_work);

    switch (ctx->type)
    {
        case DISPLAY_CTRL_WORK_TYPE_REFRESH:
            lv_task_handler();
            k_work_schedule(&g_work.timed_work,
                            K_MSEC(DISPLAY_PERIOD_AFTER_REFRESH_MS));
            break;
        default:
            break;
    }
}

//! Initialize display ctrl before calling main()
SYS_INIT_NAMED(display_ctrl_init, display_ctrl_init, APPLICATION,
               CONFIG_APPLICATION_INIT_PRIORITY);
