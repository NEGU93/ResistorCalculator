#ifndef PROGCORE_H_INCLUDED
#define PROGCORE_H_INCLUDED	

#include "allegro.h"
#include "def.h"

int initializeAllegro(ALL *allegro);
int eventHandler(ALL* allegro, int redraw);
int updateScreen(ALL* allegro);

#endif