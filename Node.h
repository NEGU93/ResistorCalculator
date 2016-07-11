#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED	

#include "def.h"
#include "allegro.h"
#include "Resistor.h"

#define VCC 1
#define GND 0

class Node {
public:
	Node();
	Node(ALLEGRO_BITMAP* image, bool type);
	void updateNode(vector<Resistor> &resistorArray, ALLEGRO_BITMAP* resistorImage);
	bool mouseOverNode(pos mouse);
	bool wireNode(pos mouse, int &selectedResIndex, UpperLowerEnum& resStart);
	//Setters
	void setIndex(int i) { index = i; }
	void setCoords(int x, int y);
	void decreseIndex() { index = index - 1; }
	//Getters
	pos getCorrds() { return nodeCoords; }
	int getIndex() { return index; }
private:
	int index;
	pos nodeCoords;
	ALLEGRO_BITMAP* image;
	bool nodeType; //true == VCC, false == GND
};

#endif