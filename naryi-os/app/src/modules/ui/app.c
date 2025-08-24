#include "app.h"

#include <errno.h>
#include <stddef.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! Module registration for logging
LOG_MODULE_REGISTER(screen, CONFIG_LOG_DEFAULT_LEVEL);

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/

int app_enter(app_api_t* api)
{
    __ASSERT((api && api->enter), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->enter();
}

int app_exit(app_api_t* api)
{
    __ASSERT((api && api->exit), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->exit();
}

bool app_is_active(app_api_t* api)
{
    __ASSERT((api && api->is_active), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->is_active();
}

int app_on_button(app_api_t* api, const msg_bus_buttons_msg_t* p_msg)
{
    __ASSERT((api && api->on_button), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->on_button(p_msg);
}
