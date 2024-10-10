#include "Mountain.h"

Mountain::Mountain() :Location('M') {
	resourcesAvailable = { "stones", "leaves", "wood" };
	taken = false;
}
void Mountain::setTaken(bool userTaken) {
	taken = userTaken;
}
int Mountain::getTaken() {
	return  taken;
}
void Mountain::draw() {
	if (taken) {
		cout << " ";
	}
	else {
		Location::draw();
	}

}
int Mountain::visit(Player& p) {
	if (!visited) {
		visited = true;
		cout << "Climbing the mountain..."<<endl;
		cout << "You gather some resources as you climb."<<endl;
		p.CollectRawMaterial(resourcesAvailable);
		p.CraftTools();
	}
	return 1;
}