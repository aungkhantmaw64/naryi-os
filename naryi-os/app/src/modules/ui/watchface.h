#ifndef __WATCHFACE_H__
#define __WATCHFACE_H__

#include "screen_api.h"

screen_api_t* watchface_create();

int watchface_destroy(screen_api_t* api);

#endif
