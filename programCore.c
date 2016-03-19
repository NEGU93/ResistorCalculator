#include "programCore.h"

int initializeAllegro(ALL *allegro) {
	
}

int eventHandler(ALL* allegro, int redraw) {
	int stillPlaying = TRUE;
	ALLEGRO_EVENT ev;
	al_wait_for_event(allegro->events_queue, &ev);

	if (ev.type == ALLEGRO_EVENT_TIMER) { redraw = TRUE; }
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		stillPlaying = FALSE;
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
		//mouse.x = ev.mouse.x;
		//mouse.y = ev.mouse.y;
		//checkMouse(allegro);
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { /*click(allegro);*/ }
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE: 
			break;
		}
	}
	//if redraw then update screen
	if ( redraw == TRUE ) {
		updateScreen(allegro);
		redraw = FALSE;
	}
	return stillPlaying;
}

int updateScreen(ALL* allegro) {
	al_set_target_backbuffer(allegro->display);
	al_clear_to_color(al_map_rgb(WHITE));
	al_draw_bitmap(allegro->fondo, 0, 0, 0);

	al_flip_display();
}