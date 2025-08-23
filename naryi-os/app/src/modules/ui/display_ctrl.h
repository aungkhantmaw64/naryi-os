#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/**
 * @brief Initializes and starts the display controller.
 *
 * This function sets up the necessary resources and configurations
 * required to operate the display controller. It should be called
 * before any other display-related operations.
 *
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int display_ctrl_start(void);

#endif
