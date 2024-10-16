#include "Mountain.h"

Mountain::Mountain() :Location('M') {
	resourcesAvailable = { "stone", "leaves", "wood", "animal_hide", "animal_bone"};
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
	size_t numResources = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "Climbing the mountain" << endl;
	}
	else {
		numResources = 1;
		cout << "You are again at the Mountain. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	return 1;
}