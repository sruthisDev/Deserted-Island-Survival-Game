#include "Beach.h"

Beach::Beach() :Location('B') {
	resourcesAvailable = { "coconuts", "crabs", "fish", "shells", "sand", "leaves" };
	taken = false;
}
void Beach::setTaken(bool userTaken) {
	taken = userTaken;
}
int Beach::getTaken() {
	return  taken;
}
void Beach::draw() {
	if (taken) {
		cout << " ";
	}
	else {
		Location::draw();
	}

}
int Beach::visit(Player& p) {
	if (!visited) {  
		visited = true;
		cout << "You have arrived at the beach. You find various resources."<< endl;
		p.CollectRawMaterial(resourcesAvailable);
		cout << "You gather some resources as you climb. [" << resourcesAvailable.at(0) << "]" << " [" << resourcesAvailable.at(1) << "]" << " [" << resourcesAvailable.at(2) << "]" << " [" << resourcesAvailable.at(3) << "]"<< " [" << resourcesAvailable.at(4)<< " [" << resourcesAvailable.at(5) << endl;

		p.CraftTools();
	}
	return 1;
}