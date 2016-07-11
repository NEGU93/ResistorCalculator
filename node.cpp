#include "Node.h"

Node::Node(ALLEGRO_BITMAP* image, bool type) {
	if (image != NULL) {
		this->image = image;
		this->index = -1;
		nodeCoords.x = -1;
		nodeCoords.y = -1;
		nodeType = type;
	}
}
Node::Node() {
	this->image = NULL;
	this->index = -1;
	nodeCoords.x = -1;
	nodeCoords.y = -1;
	nodeType = false;
}
void Node::updateNode(vector<Resistor> &resistorArray, ALLEGRO_BITMAP* resistorImage) {
	if ((nodeCoords.x != -1) && (nodeCoords.y != -1)) {
		al_draw_bitmap(image, nodeCoords.x, nodeCoords.y, 0);
	}
	if (index != -1) {
		if (index < resistorArray.size()) { // Just in case, It should always enter here.
			if (nodeType) { //If VCC
				pos firstRes = resistorArray[index].getCoords();
				draw_line(nodeCoords.x + al_get_bitmap_width(image) / 2, nodeCoords.y + al_get_bitmap_height(image), firstRes.x, firstRes.y, al_map_rgb(LINECOLOUR), LINEWIDTH);
			}
			else {
				pos lastRes = resistorArray[index].getCoords();
				if (resistorArray[index].getHoriz()) {
					draw_line_inverted(nodeCoords.x + al_get_bitmap_width(image) / 2, nodeCoords.y, lastRes.x + al_get_bitmap_width(resistorImage), lastRes.y, al_map_rgb(LINECOLOUR), LINEWIDTH);
				}
				else {
					draw_line_inverted(nodeCoords.x + al_get_bitmap_width(image) / 2, nodeCoords.y, lastRes.x, lastRes.y + al_get_bitmap_width(resistorImage), al_map_rgb(LINECOLOUR), LINEWIDTH);
				}
			}
		}
		else { cout << "VCC is pointing outside the array" << endl; }
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
