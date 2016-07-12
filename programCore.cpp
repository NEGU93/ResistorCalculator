//#include <math.h>
#include "programCore.h"
#include "setValue.h"
#include <stdlib.h>
#define TIMEPAUSE 1000
#define PI 3.14159265358979323846

ProgramCore::ProgramCore(GUIElements* gui) {
	if (!initializeGUIElements(gui)) {
		printf("Error initializing guiElements\n");
	}
	resStart = NOTOVER;
	selectedResIndex = -1;
	vcc = Node(gui->vccImage, true);
	gnd = Node(gui->gndImage, false);
	backupPos.x = 0;
	backupPos.y = 0;
	grid = true;
	stepMode = true;
	diagonally = false;
}
ProgramCore::~ProgramCore() {
	resistorArray.clear();
}

//Destroyers
void destroyButton(Button* button) {
	al_destroy_bitmap(button->buttonImage);
	al_destroy_bitmap(button->mouseOverButtonImage);
}
void destroyGuiElments(GUIElements* guiElements) {
	// Destroy Buttons
	destroyButton(&(guiElements->resistorButton));
	destroyButton(&(guiElements->wireButton));
	destroyButton(&(guiElements->gndButton));
	destroyButton(&(guiElements->vccButton));
	destroyButton(&(guiElements->runCalcul));
	for (int i = 0; i < MENUSIZE; i++) { destroyButton(&(guiElements->menuButtons[i])); }
	// Destroy Images
	al_destroy_bitmap(guiElements->resistorImage);
	al_destroy_bitmap(guiElements->gndImage);
	al_destroy_bitmap(guiElements->vccImage);
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
		if (elements->modeEnum == MOVEMODE) {
			resistorArray[selectedResIndex].moveResistor(elements->mouse.x, elements->mouse.y, stepMode);
		}
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
			break;
		case ALLEGRO_KEY_TAB:
			stepMode = !stepMode;
			break;
		case ALLEGRO_KEY_G:
			grid = !grid;
			break;
		case ALLEGRO_KEY_ESCAPE:
			selectedResIndex = -1;
			resStart = NOTOVER;
			elements->modeEnum = NORMAL;
			break;
		case ALLEGRO_KEY_L:
			diagonally = !diagonally;
			break;
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
													if (gui->runCalcul.buttonImage = al_load_bitmap("Resources/Buttons/runButtonImage1.png")) {
														if (gui->runCalcul.mouseOverButtonImage = al_load_bitmap("Resources/Buttons/runButtonImage2.png")) {
															gui->runCalcul.buttonPos.x = SCREEN_X - al_get_bitmap_width(gui->runCalcul.buttonImage) - al_get_bitmap_width(gui->resistorButton.buttonImage) / 2;
															gui->runCalcul.buttonPos.y = SCREEN_Y - 2 * al_get_bitmap_height(gui->runCalcul.buttonImage);
															gui->resistorAngle = 0;
															return TRUE;
														}
													}
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
	if (grid) { makeGrid(); }
	al_draw_bitmap(allegro->downBar, 0, SCREEN_Y - al_get_bitmap_height(allegro->downBar), 0);
	//al_draw_bitmap(allegro->fondo, 0, 0, 0);
	updateResistors(gui, allegro->font);
	updateAllButtons(gui, mouse);
	updateModes(gui, mouse, modeEnum);
	al_draw_textf(allegro->font, al_map_rgb(BLACK), SCREEN_X - 20, allegro->screenHeight - 20, ALLEGRO_ALIGN_RIGHT, "X:%d; Y:%d", mouse.x, mouse.y);
	updateTextMode(allegro->font, 20, allegro->screenHeight - 20, modeEnum);
	al_flip_display();
}
void ProgramCore::updateAllButtons(GUIElements* gui, pos mouse) {
	updateButton(gui->resistorButton, mouse);
	updateButton(gui->wireButton, mouse);
	updateButton(gui->gndButton, mouse);
	updateButton(gui->vccButton, mouse);
	if (updateCalculButton()) { updateButton(gui->runCalcul, mouse); }
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
	else if (modeEnum == WIREPLACE) {
		al_draw_line(mouse.x - DELTA, mouse.y, mouse.x + DELTA, mouse.y, al_map_rgb(BLACK), 1);
		al_draw_line(mouse.x , mouse.y - DELTA, mouse.x, mouse.y + DELTA, al_map_rgb(BLACK), 1);
		if (selectedResIndex != -1) {
			pos resTime = resistorArray[selectedResIndex].getCoords();
			if (resStart == UPPERPART) { draw_line(mouse.x, mouse.y, resTime.x, resTime.y, al_map_rgb(LINECOLOUR), LINEWIDTH, diagonally); }
			else if (resStart == LOWERPART) {
				if (resistorArray[selectedResIndex].getHoriz()) { draw_line(mouse.x, mouse.y, resTime.x + al_get_bitmap_width(gui->resistorImage), resTime.y, al_map_rgb(LINECOLOUR), LINEWIDTH, diagonally); }
				else { draw_line(mouse.x, mouse.y, resTime.x, resTime.y + al_get_bitmap_width(gui->resistorImage), al_map_rgb(LINECOLOUR), LINEWIDTH, diagonally); }
			}
		}
		else if (resStart == NODEVCC) {
			draw_line(vcc.getCorrds().x + al_get_bitmap_width(gui->vccImage) / 2, vcc.getCorrds().y + al_get_bitmap_height(gui->vccImage), mouse.x, mouse.y, al_map_rgb(LINECOLOUR), LINEWIDTH, diagonally);
		}
		else if (resStart == NODEGND) {
			draw_line(gnd.getCorrds().x + al_get_bitmap_width(gui->gndImage) / 2, gnd.getCorrds().y, mouse.x, mouse.y, al_map_rgb(LINECOLOUR), LINEWIDTH, diagonally);
		}
	}
}
void ProgramCore::updateResistors(GUIElements* gui, ALLEGRO_FONT *font) {
	if (!resistorArray.empty()) {
		for (int i = 0; i < resistorArray.size(); i++) {
			resistorArray[i].updateResistor(gui->resistorImage, resistorArray, font, diagonally);
		}
	}
	//UpdateNodes
	vcc.updateNode(resistorArray, gui->resistorImage, diagonally);
	gnd.updateNode(resistorArray, gui->resistorImage, diagonally);
}
void ProgramCore::updateTextMode(ALLEGRO_FONT *font, int x, int y, enum ModeEnum modeEnum) {
	switch (modeEnum) {
	case NORMAL:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Resistor Calculator Beta 1.0");
		break;
	case MOVEMODE:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Move your Resistor");
		break;
	case RIGHTCLICK:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Select Option");
		break;
	case RESISTORPLACE:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Place Resistor");
		break;
	case WIREPLACE:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Wire Mode");
		break;
	case GNDPLACE:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Place GND");
		break;
	case VCCPLACE:
		al_draw_text(font, al_map_rgb(BLACK), x, y, ALLEGRO_ALIGN_LEFT, "Place VCC");
		break;
	}
}
bool ProgramCore::updateCalculButton() {
	int index = gnd.getIndex();
	bool ready = false;
	if (index != -1) {
		while (resistorArray[index].getFather() != -1) {
			index = resistorArray[index].getFather();
		}
		if (vcc.getIndex() == index) { ready = true; }
	}
	if (ready) {
		for (int i = 0; i < resistorArray.size(); i++) {
			if (resistorArray[i].getSon() == -1 && i != gnd.getIndex()) {
				if (resistorArray[i].getStepBro() == -1 || resistorArray[i].getFather() == -1) {
					if (vcc.getIndex() != i) {
						ready = false;
						return ready; //No need to keep looking, I know the result.
					}
				}
			}
		}
	}
	return ready;
}
void ProgramCore::makeGrid() {
	for (int i = 1; i < SCREEN_X / MULTIPLE; i++) {
		al_draw_line(i * MULTIPLE, 0, i * MULTIPLE, SCREEN_Y, al_map_rgb(GRAY), 1);
	}
	for (int j = 1; j < SCREEN_Y / MULTIPLE; j++) {
		al_draw_line(0, j * MULTIPLE, SCREEN_X, j * MULTIPLE, al_map_rgb(GRAY), 1);
	}
}
// Mouse Functions
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
		if (updateCalculButton() && checkButton(gui->runCalcul, mouse)) { startCalculation(allegro, gui, mouse, elements->modeEnum); }
	}
	else if (elements->modeEnum == RESISTORPLACE) {
		Resistor res = Resistor(false, mouse.x, mouse.y, stepMode);
		if (gui->resistorAngle == 0) { res.rotate(); }
		resistorArray.push_back(res);
		//elements->modeEnum = NORMAL;
	}
	else if (elements->modeEnum == WIREPLACE) {
		wired(mouse, gui, elements);
	}
	else if (elements->modeEnum == VCCPLACE) { 
		vcc.setCoords(mouse.x - al_get_bitmap_width(gui->vccImage) / 2, mouse.y - al_get_bitmap_height(gui->vccImage));
		vcc.setIndex(-1);
		elements->modeEnum = NORMAL;
	}
	else if (elements->modeEnum == GNDPLACE) { 
		gnd.setCoords(mouse.x - al_get_bitmap_width(gui->gndImage) / 2, mouse.y); 
		gnd.setIndex(-1);
		elements->modeEnum = NORMAL;
	}
	else if (elements->modeEnum == RIGHTCLICK) {
		elements->modeEnum = NORMAL;
		int i = 0;
		for (i = 0; i < MENUSIZE; i++) {
			if (checkButton(gui->menuButtons[i], mouse)) {
				switch (i) {
				case 0:	//Delete
					deleteResistor(selectedResIndex);
					selectedResIndex = -1;
					break;
				case 1:	//Move
					elements->modeEnum = MOVEMODE;
					backupPos = resistorArray[selectedResIndex].getCoords();
					break;
				case 2: //Rotate
					resistorArray[selectedResIndex].rotate();
					selectedResIndex = -1;
					break;
				case 3:	//Set Value
					updateScreen(allegro, gui, mouse, elements->modeEnum);
					resistorArray[selectedResIndex].setValue(setValue(allegro->font));
					break;
				}
			}
		}
		//elements->modeEnum = NORMAL;
	}
	else if (elements->modeEnum == MOVEMODE) {
		resistorArray[selectedResIndex].moveResistor(mouse.x, mouse.y, stepMode);
		elements->modeEnum = NORMAL;
		selectedResIndex = -1;
	}
	return true;
}
void ProgramCore::rightClick(ProgramElements* elements, GUIElements* gui) {
	if (elements->modeEnum == NORMAL) {
		for (int j = 0; j < resistorArray.size(); j++) {
			if (resistorArray[j].mouseOverRes(gui->resistorImage, elements->mouse) != NOTOVER) {
				selectedResIndex = j;
				int i = 0;
				for (i = 0; i < MENUSIZE; i++) {
					gui->menuButtons[i].buttonPos.x = elements->mouse.x;
					gui->menuButtons[i].buttonPos.y = elements->mouse.y + i * al_get_bitmap_height(gui->menuButtons[i].buttonImage);
				}
				elements->modeEnum = RIGHTCLICK;
			}
		}
	}
	else if (elements->modeEnum == RESISTORPLACE) {
		selectedResIndex = -1;
		resStart = NOTOVER;
		elements->modeEnum = NORMAL;
	}
	else if (elements->modeEnum == MOVEMODE) {
		resistorArray[selectedResIndex].moveResistor(backupPos.x, backupPos.y, stepMode);
		backupPos.x = 0;
		backupPos.y = 0;
		selectedResIndex = -1;
		elements->modeEnum = NORMAL;
	}
	else { 
		selectedResIndex = -1;
		resStart = NOTOVER;
		elements->modeEnum = NORMAL; 
	}
} 

// Wiring Part
void ProgramCore::wired(pos mouse, GUIElements* gui, ProgramElements* elements) {
	// This function is used wile conecting resistors with each other.
	resistorWire(mouse, gui);
	nodeWire(mouse, elements->modeEnum);
}
void ProgramCore::nodeWire(pos mouse, ModeEnum &modeEnum) {
	if (vcc.wireNode(mouse, selectedResIndex, resStart)) { modeEnum = NORMAL; }
	if (gnd.wireNode(mouse, selectedResIndex, resStart)) { modeEnum = NORMAL; }
}
void ProgramCore::resistorWire(pos mouse, GUIElements* gui) {
	for (int i = 0; i < resistorArray.size(); i++) {
		UpperLowerEnum upperLowerEnum = resistorArray[i].mouseOverRes(gui->resistorImage, mouse); // Save the place of the resistor
		if (upperLowerEnum != NOTOVER) {	//If it was over something lets start... (this can't be NODEVCC or NODEGND)
			if (resStart == NOTOVER) { //If it's the firs of the 2 resistors save it.
				resStart = upperLowerEnum;
				selectedResIndex = i;
			}
			else {
				/* *****************************************************************************************
				*	Options:
				*		ResStart:
				*			1. NODEVCC: Do nothing to the new one, just set the new index to vcc
				*			2. NODEGND: Idem vcc but with gnd.
				*			3. LOWERPART:
				*				3.1: UPPERPART:	Set father / Son
				*				3.2: LOWERPART: Set Step Bros
				*			4. UPPERPART:
				*				4.1: UPPERPART:	SET BROTHERS
				*				4.2: LOWERPART: Set father / Son backward
				****************************************************************************************** */  
				if (resStart == NODEVCC) { vcc.setIndex(i); }
				else if (resStart == NODEGND) { gnd.setIndex(i); }
				else if (resStart == LOWERPART) {
					if (upperLowerEnum == UPPERPART) { setFatherSon(resistorArray, selectedResIndex, i); }
					else if (upperLowerEnum == LOWERPART) { setStepBros(resistorArray, selectedResIndex, i); }
					else { cout << "Should never reach here" << endl; }
				}
				else if (resStart == UPPERPART) {
					if (upperLowerEnum == LOWERPART) { setFatherSon(resistorArray, i, selectedResIndex); }
					else if (upperLowerEnum == UPPERPART) { setBros(resistorArray, selectedResIndex, i); }
					else { cout << "Should never reach here" << endl; }
				}
				else { cout << "Error, resStart wasn't Lower nor Upper" << endl; } //Normally it should never get here.
				if (vcc.getIndex() != -1) { if (resistorArray[vcc.getIndex()].getFather() != -1) { vcc.setIndex(-1); } }
				if (gnd.getIndex() != -1) { if (resistorArray[gnd.getIndex()].getSon() != -1) { gnd.setIndex(-1); } }
				//End of wiring
				resStart = NOTOVER;
				selectedResIndex = -1;
				//elements->modeEnum = NORMAL;
			}
		}
	}
}
void ProgramCore::setFatherSon(vector<Resistor> &resistorArray, int father, int son) {
	if (resistorArray[son].getFather() != -1) { //It it has a father already, leave it.
		int last = resistorArray[son].getFather();
		if (resistorArray[last].getSon() == son) { resistorArray[last].deleteSon(); }
		else if (resistorArray[last].getBrother() == son) { resistorArray[last].deleteBrother(); }
	}
	if (resistorArray[father].getSon() != -1) {	resistorArray[resistorArray[father].getSon()].setFather(-1); } //If the father had a son leave it.
	// Now the real stuf.
	resistorArray[father].setSon(son);
	resistorArray[son].setFather(father);
}
void ProgramCore::setStepBros(vector<Resistor> &resistorArray, int bro1, int bro2) {
	int save = bro1;
	int iter = save;
	if (resistorArray[iter].getStepBro() != -1) {
		while (resistorArray[iter].getStepBro() != save) {
			if (resistorArray[iter].getStepBro() == bro2) { return; }
			else { iter = resistorArray[iter].getStepBro(); }
		}
	}
	//if (resistorArray[bro1].getStepBro() == bro2) { return; }
	// This make a circle of stepbros, Infinite loop
	int tempBro1 = resistorArray[bro1].getStepBro();
	int tempBro2 = resistorArray[bro2].getStepBro();
	if (tempBro1 == -1) { resistorArray[bro2].setStepBro(bro1); }
	else { resistorArray[bro2].setStepBro(tempBro1); }
	if (tempBro2 == -1) { resistorArray[bro1].setStepBro(bro2); }
	else { resistorArray[bro1].setStepBro(tempBro2); }
}
void ProgramCore::setBros(vector<Resistor> &resistorArray, int bro1, int bro2) {
	//If both brothers have a father then error
	if (checkForRealFather(resistorArray, bro1) && checkForRealFather(resistorArray, bro2)) {
		cout << "Invalid wiring, at least one brother must have no father" << endl;
		return;
	}
	//Gives prority to bro1 normally bro1 will be father.
	else if (checkForRealFather(resistorArray, bro1)) { //If it has a father then this will have brother and the other the father
		while (resistorArray[bro1].getBrother() != -1) { 
			bro1 = resistorArray[bro1].getBrother(); 
			// For the way setBros work, this shouold never be true. But just in case...
			if (checkForRealFather(resistorArray, bro1)) { cout << "Invalid wiring, the program will explode once hit on calcule" << endl; return; }
		}	//Makes sure it has no brother
		resistorArray[bro2].setFather(bro1);
		resistorArray[bro1].setBrother(bro2);
	}
	else if (checkForRealFather(resistorArray, bro2)) { //If it has a father then this will have brother and the other the father
		while (resistorArray[bro2].getBrother() != -1) { 
			bro2 = resistorArray[bro2].getBrother(); 
			// For the way setBros work, this shouold never be true. But just in case...
			if (checkForRealFather(resistorArray, bro2)) { cout << "Invalid wiring, the program will explode once hit on calcule" << endl; return; }
		}
		resistorArray[bro2].setBrother(bro1);
		resistorArray[bro1].setFather(bro2);
	}
	// If both have no father
	else {
		while (resistorArray[bro1].getBrother() != -1) { bro1 = resistorArray[bro1].getBrother(); }	//Makes sure it has no brother
		if (bro1 != bro2) {
			resistorArray[bro1].setBrother(bro2);
			resistorArray[bro2].setFather(bro1);
		}
	}

}
bool ProgramCore::checkForRealFather(vector<Resistor> &resistorArray, int index) {
	//As father can be both father or brother, this returns true if the father was a father
	if (resistorArray[index].getFather() == -1) { return false; } //This is preventive coding, It should be outside
	if (resistorArray[resistorArray[index].getFather()].getSon() == index) { return true; }
	else { return false; }
}

// Deletion Process
void ProgramCore::deleteResistor(int indexToDelete) {
	deletePointersOfandFrom(indexToDelete);
	reorder(indexToDelete);
	resistorArray.erase(resistorArray.begin() + indexToDelete);
}
void ProgramCore::reorder(int indexToDelete) {
	/* Reorder Its previous the deletion of a resistor. 
	If I delete a resistor the vector will now have a size lower, so all pointers of index higher than the index deleted will have to be reduced in one.
	This function takes care of that.
	It changes all the pointers of other resistors in order to face the deletion of a resistor in vector and have no problem.
	*/
	if (gnd.getIndex() > indexToDelete) { gnd.decreseIndex(); }
	if (vcc.getIndex() > indexToDelete) { vcc.decreseIndex(); }
	for (int i = 0; i < resistorArray.size(); i++) {
		if (resistorArray[i].getBrother() > indexToDelete) { resistorArray[i].decreseBrother(); }
		if (resistorArray[i].getFather() > indexToDelete) { resistorArray[i].decreseFather(); }
		if (resistorArray[i].getSon() > indexToDelete) { resistorArray[i].decreseSon(); }
		if (resistorArray[i].getStepBro() > indexToDelete) { resistorArray[i].decreseStepBro(); }
	}
}
void ProgramCore::deletePointersOfandFrom(int indexToDelete) {
	/* This function receives the index of the resistor to delete and eliminates all pointers to that resistor and from that resistor to have no problems. */
	Resistor resistorToDelete = resistorArray[indexToDelete];
	if (resistorToDelete.getFather() != -1) { //IT has a father?
		if (resistorArray[resistorToDelete.getFather()].getSon() == indexToDelete) {	//It's his son?
			resistorArray[resistorToDelete.getFather()].deleteSon();
		}
		else if (resistorArray[resistorToDelete.getFather()].getBrother() == indexToDelete) {	//Or it's his brother?
			resistorArray[resistorToDelete.getFather()].deleteBrother();
		}
		else {	//It must be father or son... So this option should never run.
			cout << "Error, unrecognized child or brother" << endl; //It should never get here
		}
	}
	if (resistorToDelete.getSon() != -1) { //Take care of your son
		resistorArray[resistorToDelete.getSon()].deleteFather();
	}
	if (resistorToDelete.getBrother() != -1) { //Take care of your brother
		resistorArray[resistorToDelete.getBrother()].deleteFather();
	}
	deleteStepBro(indexToDelete);
	if (gnd.getIndex() == indexToDelete) { gnd.setIndex(-1); } //Does GND or VCC target the resistor?
	if (vcc.getIndex() == indexToDelete) { vcc.setIndex(-1); }
}
void ProgramCore::deleteStepBro(int index) {
	if (resistorArray[index].getStepBro() == -1) { return; }
	int byPass1 = resistorArray[index].getStepBro();	//A quien apunte index
	int byPass2 = index;	//Quien lo apunta a index
	while (resistorArray[byPass2].getStepBro() != index ) {
		byPass2 = resistorArray[byPass2].getStepBro();
	}
	if (byPass1 == byPass2) {
		resistorArray[byPass2].setStepBro(-1);
		return;
	}
	resistorArray[byPass2].setStepBro(byPass1);
	resistorArray[index].setStepBro(-1);
}

// Calculus Functions
double ProgramCore::calculus(int index, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum) {
	if (resistorArray[index].getStepBro() != -1) {		//Has a stepBro
		if (resistorArray[index].getBrother() != -1 && readyForParallel(resistorArray[index].getBrother(), index)) {
			double brotherValue = calculus(resistorArray[index].getBrother(), allegro, gui, mouse, modeEnum); //Here I have faith that the return will have the same stepbro that bro
			//Parallel Simple
			resistorArray[index].setValue(parallel(resistorArray[index].getValue(), brotherValue));
			takeCareOfHim(index, resistorArray[index].getBrother(), allegro, gui, mouse, modeEnum);
		}
		else if (resistorArray[index].getBrother() == -1) { 
			return resistorArray[index].getValue(); 
		}
		else {
			double brotherValue = calculus(resistorArray[index].getBrother(), allegro, gui, mouse, modeEnum); //Here I have faith that the return will have the same stepbro that bro
			//Parallel Simple
			resistorArray[index].setValue(parallel(resistorArray[index].getValue(), brotherValue));
			takeCareOfHim(index, resistorArray[index].getBrother(), allegro, gui, mouse, modeEnum);
		}
	}
	else if (resistorArray[index].getBrother() != -1) {
		double sonValue = calculus(resistorArray[index].getSon(), allegro, gui, mouse, modeEnum);
		resistorArray[index].setValue(serie(resistorArray[index].getValue(), sonValue));
		takeCareOfHim(index, resistorArray[index].getSon(), allegro, gui, mouse, modeEnum);
		calculus(index, allegro, gui, mouse, modeEnum);
		//double brotherValue = calculus(resistorArray[index].getBrother(), allegro, gui, mouse, modeEnum); 
		////Here I have faith that the return will have the same stepbro that bro
		////Parallel Simple
		//resistorArray[index].setValue(parallel(resistorArray[index].getValue(), brotherValue));
		//takeCareOfHim(index, resistorArray[index].getBrother(), allegro, gui, mouse, modeEnum);
	}
	if (resistorArray[index].getSon() != -1) {
		double sonValue = calculus(resistorArray[index].getSon(), allegro, gui, mouse, modeEnum);
		// Now Series
		resistorArray[index].setValue(serie(resistorArray[index].getValue(), sonValue));
		takeCareOfHim(index, resistorArray[index].getSon(), allegro, gui, mouse, modeEnum);
	}
	return resistorArray[index].getValue();
}
void ProgramCore::deleteEvidence(int survivor, int toDelete) {
	//GND
	if (gnd.getIndex() == toDelete) { gnd.setIndex(survivor); }
	//Pass Brother
	if (resistorArray[toDelete].getBrother() != -1) {
		resistorArray[survivor].setBrother(resistorArray[toDelete].getBrother());	//Pass Brother
		resistorArray[resistorArray[survivor].getBrother()].setFather(survivor);	//Tell the brother who his new father is.
		resistorArray[toDelete].setBrother(-1);
	}

	//Pass StepBro

	if (resistorArray[toDelete].getStepBro() != -1) {
		setStepBros(resistorArray, survivor, toDelete);
		//deleteStepBro(toDelete);
	}
	//Pass Son
	if (resistorArray[toDelete].getSon() != -1) { 
		resistorArray[survivor].setSon(resistorArray[toDelete].getSon());
		resistorArray[resistorArray[survivor].getSon()].setFather(survivor);
		resistorArray[toDelete].setSon(-1);
	}
}
void ProgramCore::takeCareOfHim(int survivor, int toDelete, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum) {
	deleteEvidence(survivor, toDelete);
	deleteResistor(toDelete);
	updateScreen(allegro, gui, mouse, modeEnum);
	Sleep(TIMEPAUSE);
}
double ProgramCore::parallel(double res1, double res2) {
	return (res1 * res2) / serie(res1, res2);
}
double ProgramCore::serie(double res1, double res2) {
	return res1 + res2;
}
bool ProgramCore::startCalculation(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum) {
	double ans = calculus(vcc.getIndex(), allegro, gui, mouse, modeEnum); //If I got here I already checked vcc points the correct one and that I have a limit.
	resistorArray[vcc.getIndex()].setFather(-1);
	resistorArray[vcc.getIndex()].setSon(-1);
	resistorArray[vcc.getIndex()].setBrother(-1);
	resistorArray[vcc.getIndex()].setStepBro(-1);
	return true;
}
bool ProgramCore::readyForParallel(int res1, int res2) {
	int equalTo = resistorArray[res1].getBrother();
	if (equalTo == -1) { equalTo = resistorArray[res2].getBrother(); }
	if (equalTo == -1) { cout << "Not even a brother to make the loop" << endl; return false; }
	int i = resistorArray[equalTo].getFather();
	int compare = i;
	i = resistorArray[compare].getStepBro();
	while (i != compare) {
		if (i == equalTo) { return true; }
		i = resistorArray[i].getStepBro();
	}
	return false;
}