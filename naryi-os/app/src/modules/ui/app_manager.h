#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__

#include "app.h"

/**
 * @brief Starts the screen manager.
 *
 * This function begins the screen manager's operation, enabling it to
 * manage and display screens as needed.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int app_manager_start(void);

/**
 * @brief Deinitializes the screen manager.
 *
 * This function releases all resources allocated by the screen manager.
 * It should be called when the screen manager is no longer needed.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int app_manager_stop(void);

#endif
