/** @file   beep1.c
    @author M.P. Hayes
    @date   17 Sep 2013
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "button.h"
#include "delay.h"


/* Connect piezo tweeter to outermost pins of UCFK4 P1 connector.  */
#define PIEZO_PIO PIO_DEFINE (PORT_D, 6)


#define LOOP_RATE 880


int main (void)
{
    system_init ();

    pio_config_set (PIEZO_PIO, PIO_OUTPUT_LOW);

    button_init ();

    pacer_init (LOOP_RATE);
    
    while (1)
    {
        pacer_wait ();

        /* Generate annoying tone.  */
        pio_output_toggle (PIEZO_PIO);

        /* While button down introduce delay to produce overrun.  */
        if (button_down_p (BUTTON1))
        {
            delay_ms (2);
        }
    }

    return 0;
}
