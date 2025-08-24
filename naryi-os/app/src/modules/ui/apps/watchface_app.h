#ifndef __WATCHFACE_APP_H__
#define __WATCHFACE_APP_H__

#include "app.h"

/**
 * @brief Creates a watchface screen.
 *
 * This function initializes and returns a pointer to the watchface screen API.
 * It sets up the necessary resources for the watchface screen.
 *
 * @return app_api_t* Pointer to the initialized watchface screen API.
 */
app_api_t* watchface_app_create();

/**
 * @brief Destroys the watchface screen.
 *
 * This function releases the resources associated with the watchface screen.
 *
 * @param api Pointer to the watchface screen API to be destroyed.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int watchface_app_destroy(app_api_t* api);

#endif
