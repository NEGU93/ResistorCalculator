#ifndef RESISTOR_H_INCLUDED
#define RESISTOR_H_INCLUDED

#include "def.h"
#include "allegro.h"
//#include "programCore.h"



class Resistor {
public:
	Resistor(bool Vertical, int x, int y);
	//TODO: ~Resistor();
	void updateResistor(ALLEGRO_BITMAP* resistorImage, vector<Resistor> &resistorArray);
	UpperLowerEnum mouseOverRes(ALLEGRO_BITMAP* resistorImage, pos mouse);
	//Seters
	void setValue(double value) { this->value = value; }
	void moveResistor(int x, int y);
	void rotate() { horizontal = !horizontal; }
		//Pointers
	void setFather(int index) { ptr2father = index; }
	void setSon(int index) { ptr2son = index; }
	void setStepBro(int index) { ptr2stepBro = index; }
	void setBrother(int index) { ptr2brother = index; }
	void deleteFather() { setFather(-1); }
	void deleteSon() { setSon(-1); }
	void deleteBrother() { setBrother(-1); }
	void deleteStepBro() { setStepBro(-1); }
	//Getters
	double getValue() { return value; }
	pos getCoords() { return rPos; }
	int getFather() { return ptr2father; }
	bool getHoriz() { return horizontal; }
private:
	double value;
	pos rPos;
	bool horizontal;
	//Pointers
	int ptr2father;
	int ptr2brother;
	int ptr2son;
	int ptr2stepBro;
};

#endif