#include "HAL/HAL.h"

static bool IsEnable = true;
static int32_t duration = 0;
static uint32_t freq = 0;
#if HAVE_PERI==1
static void BuzzerThread(void* argument)
{
    for (;;)
    {
        if (duration > 0)
        {
            ledcWriteTone(CONFIG_BUZZ_CHANNEL, freq);
            delay(duration);
            ledcWriteTone(CONFIG_BUZZ_CHANNEL, 0);

            duration = 0;
        }

        delay(50);
    }
}

void HAL::Buzz_init()
{
    pinMode(CONFIG_BUZZ_PIN, OUTPUT);
    ledcAttachPin(CONFIG_BUZZ_PIN, CONFIG_BUZZ_CHANNEL);
    ledcSetup(CONFIG_BUZZ_CHANNEL, 0, 8);
    ledcWriteTone(CONFIG_BUZZ_CHANNEL, 0);

    // Create Buzzer thread
    TaskHandle_t handleBuzzerThread;
    xTaskCreate(
        BuzzerThread,
        "BuzzerThread",
        800,
        nullptr,
        1,
        &handleBuzzerThread);
}

void HAL::Buzz_SetEnable(bool en)
{
    IsEnable = en;
}

void HAL::Buzz_Tone(uint32_t _freq, int32_t _duration)
{
    if (!IsEnable)
        return;

    if (_duration == 0)
    {
        ledcWriteTone(CONFIG_BUZZ_CHANNEL, _freq);
    } else
    {
        freq = _freq;
        duration = _duration;
    }
}

#else

void HAL::Buzz_init()
{
    
}

void HAL::Buzz_SetEnable(bool en)
{
    IsEnable = en;
}

void HAL::Buzz_Tone(uint32_t freq, int32_t duration)
{
    if(!IsEnable)
        return;
    
    if(duration >= 0)
    {
    }
    else
    {
    }
}
#endif