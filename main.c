#include "def.h"
#include "allegro.h"
#include "programCore.h"

void main(void) {
	//Allegro initialization
	ALL allegroData = { 0, 0, NULL, NULL, NULL, NULL, NULL };
	ALL* allegro = &allegroData;
	int i = init_allegro(allegro);

	//I don't know why it doesn't work
	/*if (i == 0) {
		//printf( "Failed to initialize allegro. Closing Program.\n" );
	}*/

	pos mouse = { 0, 0 };
	int redraw = FALSE;
	int stillRunning = TRUE;

	while (stillRunning == TRUE) {
		stillRunning = eventHandler(allegro, &redraw);
	}

	al_destroy_display(allegro->display);
	destroyAll(allegro);
}