#ifndef THINGS_H
#define THINGS_H

#include "system.h"

void things_create (void);

void things_twinkle (void);

void things_display (uint8_t tick);

bool things_killed_p (void);

void monster_move (int8_t dx, int8_t dy);

void things_move (void);

#endif
