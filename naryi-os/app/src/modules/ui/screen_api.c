#include "screen_api.h"

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

int screen_enter(screen_api_t* api)
{
    __ASSERT((api && api->enter), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->enter();
}

int screen_refresh(screen_api_t* api)
{
    __ASSERT((api && api->refresh), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->refresh();
}

int screen_exit(screen_api_t* api)
{
    __ASSERT((api && api->exit), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->exit();
}

int screen_up(screen_api_t* api)
{
    __ASSERT((api && api->left), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->left();
}

int screen_down(screen_api_t* api)
{
    __ASSERT((api && api->right), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->right();
}

bool screen_is_active(screen_api_t* api)
{
    __ASSERT((api && api->is_active), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->is_active();
}
