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
	void setIndex(int i) { index = i; }
	void setCoords(int x, int y);
	bool mouseOverNode(pos mouse);
	pos getCorrds() { return nodeCoords; }
private:
	int index;
	pos nodeCoords;
	ALLEGRO_BITMAP* image;
};

#endif