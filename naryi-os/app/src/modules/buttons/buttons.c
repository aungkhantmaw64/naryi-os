#include "buttons.h"

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

enum
{
    //! Represents the LEFT button index
    LEFT_BUTTON = 0,
    //! Represents the RIGHt button index
    RIGHT_BUTTON,
    //! Represents the ENTER button index
    ENTER_BUTTON,
    //! Represents the BACK button index
    BACK_BUTTON,
};

/**
 * @brief Callback to be executed when any button is pressed
 *
 */
static void button_pressed(const struct device* dev, struct gpio_callback* cb,
                           uint32_t pins);

/********************************************************************************************************************
 *
 *                                         Private Variables
 *
 ********************************************************************************************************************/

//! Button array to represent LEFT, RIGHT, ENTER, and BACK
static struct gpio_dt_spec buttons[] = {
    [LEFT_BUTTON]  = GPIO_DT_SPEC_GET(DT_NODELABEL(button1), gpios),
    [RIGHT_BUTTON] = GPIO_DT_SPEC_GET(DT_NODELABEL(button2), gpios),
    [ENTER_BUTTON] = GPIO_DT_SPEC_GET(DT_NODELABEL(button3), gpios),
    [BACK_BUTTON]  = GPIO_DT_SPEC_GET(DT_NODELABEL(button4), gpios)};

//! Button callback context
static struct gpio_callback button_cb_data = {0};

//! Module registration for logging
LOG_MODULE_REGISTER(buttons, CONFIG_LOG_DEFAULT_LEVEL);

/********************************************************************************************************************
 *
 *                                         Public Function Definitions
 *
 ********************************************************************************************************************/

int buttons_start(void)
{
    int ret = {0};

    gpio_init_callback(&button_cb_data, button_pressed, 0);

    for (int i = {0}; i < ARRAY_SIZE(buttons); i++)
    {
        struct gpio_dt_spec* p_button = &buttons[i];

        if (!gpio_is_ready_dt(p_button))
        {
            LOG_ERR("Error: button device %s is not ready\n",
                    p_button->port->name);

            return -ENODEV;
        }

        LOG_INF("button device %s is ready.", p_button->port->name);

        ret = gpio_pin_configure_dt(p_button, GPIO_INPUT);

        if (ret != 0)
        {
            LOG_ERR("Error %d: failed to configure %s pin %d\n", ret,
                    p_button->port->name, p_button->pin);

            return ret;
        }

        ret =
            gpio_pin_interrupt_configure_dt(p_button, GPIO_INT_EDGE_TO_ACTIVE);

        if (ret != 0)
        {
            LOG_ERR("Error %d: failed to configure interrupt on %s pin %d\n",
                    ret, p_button->port->name, p_button->pin);

            return 0;
        }

        button_cb_data.pin_mask |= BIT(p_button->pin);

        gpio_add_callback(p_button->port, &button_cb_data);

        LOG_INF("Set up button at %s pin %d\n", p_button->port->name,
                p_button->pin);
    }

    return 0;
}

int buttons_stop(void)
{
    return 0;
}

/********************************************************************************************************************
 *
 *                                         Private Function Definitions
 *
 ********************************************************************************************************************/

static void button_pressed(const struct device* dev, struct gpio_callback* cb,
                           uint32_t pins)
{
    for (int i = 0; i < ARRAY_SIZE(buttons); i++)
    {
        if (BIT(buttons[i].pin) == pins)
        {
            LOG_INF("Pin %d is pressed!\n", buttons[i].pin);
        }
    }
}
