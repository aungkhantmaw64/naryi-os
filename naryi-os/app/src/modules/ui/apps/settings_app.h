#ifndef __SETTINGS_APP_H__
#define __SETTINGS_APP_H__

#include "app.h"

/**
 * @brief Creates an instance of the settings application.
 *
 * This function initializes and returns a pointer to the settings application's
 * API.
 *
 * @return A pointer to the settings application's API (app_api_t*).
 */
app_api_t* settings_app_create();

/**
 * @brief Destroys an instance of the settings application.
 *
 * This function cleans up resources associated with the settings application's
 * API.
 *
 * @param api A pointer to the settings application's API to be destroyed.
 * @return An integer indicating success (0) or failure (non-zero).
 */
int settings_app_destroy(app_api_t* api);

#endif
