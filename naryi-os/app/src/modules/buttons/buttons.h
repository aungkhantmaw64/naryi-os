#ifndef __BUTTONS_H__
#define __BUTTONS_H__

/**
 * @brief Initializes the buttons module and prepares it for use.
 *
 * @return 0 on success or an appropriate error code on failure.
 */
int buttons_start(void);

/**
 * @brief Stops the buttons module and releases any allocated resources.
 *
 * @return 0 on success or an appropriate error code on failure.
 */
int buttons_stop(void);

#endif
