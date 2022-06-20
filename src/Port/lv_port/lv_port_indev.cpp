/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "HAL/HAL.h"
#include "Port/Display.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t* indev_drv, lv_indev_data_t* data);
static void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );

/**********************
 *  STATIC VARIABLES
 **********************/
static TouchPoint_t coordinate;
lv_indev_t * indev_touchpad;
lv_indev_t* encoder_indev;
lv_group_t * lv_group;

M5Touch T;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
// static lv_indev_drv_t indev_drv;
static lv_indev_drv_t indev_drv_Touchpad;
static lv_indev_drv_t indev_drv_Encoder;
// extern TFT_eSPI tft;

void lv_port_indev_init(void)
{

    // lv_indev_drv_init( &indev_drv_Touchpad );
    // indev_drv_Touchpad.type = LV_INDEV_TYPE_POINTER;
    // indev_drv_Touchpad.read_cb = my_touchpad_read;
    // indev_touchpad = lv_indev_drv_register( &indev_drv_Touchpad );
    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv_Encoder);
    indev_drv_Encoder.type = LV_INDEV_TYPE_POINTER;
    indev_drv_Encoder.read_cb = encoder_read;
    encoder_indev = lv_indev_drv_register(&indev_drv_Encoder);

    /* Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     * add objects to the group with `lv_group_add_obj(group, obj)`
     * and assign this input device to group to navigate in it:
     * `lv_indev_set_group(indev_encoder, group);` */
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
/*Read the touchpad*/
static void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
     HAL::Touch_GetPressPoint(&coordinate);
    // Serial.printf("x:%d, y:%d \r\n", coordinate.x, coordinate.y);
    if (coordinate.x == -1) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->point.x = coordinate.x;
        data->point.y = coordinate.y;
        data->state = LV_INDEV_STATE_PR;
    }
    // uint16_t touchX, touchY;

    // bool touched = tft.getTouch( &touchX, &touchY);

    // if( !touched )
    // {
    //     data->state = LV_INDEV_STATE_REL;
    // }
    // else
    // {
    //     data->state = LV_INDEV_STATE_PR;

    //     /*Set the coordinates*/
    //     data->point.x = touchX;
    //     data->point.y = touchY;

    // }
}
/*------------------
 * Encoder
 * -----------------*/

/* Initialize your keypad */
static void encoder_init(void)
{
    /*Do it in Init*/
}


/* Will be called by the library to read the encoder */
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    data->enc_diff = HAL::Encoder_GetDiff();
    data->state =  HAL::Encoder_GetIsPush() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
