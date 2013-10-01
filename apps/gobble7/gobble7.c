/** @file   gobble7.c
    @author M.P. Hayes
    @date   1 Oct 2013
    @brief 
*/

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "task.h"
#include "navswitch.h"
#include "led.h"
#include "timer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "things.h"


#define DISPLAY_RATE 200

#define MOVE_RATE 10

#define NAVSWITCH_RATE 50

#define MONSTER_FLASH_RATE 5


static bool running = 0;
static bool game_over = 1;
static int duration = 0;


static void display (__unused__ void *data)
{
    tinygl_update ();
}


static void monster_flash_task (__unused__ void *data)
{
    /* Flash the monster.  */
    if (running)
        monster_toggle ();
}


static void things_task (__unused__ void *data)
{
    /* Move the things.  */
    if (running)
    {
        duration++;
        things_move ();
    }
}


static void navswitch_task (__unused__ void *data)
{
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


int main (void)
{
    task_t tasks[] =
    {
        {.func = display, .period = TASK_RATE / DISPLAY_RATE},
        {.func = navswitch_task, .period = TASK_RATE / NAVSWITCH_RATE},
        {.func = things_task, .period = TASK_RATE / MOVE_RATE},
        {.func = monster_flash_task, .period = TASK_RATE / MONSTER_FLASH_RATE},
    };


    system_init ();
    navswitch_init ();
    led_init ();
    led_set (LED1, 0);

    tinygl_init (DISPLAY_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    tinygl_text ("GOBBLE: PUSH TO START");

    task_schedule (tasks, 4);

    return 0;
}
