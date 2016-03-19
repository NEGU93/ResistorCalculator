#ifndef ALLEGRO_H_INCLUDED
#define ALLEGRO_H_INCLUDED

#define ALLEGRO_STATICLINK 
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_acodec.h>

#define SCREEN_X 1680	
#define SCREEN_Y 900

#define MAXRESOLUTION_X SCREEN_X
#define MAXRESOLUTION_Y SCREEN_Y

typedef struct {
	int screenWidth;
	int screenHeight;
	//DISPLAYS
	ALLEGRO_DISPLAY *display;
	//EVENT QUEUE
	ALLEGRO_EVENT_QUEUE *events_queue;
	//TIMERS
	ALLEGRO_TIMER * timer;
	//FONTS
	ALLEGRO_FONT *font;
	//BITMAPS
	ALLEGRO_BITMAP* fondo;
} ALL;

int init_allegro(ALL *allegro);
void destroyAll(ALL *allegro);
ALLEGRO_BITMAP *al_load_bitmap_resized(const char *filename, ALL* allegro); //TODO: que pase solo los ints que necesito y no toda la struct

#endif

