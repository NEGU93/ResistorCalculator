#include <math.h>
#include "programCore.h"
#define PI 3.14159265358979323846

BOOL initializeGUIElements(GUIElements* gui) {
	if (gui->resistorButton.buttonImage = al_load_bitmap("Resources/Buttons/resistorButtonImage1.png")) {
		if (gui->resistorButton.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/resistorButtonImage2.png")) {
			gui->resistorButton.buttonPos.x = SCREEN_X - 3 * al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
			gui->resistorButton.buttonPos.y = al_get_bitmap_height(gui->resistorButton.buttonImage) / 2;
			if (gui->wireButton.buttonImage = al_load_bitmap("Resources/Buttons/wireButtonImage1.png")) {
				if (gui->wireButton.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/wireButtonImage2.png")) {
					gui->wireButton.buttonPos.x = SCREEN_X - 3 * al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
					gui->wireButton.buttonPos.y = 2 * al_get_bitmap_height(gui->resistorButton.buttonImage);
					if (gui->resistor = al_load_bitmap("Resources/resistor.png")) {
						gui->resistorAngle = 0;
						return TRUE;
					}
					else { printf("Unable to load resistor Image"); }
				}
				else { printf("Unable to load wire button Image 2"); }
			}
			else { printf("Unable to load wire button Image 1"); }
		}
		else { printf("Unable to load resistor button image 2"); }
	}
	else { printf("Unable to load resistor button image 1"); }

	return FALSE;
}
BOOL eventHandler(ALL* allegro, ProgramElements* elements, GUIElements* gui) {
	int stillPlaying = TRUE;
	ALLEGRO_EVENT ev;
	al_wait_for_event(allegro->events_queue, &ev);

	if (ev.type == ALLEGRO_EVENT_TIMER) { elements->redraw = TRUE; }
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		stillPlaying = FALSE;
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
		elements->mouse.x = ev.mouse.x;
		elements->mouse.y = ev.mouse.y;
		//checkMouse(allegro);
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { click(allegro, elements->mouse, gui, elements); }
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_SPACE:
			if (gui->resistorAngle == 0) { gui->resistorAngle = PI / 2; }
			else { gui->resistorAngle = 0; }
		}
	}
	//if redraw then update screen
	if ( elements->redraw == TRUE ) {
		updateScreen(allegro, gui, elements->mouse, elements->modeEnum);
		elements->redraw = FALSE;
	}
	return stillPlaying;
}
//Update
void updateScreen(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum) {
	al_set_target_backbuffer(allegro->display);
	al_clear_to_color(al_map_rgb(WHITE));
	//al_draw_bitmap(allegro->fondo, 0, 0, 0);
	updateButton(gui->resistorButton, mouse);
	updateButton(gui->wireButton, mouse);
	if (modeEnum == RESISTORPLACE) {
		if (gui->resistorAngle == 0) {
			al_draw_bitmap(gui->resistor, mouse.x, mouse.y - al_get_bitmap_height(gui->resistor) / 2, 0);
		}
		else {
			al_draw_rotated_bitmap(gui->resistor, al_get_bitmap_width(gui->resistor) / 2, al_get_bitmap_width(gui->resistor) / 2, mouse.x - al_get_bitmap_height(gui->resistor), mouse.y + al_get_bitmap_width(gui->resistor) / 2, gui->resistorAngle, 0);
		}
	}
	al_flip_display();
}
void updateButton(Button button, pos mouse) {
	if (checkButton(button, mouse)) {
		al_draw_bitmap(button.mouseOverButtonImage, button.buttonPos.x, button.buttonPos.y, 0);
	}
	else {
		al_draw_bitmap(button.buttonImage, button.buttonPos.x, button.buttonPos.y, 0);
	}
}

BOOL checkButton(Button button, pos mouse) {
	int mouseOverButton = FALSE;
	if ((mouse.x > button.buttonPos.x) && (mouse.x < button.buttonPos.x + al_get_bitmap_width(button.buttonImage))) {
		if ((mouse.y > button.buttonPos.y) && (mouse.y < button.buttonPos.y + al_get_bitmap_height(button.buttonImage))) {
			mouseOverButton = TRUE;
		}
		else { mouseOverButton = FALSE; }
	}
	else { mouseOverButton = FALSE; }
	return mouseOverButton;
}
BOOL click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements) {
	if (elements->modeEnum == NORMAL) {
		if (checkButton(gui->resistorButton, mouse)) {
			elements->modeEnum = RESISTORPLACE;
		}
	}
	else if (elements->modeEnum == RESISTORPLACE) {
		elements->modeEnum = NORMAL;
	}
}

 