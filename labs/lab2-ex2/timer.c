#include <avr/io.h>
#include "timer.h"

/* Initialise timer.  */
void timer_init (void)
{
    /* TODO */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

}


/* Wait for the specified length of time.  */
void timer_delay_ms (uint16_t milliseconds)
{
    uint16_t count_stop=0;

    /* TODO: Calculate the timer/counter value needed 
       for the given number of milliseconds. */
    count_stop=milliseconds*milliseconds*(8e6/1024)/1000;

    /* TODO: Wait for the timer/couter to reach the 
       value calculated above.  */
    TCNT1=0;  /* reset the counter */

    while (TCNT1 < count_stop)
    {
        continue;
    }

}
