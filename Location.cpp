#include "Location.h"

#include<iostream>
using namespace std;

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
		p.CraftTools(resourcesAvailable);

	}
	return 1;

}