#include "Resistor.h"

Resistor::Resistor(bool vertical, int x, int y) {
	value = 1000;
	this->vertical = vertical;
	rPos.x = x;
	rPos.y = y;
}

void Resistor::moveResistor(int x, int y) {
	rPos.x = x;
	rPos.y = y;
}

bool Resistor::mouseOverRes(ALLEGRO_BITMAP* resistorImage, pos mouse) {
	return false;
}