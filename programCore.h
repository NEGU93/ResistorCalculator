#ifndef PROGCORE_H_INCLUDED
#define PROGCORE_H_INCLUDED	

#include "allegro.h"
#include "def.h"
#include "Resistor.h"
#include "Node.h"

#define MENUSIZE 4

enum ModeEnum { NORMAL, MOVEMODE, RIGHTCLICK,
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
	Button runCalcul;
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
	// Initializers
	BOOL initializeGUIElements(GUIElements* gui);
	BOOL initializeMenu(GUIElements* gui);
	// Update Functions
	void updateButton(Button button, pos mouse);
	void updateScreen(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void updateModes(GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void updateAllButtons(GUIElements* gui, pos mouse);
	void updateResistors(GUIElements* gui, ALLEGRO_FONT *font);
	void updateTextMode(ALLEGRO_FONT *font, int x, int y, enum ModeEnum modeEnum);
	bool updateCalculButton();
	// Mouse Buttons
	BOOL checkButton(Button button, pos mouse);
	BOOL click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements);
	void rightClick(ProgramElements* elements, GUIElements* gui);
	// Main Calculation
	bool startCalculation(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	double calculate(int index, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void getSeries(int index, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void getParallel(int index, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	// Resistor Manipulation
	void wired(pos mouse, GUIElements* gui, ProgramElements* elements);
	//Deletion Process
	void deleteResistor(int indexToDelete);
	void reorder(int indexToDelete);
	void deletePointersOfandFrom(int indexToDelete);
	
	// ------------ Variables -------------------
	vector<Resistor> resistorArray;
	Node vcc;
	Node gnd;
	int selectedResIndex;
	bool grid;
	pos backupPos;
	UpperLowerEnum resStart;
};

#endif