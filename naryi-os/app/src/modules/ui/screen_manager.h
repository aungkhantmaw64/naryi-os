#ifndef __SCREEN_MANAGER_H__
#define __SCREEN_MANAGER_H__

#include "screen_api.h"

/**
 * @brief Pushes a new screen onto the screen stack.
 *
 * This function adds a new screen to the stack managed by the screen manager.
 * The screen is defined by the provided screen API.
 *
 * @param api Pointer to the screen API structure.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int screen_manager_push_screen(screen_api_t* api);

/**
 * @brief Starts the screen manager.
 *
 * This function begins the screen manager's operation, enabling it to
 * manage and display screens as needed.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int screen_manager_start(void);

/**
 * @brief Deinitializes the screen manager.
 *
 * This function releases all resources allocated by the screen manager.
 * It should be called when the screen manager is no longer needed.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int screen_manager_deinit(void);

#endif
