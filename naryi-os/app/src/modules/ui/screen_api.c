#include "screen_api.h"

#include <errno.h>
#include <stddef.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

//! Module registration for logging
LOG_MODULE_REGISTER(screen, CONFIG_LOG_DEFAULT_LEVEL);

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

bool screen_is_active(screen_api_t* api)
{
    __ASSERT((api && api->is_active), "Invalid api at line %d, in %s", __LINE__,
             __func__);
    return api->is_active();
}
