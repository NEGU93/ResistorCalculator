#ifndef PROGCORE_H_INCLUDED
#define PROGCORE_H_INCLUDED	

#include "allegro.h"
#include "def.h"
#include "Resistor.h"
#include "Node.h"

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




class ProgramCore {
public:
	ProgramCore(GUIElements* gui);
	BOOL eventHandler(ALL* allegro, ProgramElements* elements, GUIElements* gui);
private:
	//Initializers
	BOOL initializeGUIElements(GUIElements* gui);
	BOOL initializeMenu(GUIElements* gui);
	//Update Functions
	void updateButton(Button button, pos mouse);
	void updateScreen(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void updateModes(GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void updateAllButtons(GUIElements* gui, pos mouse);
	void updateResistors(GUIElements* gui);
	//Mouse Buttons
	BOOL checkButton(Button button, pos mouse);
	BOOL click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements);
	void rightClick(ProgramElements* elements, GUIElements* gui);
	//Other Methods
	void wired(pos mouse, GUIElements* gui, ProgramElements* elements);
	// ------------ Variables -------------------
	vector<Resistor> resistorArray;
	UpperLowerEnum resStart;
	UpperLowerEnum resEnd;
	int selectedResIndex;
	Node vcc;
	Node gnd;
};

#endif