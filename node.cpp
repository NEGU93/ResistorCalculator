#include "Node.h"

Node::Node(ALLEGRO_BITMAP* image) {
	if (image != NULL) {
		this->image = image;
		this->index = -1;
		nodeCoords.x = -1;
		nodeCoords.y = -1;
	}
}
Node::Node() {
	this->image = NULL;
	this->index = -1;
	nodeCoords.x = -1;
	nodeCoords.y = -1;
}
void Node::updateNode() {
	if ((nodeCoords.x != -1) && (nodeCoords.y != -1)) {
		al_draw_bitmap(image, nodeCoords.x, nodeCoords.y, 0);
	}
}
void Node::setCoords(int x, int y) {
	nodeCoords.x = x;
	nodeCoords.y = y;
}
bool Node::mouseOverNode(pos mouse) {
	if ((mouse.x > nodeCoords.x) && (mouse.x < nodeCoords.x + al_get_bitmap_width(image))) {
		if ((mouse.y > nodeCoords.y) && (mouse.y < nodeCoords.y + al_get_bitmap_height(image))) {
			return true;
		}
	}
	return false;
}
