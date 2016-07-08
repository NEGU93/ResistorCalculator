#include "Resistor.h"
#define PI 3.14159265358979323846

Resistor::Resistor(bool vertical, int x, int y) {
	value = 1000;
	this->vertical = vertical;
	rPos.x = x;
	rPos.y = y;
}
void Resistor::updateResistor(ALLEGRO_BITMAP* resistorImage) {
	if (vertical) {
		al_draw_bitmap(resistorImage, rPos.x, rPos.y - al_get_bitmap_height(resistorImage) / 2, 0);
	}
	else {
		al_draw_rotated_bitmap(resistorImage, al_get_bitmap_width(resistorImage) / 2, al_get_bitmap_width(resistorImage) / 2, rPos.x - al_get_bitmap_height(resistorImage), rPos.y + al_get_bitmap_width(resistorImage) / 2, PI / 2, 0);
	}
}
void Resistor::moveResistor(int x, int y) {
	rPos.x = x;
	rPos.y = y;
}

bool Resistor::mouseOverRes(ALLEGRO_BITMAP* resistorImage, pos mouse) {
	return false;
}