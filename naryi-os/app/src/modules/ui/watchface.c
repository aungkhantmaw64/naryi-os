#include "watchface.h"

#include <lvgl.h>
#include <zephyr/logging/log.h>

#include "screen_api.h"

//! Module registration for logging
LOG_MODULE_REGISTER(watchface);

LV_IMG_DECLARE(wavy_bg);
LV_FONT_DECLARE(orbitron_47);

typedef struct
{
    lv_obj_t* hrs_mins;
    lv_obj_t* am_pm;
    lv_obj_t* date;
    lv_obj_t* day_of_the_week;
} pdw_clock_widget_t;

static lv_obj_t*          g_root_page      = {0};
static lv_obj_t*          g_background_img = {0};
static pdw_clock_widget_t g_clock_widget   = {0};

static screen_api_t g_watchface = {0};

static bool g_is_active = false;

static int watchface_enter(void)
{
    g_root_page = lv_obj_create(lv_scr_act());
    // Remove border, padding, etc.
    lv_obj_remove_style_all(g_root_page);
    lv_obj_set_width(g_root_page, LV_SIZE_CONTENT);
    lv_obj_set_height(g_root_page, LV_SIZE_CONTENT);
    // Enable clipping to make it circular
    lv_obj_set_style_border_width(g_root_page, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(g_root_page, LV_RADIUS_CIRCLE,
                            0); // Full circular radius
    lv_obj_set_style_bg_color(g_root_page, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_root_page, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_center(g_root_page);

    g_background_img = lv_img_create(g_root_page);

    lv_img_set_src(g_background_img, &wavy_bg);
    lv_obj_set_width(g_background_img, LV_SIZE_CONTENT);
    lv_obj_set_height(g_background_img, LV_SIZE_CONTENT);
    lv_obj_set_x(g_background_img, 0);
    lv_obj_set_y(g_background_img, 0);
    lv_obj_center(g_background_img);

    lv_obj_set_style_bg_img_src(g_root_page, g_background_img,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    g_clock_widget.hrs_mins = lv_label_create(g_root_page);
    lv_obj_align(g_clock_widget.hrs_mins, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(g_clock_widget.hrs_mins, &orbitron_47, 0);
    lv_obj_set_style_text_color(g_clock_widget.hrs_mins, lv_color_white(),
                                LV_PART_MAIN);
    lv_obj_set_style_text_opa(g_clock_widget.hrs_mins, LV_OPA_COVER,
                              LV_PART_MAIN);
    lv_label_set_text(g_clock_widget.hrs_mins, "10:22");

    g_clock_widget.am_pm = lv_label_create(g_root_page);
    lv_label_set_text(g_clock_widget.am_pm, "PM");
    lv_obj_set_style_text_font(g_clock_widget.am_pm, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(g_clock_widget.am_pm, lv_color_white(),
                                LV_PART_MAIN);
    lv_obj_set_style_text_opa(g_clock_widget.am_pm, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_align_to(g_clock_widget.am_pm, g_clock_widget.hrs_mins,
                    LV_ALIGN_OUT_TOP_RIGHT, 0, -5);

    g_clock_widget.date = lv_label_create(g_root_page);
    lv_label_set_text(g_clock_widget.date, "Sun");
    lv_obj_set_style_text_font(g_clock_widget.date, &lv_font_montserrat_36, 0);
    lv_obj_set_style_text_color(g_clock_widget.date, lv_color_white(),
                                LV_PART_MAIN);
    lv_obj_set_style_text_opa(g_clock_widget.date, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_align_to(g_clock_widget.date, g_clock_widget.hrs_mins,
                    LV_ALIGN_OUT_BOTTOM_MID, 0, 30);

    g_clock_widget.day_of_the_week = lv_label_create(g_root_page);
    lv_label_set_text(g_clock_widget.day_of_the_week, "3");
    lv_obj_set_style_text_font(g_clock_widget.day_of_the_week,
                               &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(g_clock_widget.day_of_the_week,
                                lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_opa(g_clock_widget.day_of_the_week, LV_OPA_COVER,
                              LV_PART_MAIN);

    lv_obj_align_to(g_clock_widget.day_of_the_week, g_clock_widget.date,
                    LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    return 0;
}

static int watchface_refresh(void)
{
    lv_task_handler();
    return 0;
}

static int watchface_exit(void)
{
    g_is_active = false;
    return 0;
}

bool watchface_is_active(void)
{
    return g_is_active;
}

screen_api_t* watchface_create()
{
    g_watchface.enter     = watchface_enter;
    g_watchface.exit      = watchface_exit;
    g_watchface.is_active = watchface_is_active;
    g_watchface.refresh   = watchface_refresh;
    return &g_watchface;
}

int watchface_destroy(screen_api_t* api)
{
    return 0;
}
