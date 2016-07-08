#include "def.h"
#include "allegro.h"
#include "programCore.h"

void main(void) {
	//Allegro initialization
	ALL allegroData = { 0, 0, NULL, NULL, NULL, NULL, };
	ALL* allegro = &allegroData;
	int i = init_allegro(allegro);

	//I don't know why it doesn't work
	/*if (i == 0) {
		//printf( "Failed to initialize allegro. Closing Program.\n" );
	}*/

	ProgramElements programElements = { {0, 0}, FALSE, TRUE, NORMAL };
	ProgramElements *elements = &programElements;
	GUIElements guiElements;
	GUIElements* gui = &guiElements;
	if (!initializeGUIElements(gui)) {
		printf("Error initializing guiElements\n");
		elements->stillRunning = FALSE;
	}

	while (programElements.stillRunning == TRUE) {
		programElements.stillRunning = eventHandler(allegro, elements, gui);
	}

	al_destroy_display(allegro->display);
	destroyAll(allegro);

	getchar();
}