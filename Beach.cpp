#include "Beach.h"


Beach::Beach() :Location('B') {
	resourcesAvailable = { "coconuts", "crabs", "fish", "shells", "sand", "leaves" };
	taken = false;
	value = 0;
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
void Beach::SetValue(int num) {
	value = num;
}
int Beach::GetValue() {
	return value;
}

int Beach::visit(Player& p) {

	size_t numResources = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "You have arrived at the beach. You find various resources." << endl;
	}
	else {
		numResources = 1;
		cout << "You are again at the beach. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	return 1;
}