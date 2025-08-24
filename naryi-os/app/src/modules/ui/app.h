#ifndef __APP_H__
#define __APP_H__

#include <stdbool.h>

#include "msg_bus.h"

/**
 * @brief Structure defining the application API.
 *
 * This structure contains function pointers that represent
 * the interface for interacting with an application module.
 */
typedef struct app_api_struct
{
    // Function to initialize or enter the application.
    int (*enter)(void);
    // Function to clean up or exit the application.
    int (*exit)(void);
    // Function to check if the application is active.
    bool (*is_active)(void);
    // Callback for handling button messages.
    int (*on_button)(const msg_bus_buttons_msg_t* p_msg);
    // Function to display the menu icon for the application.
    int (*show_menu_icon)(void);
} app_api_t;

/**
 * @brief Initializes and enters the application.
 *
 * @param api Pointer to the application API structure.
 * @return int Status code indicating success or failure.
 */
int app_enter(app_api_t* api);

/**
 * @brief Exits and cleans up the application.
 *
 * @param api Pointer to the application API structure.
 * @return int Status code indicating success or failure.
 */
int app_exit(app_api_t* api);

/**
 * @brief Checks if the application is currently active.
 *
 * @param api Pointer to the application API structure.
 * @return bool True if the application is active, false otherwise.
 */
bool app_is_active(app_api_t* api);

/**
 * @brief Handles button events for the application.
 *
 * @param api Pointer to the application API structure.
 * @param p_msg Pointer to the button message structure.
 * @return int Status code indicating success or failure.
 */
int app_on_button(app_api_t* api, const msg_bus_buttons_msg_t* p_msg);

/**
 * @brief Displays the menu icon for the application.
 *
 * @param api Pointer to the application API structure.
 * @return int Status code indicating success or failure.
 */
int app_show_menu_icon(app_api_t* api);

#endif
