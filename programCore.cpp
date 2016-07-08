//#include <math.h>
#include "programCore.h"
#define PI 3.14159265358979323846

ProgramCore::ProgramCore(GUIElements* gui) {
	if (!initializeGUIElements(gui)) {
		printf("Error initializing guiElements\n");
	}
}

BOOL ProgramCore::eventHandler(ALL* allegro, ProgramElements* elements, GUIElements* gui) {
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
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { 
		if (ev.mouse.button == 2) { //Right Click
			rightClick(elements, gui);
		}
		else { click(allegro, elements->mouse, gui, elements); } //Left Click
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) { //Keyboard
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
//Initializers
BOOL ProgramCore::initializeGUIElements(GUIElements* gui) {
	if (initializeMenu(gui)) {
		if (gui->resistorButton.buttonImage = al_load_bitmap("Resources/Buttons/resistorButtonImage1.png")) {
			if (gui->resistorButton.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/resistorButtonImage2.png")) {
				gui->resistorButton.buttonPos.x = SCREEN_X - 3 * al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
				gui->resistorButton.buttonPos.y = 0 * al_get_bitmap_height(gui->resistorButton.buttonImage);
				if (gui->wireButton.buttonImage = al_load_bitmap("Resources/Buttons/wireButtonImage1.png")) {
					if (gui->wireButton.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/wireButtonImage2.png")) {
						gui->wireButton.buttonPos.x = SCREEN_X - 3 * al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
						gui->wireButton.buttonPos.y = 1 * al_get_bitmap_height(gui->resistorButton.buttonImage);
						if (gui->gndButton.buttonImage = al_load_bitmap("Resources/Buttons/gndButtonImage1.png")) {
							if (gui->gndButton.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/gndButtonImage2.png")) {
								gui->gndButton.buttonPos.x = SCREEN_X - 3 * al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
								gui->gndButton.buttonPos.y = 2 * al_get_bitmap_height(gui->resistorButton.buttonImage);
								if (gui->vccButton.buttonImage = al_load_bitmap("Resources/Buttons/vccButtonImage1.png")) {
									if (gui->vccButton.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/vccButtonImage2.png")) {
										gui->vccButton.buttonPos.x = SCREEN_X - 3 * al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
										gui->vccButton.buttonPos.y = 3 * al_get_bitmap_height(gui->resistorButton.buttonImage);
										if (gui->resistorImage = al_load_bitmap("Resources/resistor.png")) {
											if (gui->gndImage = al_load_bitmap("Resources/Ground.png")) {
												if (gui->vccImage = al_load_bitmap("Resources/connector.png")) {
													gui->resistorAngle = 0;
													return TRUE;
												}
												else { printf("Unable to load connector Image\n"); }
											}
											else { printf("Unable to load gnd image\n"); }
										}
										else { printf("Unable to load resistor Image\n"); }
									}
									else { printf("Unable to load connect Image 2\n"); }
								}
								else { printf("Unable to load connector Image 1\n"); }
							}
							else { printf("unable to load gnd image 2\n"); }
						}
						else { printf("unable to load gnd image 1\n"); }
					}
					else { printf("Unable to load wire button Image 2\n"); }
				}
				else { printf("Unable to load wire button Image 1\n"); }
			}
			else { printf("Unable to load resistor button image 2\n"); }
		}
		else { printf("Unable to load resistor button image 1\n"); }
	}
	else { printf("Failed to initialize the Menu\n"); }

	return FALSE;
}
BOOL ProgramCore::initializeMenu(GUIElements* gui) {
	int i = 0;
	if (gui->menuButtons[0].buttonImage = al_load_bitmap("Resources/Desplegable/DeleteMenu.png")) {
		if (gui->menuButtons[0].mouseOverButtonImage = al_load_bitmap("Resources/Desplegable/mouseOverDeleteMenu.png")) {
			if (gui->menuButtons[1].buttonImage = al_load_bitmap("Resources/Desplegable/MoveMenu.png")) {
				if (gui->menuButtons[1].mouseOverButtonImage = al_load_bitmap("Resources/Desplegable/mouseOverMoveMenu.png")) {
					if (gui->menuButtons[2].buttonImage = al_load_bitmap("Resources/Desplegable/RotateMenu.png")) {
						if (gui->menuButtons[2].mouseOverButtonImage = al_load_bitmap("Resources/Desplegable/mouseOverRotateMenu.png")) {
							if (gui->menuButtons[3].buttonImage = al_load_bitmap("Resources/Desplegable/SetValueMenu.png")) {
								if (gui->menuButtons[3].mouseOverButtonImage = al_load_bitmap("Resources/Desplegable/mouseOverSetValueMenu.png")) {
									for (i = 0; i < MENUSIZE; i++) {
										gui->menuButtons[i].buttonPos.x = 0;
										gui->menuButtons[i].buttonPos.y = 0;
									}
									return TRUE;
								}
								else { printf("Failed to load mouseOverSetValueMenu.png\n"); }
							}
							else { printf("Failed to load SetValueMenu.png\n"); }
						}
						else { printf("Failed to load mouseOverRotateMenu.png\n"); }
					}
					else { printf("Failed to load RotateMenu.png\n"); }
				}
				else { printf("Failed to load mouseOverMoveMenu.png\n"); }
			}
			else { printf("Failed to load MoveMenu.png\n"); }
		}
		else { printf("Failed to load mouseOverDeleteMenu.png\n"); }
	}
	else { printf("Failed to load DeleteMenu.png\n"); }

	return FALSE;
}
//Update
void ProgramCore::updateScreen(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum) {
	int i = 0;
	al_set_target_backbuffer(allegro->display);
	al_clear_to_color(al_map_rgb(WHITE));
	//al_draw_bitmap(allegro->fondo, 0, 0, 0);
	updateResistors(gui);
	updateAllButtons(gui, mouse);
	updateModes(gui, mouse, modeEnum);
	
	al_flip_display();
}
void ProgramCore::updateAllButtons(GUIElements* gui, pos mouse) {
	updateButton(gui->resistorButton, mouse);
	updateButton(gui->wireButton, mouse);
	updateButton(gui->gndButton, mouse);
	updateButton(gui->vccButton, mouse);
}
void ProgramCore::updateButton(Button button, pos mouse) {
	if (checkButton(button, mouse)) {
		al_draw_bitmap(button.mouseOverButtonImage, button.buttonPos.x, button.buttonPos.y, 0);
	}
	else {
		al_draw_bitmap(button.buttonImage, button.buttonPos.x, button.buttonPos.y, 0);
	}
}
void ProgramCore::updateModes(GUIElements* gui, pos mouse, enum ModeEnum modeEnum) {
	int i = 0;
	if (modeEnum == RESISTORPLACE) { //Draw a resistor that follows the mouse
		if (gui->resistorAngle == 0) {
			al_draw_bitmap(gui->resistorImage, mouse.x, mouse.y - al_get_bitmap_height(gui->resistorImage) / 2, 0);
		}
		else {
			al_draw_rotated_bitmap(gui->resistorImage, al_get_bitmap_width(gui->resistorImage) / 2, al_get_bitmap_width(gui->resistorImage) / 2, mouse.x - al_get_bitmap_height(gui->resistorImage), mouse.y + al_get_bitmap_width(gui->resistorImage) / 2, gui->resistorAngle, 0);
		}
	}
	else if (modeEnum == GNDPLACE) {
		al_draw_bitmap(gui->gndImage, mouse.x - al_get_bitmap_width(gui->gndImage) / 2, mouse.y, 0);
	}
	else if (modeEnum == VCCPLACE) {
		al_draw_bitmap(gui->vccImage, mouse.x - al_get_bitmap_width(gui->vccImage) / 2, mouse.y - al_get_bitmap_height(gui->vccImage), 0);
	}
	else if (modeEnum == RIGHTCLICK) { //If I made right click I have to update the menu over the mouse
		for (i = 0; i < MENUSIZE; i++) {
			updateButton(gui->menuButtons[i], mouse);
		}
	}
}
void ProgramCore::updateResistors(GUIElements* gui) {
	if (!resistorArray.empty()) {
		for (int i = 0; i < resistorArray.size(); i++) {
			resistorArray[i].updateResistor(gui->resistorImage);
		}
	}
}
//Mouse Functions
BOOL ProgramCore::checkButton(Button button, pos mouse) {
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
BOOL ProgramCore::click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements) {
	if (elements->modeEnum == NORMAL) {
		if (checkButton(gui->resistorButton, mouse)) { elements->modeEnum = RESISTORPLACE;	}
		else if (checkButton(gui->wireButton, mouse)) { elements->modeEnum = WIREPLACE; }
		else if (checkButton(gui->gndButton, mouse)) { elements->modeEnum = GNDPLACE; }
		else if (checkButton(gui->vccButton, mouse)) { elements->modeEnum = VCCPLACE; }
	}
	else if (elements->modeEnum == RESISTORPLACE) {
		if (gui->resistorAngle == 0) {	resistorArray.push_back(Resistor(true, mouse.x, mouse.y)); 	}
		else { resistorArray.push_back(Resistor(false, mouse.x, mouse.y)); }
		elements->modeEnum = NORMAL;
	}
	else if (elements->modeEnum == WIREPLACE || elements->modeEnum == GNDPLACE || elements->modeEnum == VCCPLACE || elements->modeEnum == RIGHTCLICK) {
		elements->modeEnum = NORMAL;
	}
	return true;
}
void ProgramCore::rightClick(ProgramElements* elements, GUIElements* gui) {
	int i = 0;
	for (i = 0; i < MENUSIZE; i++) {
		gui->menuButtons[i].buttonPos.x = elements->mouse.x;
		gui->menuButtons[i].buttonPos.y = elements->mouse.y + i * al_get_bitmap_height(gui->menuButtons[i].buttonImage);
	}
	elements->modeEnum = RIGHTCLICK;
}

 