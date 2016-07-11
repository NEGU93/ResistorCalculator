#ifndef ALLEGRO_H_INCLUDED
#define ALLEGRO_H_INCLUDED

#define ALLEGRO_STATICLINK 
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_acodec.h>

#define SCREEN_X 1280	
#define SCREEN_Y 720

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
	ALLEGRO_BITMAP* downBar;
} ALL;

int init_allegro(ALL *allegro);
void destroyAll(ALL *allegro);
ALLEGRO_BITMAP *al_load_bitmap_resized(const char *filename, ALL* allegro); //TODO: que pase solo los ints que necesito y no toda la struct
void draw_line(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, float thickness);
void draw_line_inverted(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, float thickness);

#endif

