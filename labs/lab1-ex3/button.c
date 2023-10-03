#include <avr/io.h>
#include "button.h"


/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    if ((PIND & (1<<7)) != 0) {
        return 1;
    }
    return 0;
    /* TODO.  */
}


/** Initialise button1.  */
void button_init (void)
{
    DDRD |= (0<<7);
    /* TODO.  */
}

