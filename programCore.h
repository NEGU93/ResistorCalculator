#ifndef PROGCORE_H_INCLUDED
#define PROGCORE_H_INCLUDED	

#include "allegro.h"
#include "def.h"

#define MENUSIZE 4

enum ModeEnum { NORMAL, DELETEMODE, RIGHTCLICK,
	RESISTORPLACE, WIREPLACE, GNDPLACE, VCCPLACE 
};

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
	Button gndButton;
	Button vccButton;
	//Images
	ALLEGRO_BITMAP* resistorImage;
	float resistorAngle;
	ALLEGRO_BITMAP* gndImage;
	ALLEGRO_BITMAP* vccImage;
	//Menu
	Button menuButtons[MENUSIZE];
} GUIElements;

BOOL initializeGUIElements(GUIElements* gui);
BOOL initializeMenu(GUIElements* gui);
BOOL eventHandler(ALL* allegro, ProgramElements* elements, GUIElements* gui);
//Update Functions
void updateButton(Button button, pos mouse);
void updateScreen(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
void updateModes(GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
void updateAllButtons(GUIElements* gui, pos mouse);
//Mouse Buttons
BOOL checkButton(Button button, pos mouse);
BOOL click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements);
void rightClick(ProgramElements* elements, GUIElements* gui);

#endif