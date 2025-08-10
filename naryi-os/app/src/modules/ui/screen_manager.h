#ifndef __SCREEN_MANAGER_H__
#define __SCREEN_MANAGER_H__

#include "screen_api.h"

int screen_manager_init(void);

int screen_manager_push_screen(screen_api_t* api);

int screen_manager_start(void);

int screen_manager_deinit(void);

#endif
