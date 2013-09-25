/** @file   ir_spam1.c
    @author M. P. Hayes, UCECE
    @date   24 September 2013
    @brief  Repeatedly send message over IR.
*/

#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

/* Define polling rate in Hz.  */
#define LOOP_RATE 20


int main (void)
{
    int count = 5;

    system_init ();

    ir_uart_init ();

    pacer_init (LOOP_RATE);

    /* Paced loop.  */
    while (1)
    {
        /* Wait for next tick.  */
        pacer_wait ();
        
        ir_uart_putc ('A');
    }

    return 0;
}
