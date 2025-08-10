#ifndef __SCREEN_API_H__
#define __SCREEN_API_H__

#include <stdbool.h>

typedef struct screen_api_struct
{
    int (*enter)(void);
    int (*exit)(void);
    int (*refresh)(void);
    bool (*is_active)(void);
} screen_api_t;

int  screen_enter(screen_api_t* api);
int  screen_refresh(screen_api_t* api);
int  screen_exit(screen_api_t* api);
bool screen_is_active(screen_api_t* api);

#endif
