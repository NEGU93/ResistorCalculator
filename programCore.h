#ifndef PROGCORE_H_INCLUDED
#define PROGCORE_H_INCLUDED	

#include "allegro.h"
#include "def.h"

enum ModeEnum { NORMAL, RESISTORPLACE, DELETEMODE, WIRE };

typedef struct {
	pos mouse;
	int redraw;
	int stillRunning;
	enum ModeEnum modeEnum;
} ProgramElements;

typedef struct {
	ALLEGRO_BITMAP* buttonImage;
	ALLEGRO_BITMAP* mouseOverButtonImage;
	pos buttonPos;
} Button;

typedef struct {
	//BUTTONS
	Button resistorButton;
	Button wireButton;
	//Images
	ALLEGRO_BITMAP* resistor;
	float resistorAngle;
} GUIElements;

BOOL initializeGUIElements(GUIElements* gui);
BOOL eventHandler(ALL* allegro, ProgramElements* elements, GUIElements* gui);
//Update Functions
void updateButton(Button button, pos mouse);
void updateScreen(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
//Mouse Buttons
BOOL checkButton(Button button, pos mouse);
BOOL click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements);

#endif