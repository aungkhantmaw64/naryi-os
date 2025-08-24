#ifndef __WATCHFACE_APP_H__
#define __WATCHFACE_APP_H__

#include "app.h"

/**
 * @brief Creates a new instance of the watchface application.
 *
 * This function initializes and returns a pointer to the application API
 * for the watchface application.
 *
 * @return A pointer to the app_api_t structure representing the watchface
 * application.
 */
app_api_t* watchface_app_create();

/**
 * @brief Destroys an instance of the watchface application.
 *
 * This function cleans up resources associated with the watchface application.
 *
 * @param api A pointer to the app_api_t structure representing the watchface
 * application.
 * @return An integer indicating success (0) or failure (non-zero).
 */
int watchface_app_destroy(app_api_t* api);

#endif
