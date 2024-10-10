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
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 9);

		p.CollectRawMaterial(resourcesAvailable);
		p.CraftTools();

		/*
		if (dis(gen) == 0) {
			std::cout << "You've discovered a secret place! This is a major victory!\n";
			exit(0);  
		}
		*/

		std::cout << "You've discovered a secret place! This is a major victory!\n";
		p.VisitCave();
	}
	return 1;
}