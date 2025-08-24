#ifndef __APP_H__
#define __APP_H__

#include <stdbool.h>

#include "msg_bus.h"

typedef struct app_api_struct
{
    int (*enter)(void);

    int (*exit)(void);

    bool (*is_active)(void);

    int (*on_button)(const msg_bus_buttons_msg_t* p_msg);

    int (*show_menu_icon)(void);

} app_api_t;

int app_enter(app_api_t* api);

int app_exit(app_api_t* api);

bool app_is_active(app_api_t* api);

int app_on_button(app_api_t* api, const msg_bus_buttons_msg_t* p_msg);

int app_show_menu_icon(app_api_t* api);

#endif
