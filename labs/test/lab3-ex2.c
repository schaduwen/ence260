/* @file   game.c
 * @author Yunu Cho, Owen Zhou
 * @date   10 October 2023
 * @brief  Implementation of a ping pong game.
 */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#include <stdio.h>

/* macros */
#define PACER_RATE 500
#define MESSAGE_RATE 10
#define MIN_ROUNDS 1
#define MAX_ROUNDS 9

/* function implementations */
void display_character(char c)
{
    char buffer[2];

    buffer[0] = c;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

uint8_t pre_phase(void)
{
    uint8_t rounds = MIN_ROUNDS;
    while(1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            rounds = (rounds == MAX_ROUNDS) ? MAX_ROUNDS : rounds+1;
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            rounds = (rounds == MIN_ROUNDS) ? MIN_ROUNDS : rounds-1;
        }
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            return rounds;
        }

        display_character(rounds+'0');
    }
}

int main (void)
{
    system_init ();
    navswitch_init();

    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    pacer_init(PACER_RATE);

    uint8_t rounds = pre_phase();
    printf("%d\n", rounds);
    // round_phase();
    // post_phase();
}
