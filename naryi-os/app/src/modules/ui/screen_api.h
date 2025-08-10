#ifndef __SCREEN_API_H__
#define __SCREEN_API_H__

#include <stdbool.h>

/**
 * @brief Structure representing the screen API.
 *
 * This structure defines a set of function pointers for managing screen
 * operations. Each function pointer corresponds to a specific screen-related
 * action.
 */
typedef struct screen_api_struct
{
    /**
     * @brief Function to enter the screen.
     * @return Returns an integer status code.
     */

    int (*enter)(void);

    /**
     * @brief Function to exit the screen.
     * @return Returns an integer status code.
     */
    int (*exit)(void);

    /**
     * @brief Function to refresh the screen.
     * @return Returns an integer status code.
     */
    int (*refresh)(void);

    /**
     * @brief Function to check if the screen is active.
     * @return Returns a boolean indicating whether the screen is active.
     */
    bool (*is_active)(void);
} screen_api_t;

/**
 * @brief Enter the screen using the provided API.
 *
 * @param api Pointer to the screen API structure.
 * @return Returns an integer status code.
 */
int screen_enter(screen_api_t* api);

/**
 * @brief Refresh the screen using the provided API.
 *
 * @param api Pointer to the screen API structure.
 * @return Returns an integer status code.
 */
int screen_refresh(screen_api_t* api);

/**
 * @brief Exit the screen using the provided API.
 *
 * @param api Pointer to the screen API structure.
 * @return Returns an integer status code.
 */
int screen_exit(screen_api_t* api);

/**
 * @brief Check if the screen is active using the provided API.
 *
 * @param api Pointer to the screen API structure.
 * @return Returns a boolean indicating whether the screen is active.
 */
bool screen_is_active(screen_api_t* api);

#endif
