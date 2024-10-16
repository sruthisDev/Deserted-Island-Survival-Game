#include "Location.h"

#include<iostream>
using namespace std;

//macro for console color
#define SET_COLOR(code) std::cout << "\033[" << (code) << "m"
#define RESET_COLOR() std::cout << "\033[0m"

Location::Location(char s) {
	visited = false;
	symbol = s;
}

void Location::setSymbol(char userSymbol) {
	symbol = userSymbol;
}
char Location::getSymbol() {
	return symbol;
}

void Location::setVisited(bool userVisited) {
	visited = userVisited;
}
bool Location::getVisited() {
	return visited;
}

void Location::draw() {
	if (visited) {
		cout << symbol;
	}
	else {
		cout << '.';
	}
}

int Location::visit(Player& p) {
	if (!visited) {
		visited = true;
		cout << "You found a new location." << endl;
	}
	return 1;
}

int Location::visit(Player& p, bool init) {
	if (!visited) {
		visited = true;
		//cout << "You found a new location." << endl;
	}
	return 1;
}


vector<string>& Location::getResources() {
	return this->resourcesAvailable;
}

void Location::CollectResources(Player& p, size_t numResources) {
	vector<string> resourcesCollected;
	if (this->resourcesAvailable.size() <= 0) {
		return;
	}
	vector<string>& availableResources = getResources(); // Derived classes provide resources
	int sizeOfResources = static_cast<int>(availableResources.size() - 1);
	int index;

	for (int i = 0; i < numResources; i++) {
		if (sizeOfResources >= 0) {
			index = generateRandomNumber(0, sizeOfResources);
			resourcesCollected.push_back(availableResources[index]);
			//cout << " [" << resourcesCollected.back() << "]";
		}
	}
	p.CollectRawMaterial(resourcesCollected);
	p.CraftTools();
}