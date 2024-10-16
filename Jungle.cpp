#include "Jungle.h"

Jungle::Jungle() :Location('J') {
	resourcesAvailable = { "coconut","wood", "stone", "leaves", "plants", "fruits", "resin", "fibers", "animal_hide", "animal_bone"};
	taken = false;
}
void Jungle::setTaken(bool userTaken) {
	taken = userTaken;
}
int Jungle::getTaken() {
	return  taken;
}
void Jungle::draw() {
	if (taken) {
		cout << " ";
	}
	else {
		Location::draw();
	}

}
int Jungle::visit(Player& p) {

	size_t numResources = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "You have entered the Jungle. There are many resources here and Danger lurks around every tree...\n\n";
		std::cout << "An animal appears!\n";
		std::cout << "Choose an action: \n1. Attack\n2. Escape\n";
		char action;
		std::cin >> action;

		if (action == '1') {
			attack(p);
		}
		else {
			escape(p);
		}
	}
	else {
		numResources = 1;
		cout << "You are again at the Jungle. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	return 1;
}

void Jungle::attack(Player& player) {
	if (player.GetNumOfTools() > 0) {
		std::cout << "You choose to attack the animal with your tools...\n";
		player.SetNumAnimalsKilled(1); // Increment the count of animals killed
		std::cout << "You killed the animal! The path ahead seems clearer now.\n";
	}
	else {
		std::cout << "You attempt to attack but have no tools! The animal escapes.\n";
	}
}

void Jungle::escape(Player& player) {
	std::cout << "You choose to escape from the wild animal...\n";
	std::cout << "You quickly back away and the animal does not pursue. Safe for now!\n";
}