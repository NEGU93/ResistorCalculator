#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED	

#include "def.h"
#include "allegro.h"

#define VCC 1
#define GND 0

class Node {
public:
	Node();
	Node(ALLEGRO_BITMAP* image);
	void updateNode();
	bool mouseOverNode(pos mouse);
	//Setters
	void setIndex(int i) { index = i; }
	void setCoords(int x, int y);
	//Getters
	pos getCorrds() { return nodeCoords; }
	int getIndex() { return index; }
private:
	int index;
	pos nodeCoords;
	ALLEGRO_BITMAP* image;
};

#endif