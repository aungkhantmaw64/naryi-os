#include "buttons.h"

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

#include "msg_bus.h"

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

typedef struct button_work
{
    uint32_t pins;

    struct k_work_delayable timed_work;
} buttons_delayable_work_t;

/**
 * @brief Callback to be executed when any button is pressed
 *
 */
static void button_pressed(const struct device* dev, struct gpio_callback* cb,
                           uint32_t pins);

static void buttons_cooldown_work_handler(struct k_work* work);

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

static buttons_delayable_work_t g_cooldown_work = {0};

//! Module registration for logging
LOG_MODULE_REGISTER(buttons, CONFIG_LOG_DEFAULT_LEVEL);

ZBUS_CHAN_DECLARE(msg_bus_buttons_chan);

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

    k_work_init_delayable(&g_cooldown_work.timed_work,
                          buttons_cooldown_work_handler);

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
    g_cooldown_work.pins = pins;

    k_work_schedule(&g_cooldown_work.timed_work, K_MSEC(15));
}

static void buttons_cooldown_work_handler(struct k_work* work)
{
    struct k_work_delayable* dwork = k_work_delayable_from_work(work);

    buttons_delayable_work_t* ctx =
        CONTAINER_OF(dwork, buttons_delayable_work_t, timed_work);

    for (int i = 0; i < ARRAY_SIZE(buttons); i++)
    {
        if (BIT(buttons[i].pin) == ctx->pins)
        {
            msg_bus_buttons_msg_t msg = {
                .direction = MSG_BUS_BUTTON_DIR_UNKNOWN,
            };
            switch (i)
            {
                case LEFT_BUTTON:
                    msg.direction = MSG_BUS_BUTTON_DIR_LEFT;
                    break;
                case RIGHT_BUTTON:
                    msg.direction = MSG_BUS_BUTTON_DIR_RIGHT;
                    break;
                case ENTER_BUTTON:
                    msg.direction = MSG_BUS_BUTTON_DIR_ENTER;
                    break;
                case BACK_BUTTON:
                    msg.direction = MSG_BUS_BUTTON_DIR_BACK;
                    break;
            }
            zbus_chan_pub(&msg_bus_buttons_chan, &msg, K_NO_WAIT);
        }
    }
}
