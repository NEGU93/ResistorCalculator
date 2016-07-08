#ifndef RESISTOR_H_INCLUDED
#define RESISTOR_H_INCLUDED

#include "def.h"
#include "allegro.h"

class Resistor {
public:
	Resistor(bool Vertical, int x, int y);
	//TODO: ~Resistor();

	bool mouseOverRes(ALLEGRO_BITMAP* resistorImage, pos mouse);
	//Seters
	void setValue(double value) { this->value = value; }
	void moveResistor(int x, int y);
	//Getters
	double getValue() { return value; }
private:
	double value;
	pos rPos;
	bool vertical;
};

#endif