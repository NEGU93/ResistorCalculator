#include "allegro.h"
#include "def.h"

#define SCREEN_W 300
#define SCREEN_H 50

#define SCREEN_MIDDLE_H 20

typedef struct {
	ALLEGRO_DISPLAY *display2;
	ALLEGRO_EVENT_QUEUE *event_queue2;
	ALLEGRO_TIMER *timer2;
	
}ALG;

double setValue(ALLEGRO_FONT* font);
int init(ALG* allg, ALLEGRO_FONT* font);
double SearchEV(ALG* allg, ALLEGRO_FONT* font);
int destroy(ALG* allg);

const float FPS = 10;

enum MYKEYS {
	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_BACKSPACE
};