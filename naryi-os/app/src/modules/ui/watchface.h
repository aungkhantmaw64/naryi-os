#ifndef __WATCHFACE_H__
#define __WATCHFACE_H__

#include "screen_api.h"

/**
 * @brief Creates a watchface screen.
 *
 * This function initializes and returns a pointer to the watchface screen API.
 * It sets up the necessary resources for the watchface screen.
 *
 * @return screen_api_t* Pointer to the initialized watchface screen API.
 */
screen_api_t* watchface_create();

/**
 * @brief Destroys the watchface screen.
 *
 * This function releases the resources associated with the watchface screen.
 *
 * @param api Pointer to the watchface screen API to be destroyed.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int watchface_destroy(screen_api_t* api);

#endif
