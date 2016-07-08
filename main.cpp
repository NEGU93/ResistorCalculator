#include "def.h"
#include "allegro.h"
#include "programCore.h"
#include "Resistor.h"

void main(void) {
	//Allegro initialization
	ALL allegroData = { 0, 0, NULL, NULL, NULL, NULL, };
	ALL* allegro = &allegroData;
	int i = init_allegro(allegro);
	//Program and Gui elements
	ProgramElements programElements = { {0, 0}, FALSE, TRUE, NORMAL };
	ProgramElements *elements = &programElements;
	GUIElements guiElements;
	GUIElements* gui = &guiElements;
	//Initialize program Core
	ProgramCore *programCore = NULL;
	if (programCore != NULL) { delete programCore; }
	programCore = new ProgramCore(gui);
	//Principal loop
	while (programElements.stillRunning == TRUE) {
		programElements.stillRunning = programCore->eventHandler(allegro, elements, gui);
	}
	//End Program
	al_destroy_display(allegro->display);
	destroyAll(allegro);

	getchar();
}