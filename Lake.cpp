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
	size_t numResources = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "You have arrived at the Lake. You find various resources." << endl;
	}
	else {
		numResources = 1;
		cout << "You are again at the Lake. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	return 1;
}
