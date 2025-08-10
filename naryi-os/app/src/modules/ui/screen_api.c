#include "screen_api.h"

#include <errno.h>
#include <stddef.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

//! Module registration for logging
LOG_MODULE_REGISTER(screen);

int screen_enter(screen_api_t* api)
{
    if (api->enter == NULL)
    {
        LOG_ERR("api->enter is invalid (NULL).");
        return -EINVAL;
    }
    return api->enter();
}

int screen_refresh(screen_api_t* api)
{
    if (!api || api->refresh == NULL)
    {
        LOG_ERR("api->enter is invalid (NULL).");
        return -EINVAL;
    }
    return api->refresh();
}

int screen_exit(screen_api_t* api)
{
    if (api->exit == NULL)
    {
        LOG_ERR("api->exit is invalid (NULL).");
        return -EINVAL;
    }
    return api->exit();
}

bool screen_is_active(screen_api_t* api)
{
    if (api->is_active == NULL)
    {
        LOG_ERR("api->is_active is invalid (NULL).");
    }
    return api->is_active();
}
