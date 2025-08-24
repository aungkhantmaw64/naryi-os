#ifndef __MUSIC_APP_H__
#define __MUSIC_APP_H__

#include "app.h"

/**
 * @brief Creates a new instance of the music application.
 *
 * This function initializes and returns a pointer to the music application's
 * API.
 *
 * @return A pointer to the app_api_t structure representing the music
 * application.
 */
app_api_t* music_app_create();

/**
 * @brief Destroys an instance of the music application.
 *
 * This function cleans up resources associated with the music application.
 *
 * @param api A pointer to the app_api_t structure representing the music
 * application.
 * @return An integer indicating success (0) or failure (non-zero).
 */
int music_app_destroy(app_api_t* api);

#endif
