/** @file   pulsate1.c
    @author M.P. Hayes
    @date   25 Sep 2013
    @brief  Example of controlling pixel brightness with PWM.
*/

#include <stdlib.h>
#include "system.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"

/* This controls the range of luminance.  A bigger number gives more
   dynamic range but requires a faster update rate.  */
#define LUMINANCE_STEPS 25

/* This needs to be fast enough to prevent the eye noticing flicker.
   A lower value (say 5) is useful for flashing pixels.  */
#define PWM_RATE 40

/* This is the rate (Hz) of luminance changes.  */
#define PULSATE_RATE 10

#define UPDATE_RATE (LUMINANCE_STEPS * PWM_RATE)

#define LOOP_RATE (TINYGL_WIDTH * UPDATE_RATE)

int main (void)
{
    uint16_t pulsate_tick = 0;
    uint8_t pwm_tick = 0;
    uint8_t x;
    uint8_t y;
    uint8_t col;
    uint8_t luminance = 0;
    /* This controls the luminance levels.  The maximum value
       of LUMINANCE_STEPS gives 100 percent duty cycle.   */
    const uint8_t levels[] = {1, 2, 4, 8, 15, 25, 15, 8, 4, 2, 1};

    system_init ();

    tinygl_init (LOOP_RATE);
    led_init ();

    pacer_init (LOOP_RATE);

    while (1)
    {
        uint8_t state;

        /* Refresh display.  */
        for (col = 0; col < TINYGL_WIDTH; col++)
        {
            pacer_wait ();

            tinygl_update ();
        }

        pulsate_tick++;
        if (pulsate_tick >= UPDATE_RATE / PULSATE_RATE)
        {
            pulsate_tick = 0;

            if (luminance == 0)
                luminance = ARRAY_SIZE (levels) - 1;
            else
                luminance--;
        }

        state = levels[luminance] > pwm_tick;

        /* Pulse width modulate pixels to control luminance.  */
        for (x = 0; x < TINYGL_WIDTH; x++)
        {
            for (y = 0; y < TINYGL_HEIGHT; y++)
            {
                tinygl_draw_point (tinygl_point (x, y), state);
            }
        }

        led_set (LED1, state);

        pwm_tick++;
        if (pwm_tick >= UPDATE_RATE / PWM_RATE)
        {
            pwm_tick = 0;
        }
    }
    return 0;
}
