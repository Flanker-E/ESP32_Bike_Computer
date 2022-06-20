#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <TFT_eSPI.h>
// #include "App/Config/Config.h"
#include "HAL/Config/Config.h"
#include "lvgl.h"
#include "FS.h"

// #include "TFT_eSPI.h"
typedef TFT_eSPI SCREEN_CLASS;
// TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
// static lv_indev_drv_t indev_drv;

// static const uint16_t screenWidth  = 320;
// static const uint16_t screenHeight = 240;

// static lv_disp_draw_buf_t draw_buf;
// static lv_color_t buf[ screenWidth * 80 ];

// static lv_color_t lv_disp_buf_p[ CONFIG_SCREEN_BUFFER_SIZE ];
// static lv_disp_draw_buf_t disp_buf;
// static lv_disp_drv_t disp_drv;

// TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
#define CALIBRATION_FILE "/TouchCalData1"

#define REPEAT_CAL false
// typedef TFT_eSPI SCREEN_CLASS;
// lv_indev_t * indev_touchpad;
// lv_indev_t* encoder_indev;
extern lv_indev_t * indev_touchpad;
extern lv_indev_t * encoder_indev;

void Port_Init();
void DisplayFault_Init(SCREEN_CLASS* scr);
void lv_port_disp_init(SCREEN_CLASS* scr);
void lv_fs_if_init();
void lv_port_indev_init();

extern TaskHandle_t handleTaskLvgl;

#endif
