#include "Lake.h"

Lake::Lake() :Location('L') {
	resourcesAvailable = { "Drinking_Water", "fish" };
	taken = false;
}
void Lake::setTaken(bool userTaken) {
	taken = userTaken;
}
int Lake::getTaken() {
	return  taken;
}
void Lake::draw() {
	if (taken) {
		cout << " ";
	}
	else {
		Location::draw();
	}

}
int Lake::visit(Player& p) {
	if (!visited) {
		visited = true;
		cout << "You have arrived at the beach. You find various resources." << endl;
		p.CollectRawMaterial(resourcesAvailable);
		cout << "You gather some resources as you climb. [" << resourcesAvailable.at(0) << "]" << " [" << resourcesAvailable.at(1) << endl;
		p.CraftTools();
	}
	return 1;
}
