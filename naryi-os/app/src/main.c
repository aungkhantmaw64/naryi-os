#include <lvgl.h>
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

#include "modules/buttons/buttons.h"
#include "modules/ui/display_ctrl.h"
#include "modules/ui/screen_manager.h"
#include "modules/ui/watchface.h"

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

int main(void)
{
    __ASSERT(display_ctrl_start() == 0, "Failed to start display_ctrl.");

    __ASSERT(screen_manager_push_screen(watchface_create()) == 0,
             "Failed to push the watchface to screen_manager.");

    __ASSERT(screen_manager_start() == 0,
             "Failed to start the screen_manager.");

    __ASSERT(buttons_start() == 0, "Failed to start buttons.");

    return 0;
}
