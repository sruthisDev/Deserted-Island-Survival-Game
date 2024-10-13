#include "Cave.h"

Cave::Cave() :Location('C') {
	resourcesAvailable = { "stones"};
	taken = false;
}
void Cave::setTaken(bool userTaken) {
	taken = userTaken;
}
int Cave::getTaken() {
	return  taken;
}
void Cave::draw() {
	if (taken) {
		cout << " ";
	}
	else {
		Location::draw();
	}

}
int Cave::visit(Player& p) {
	if (!visited) {

		visited = true;
		cout << "Exploring a mysterious cave..." << endl;

		p.CollectRawMaterial(resourcesAvailable);
		p.CraftTools();

		/*
		if (dis(gen) % 100 < 40) {
			std::cout << "You've discovered a secret place! You have achieved an objective!\n";
			p.VisitCave();
		}
		*/

		std::cout << "You've discovered a secret place! You have achieved an objective!\n";
		p.foundMysteryPlace();
	}
	return 1;
}