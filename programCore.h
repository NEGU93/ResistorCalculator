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
	int redraw;					// It tells the event handler if it is time to redraw the screen or not.
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

void destroyButton(Button* button);
void destroyGuiElements(GUIElements* guiElements);

class ProgramCore {
public:
	ProgramCore(GUIElements* gui);
	~ProgramCore();
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
	void makeGrid();
	// Mouse Buttons
	BOOL checkButton(Button button, pos mouse);
	BOOL click(ALL* allegro, pos mouse, GUIElements* gui, ProgramElements* elements);
	void rightClick(ProgramElements* elements, GUIElements* gui);
	// Main Calculation
	double calculus(int index, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	void deleteEvidence(int survivor, int toDelete);
	void takeCareOfHim(int survivor, int toDelete, ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	double parallel(double res1, double res2);
	double serie(double res1, double res2);
	bool readyForParallel(int res1, int res2);
	bool startCalculation(ALL* allegro, GUIElements* gui, pos mouse, enum ModeEnum modeEnum);
	// Resistor Manipulation
	void wired(pos mouse, GUIElements* gui, ProgramElements* elements);
	void nodeWire(pos mouse, ModeEnum &modeEnum);
	void resistorWire(pos mouse, GUIElements* gui);
	void setFatherSon(vector<Resistor> &resistorArray, int father, int son);
	void setStepBros(vector<Resistor> &resistorArray, int bro1, int bro2);
	void setBros(vector<Resistor> &resistorArray, int bro1, int bro2);
	bool checkForRealFather(vector<Resistor> &resistorArray, int index);
	//Deletion Process
	void deleteResistor(int indexToDelete);
	void reorder(int indexToDelete);
	void deletePointersOfandFrom(int indexToDelete);
	void deleteStepBro(int index);
	
	// ------------ Variables -------------------
	vector<Resistor> resistorArray;
	Node vcc;
	Node gnd;
	int selectedResIndex;
	bool grid;
	bool stepMode;
	bool diagonally;
	pos backupPos;
	UpperLowerEnum resStart;
};

#endif