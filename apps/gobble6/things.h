#ifndef THINGS_H
#define THINGS_H

#include "system.h"

bool things_killed_p (void);

void things_create (void);

void things_move (void);

void monster_move (int8_t dx, int8_t dy);

void monster_toggle (void);

#endif
