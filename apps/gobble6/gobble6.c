/** @file   gobble6.c
    @author M.P. Hayes
    @date   29 Sep 2013
    @brief 
*/

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "led.h"
#include "timer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "things.h"


#define LOOP_RATE 200

#define MOVE_RATE 25

#define NAVSWITCH_RATE 50


int main (void)
{
    uint16_t tick = 0;
    uint16_t navswitch_tick = 0;
    bool running = 0;
    bool game_over = 1;
    int duration = 0;


    system_init ();
    navswitch_init ();
    led_init ();
    led_set (LED1, 0);

    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    pacer_init (LOOP_RATE);

    tinygl_text ("GOBBLE: PUSH TO START");

    while (1)
    {
        uint8_t col;

        /* Refresh things.  */
        for (col = 0; col < TINYGL_WIDTH; col++)
        {
            pacer_wait ();

            tinygl_update ();
        }

        navswitch_tick++;
        if (navswitch_tick >= LOOP_RATE / NAVSWITCH_RATE)
        {
            static int count = 0;

            count++;
            if (running && count % 4 == 0)
                monster_toggle ();

            navswitch_tick = 0;

            navswitch_update ();

            if (navswitch_push_event_p (NAVSWITCH_NORTH))
                monster_move (0, -1);
            if (navswitch_push_event_p (NAVSWITCH_SOUTH))
                monster_move (0, 1);
            if (navswitch_push_event_p (NAVSWITCH_EAST))
                monster_move (1, 0);
            if (navswitch_push_event_p (NAVSWITCH_WEST))
                monster_move (-1, 0);
            
            /* Pause/resume things running around.  */
            if (navswitch_push_event_p (NAVSWITCH_PUSH))
            {
                if (! running && game_over)
                {
                    srand (timer_get ());
                    tinygl_clear ();
                    things_create ();

                    duration = 0;
                    game_over = 0;
                }

                running = !running;
                led_set (LED1, running);
            }

            if (running && things_killed_p ())
            {
                char buffer[6];
                
                running = 0;
                game_over = 1;
                led_set (LED1, 0);
                sprintf (buffer, "%d", duration);
                tinygl_text (buffer);
            }
        }

        tick++;
        if (tick >= LOOP_RATE / MOVE_RATE)
        {
            tick = 0;
            
            if (running)
            {
                duration++;
                things_move ();
            }
        }
    }
    return 0;
}
