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

	vector<string> resourcesCollected;
	int index, sizeOfResources;
	sizeOfResources = resourcesAvailable.size() - 1;

	if (!visited) {  

		visited = true;
		cout << "You have arrived at the beach. You find various resources."<< endl;
		SetValue(generateRandomNumber(0, sizeOfResources)) ;
		cout << "You gather some resources as you climb.";
		for (int i = 0; i < GetValue(); i++) {
			index = generateRandomNumber(0, sizeOfResources);
			resourcesCollected.push_back( resourcesAvailable[index]);
			cout << " [" << resourcesCollected[i] << "]";
		}
		cout << endl;
		p.CollectRawMaterial(resourcesCollected);
		p.CraftTools();
	}
	else {

		cout << "You are again at the beach. You find few resources." << endl;
		SetValue(resourcesAvailable.size()/2);
		cout << "You gather some resources as you climb.";
		for (int i = 0; i < GetValue(); i++) {
			index = generateRandomNumber(0, sizeOfResources);
			resourcesCollected.push_back(resourcesAvailable[index]);
			cout << " [" << resourcesCollected[i] << "]";
		}
		cout << endl;
		p.CollectRawMaterial(resourcesCollected);
		p.CraftTools();

	}
	return 1;
}