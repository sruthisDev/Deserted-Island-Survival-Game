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
	size_t numResources = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "You have arrived at the Cave. You find various resources." << endl;
		cout << "You've discovered a secret place! You have achieved an objective!\n";
		p.foundMysteryPlace();
	}
	else {
		numResources = 1;
		cout << "You are again at the Cave. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	return 1;
}