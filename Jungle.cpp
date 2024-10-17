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
		numResources = getResources().size()-3;
	}
	else {
		numResources = 2;
		cout << "You are again at the Jungle. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	WildAnimalAttackEvent(p);
	FollowMonkeyEvent(p);
	return 1;
}

void Jungle::WildAnimalAttackEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Attack with a tool", p.hasToolX("axe") || p.hasToolX("spear") || p.hasToolX("knife")},
		{"Attack directly (50% chance to succeed)", true},
		{"Escape", true}
	};

	cout << endl << "A wild bear suddenly appears in the dense jungle!" << endl;
	cout << "You need to act quickly. What will you do?" << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	// Get valid input from the player
	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		cout << "You use your tool to attack the wild animal." << endl;
		cout << "You successfully kill the animal and obtain an animal hide!" << endl;
		p.CollectRawMaterial({ "animal_hide" });
		cout << "You eat the animal to satisfy food quota for the day" << endl;
		p.SetEnoughFood(true);
		p.SetNumAnimalsKilled(1);
		break;
	case '2':
		cout << "You decide to attack the animal directly." << endl;
		if (generateRandomNumber(0,100) < 50) { // 50% chance of success
			cout << "You managed to kill the animal with your bare hands! You obtain an animal hide." << endl;
			p.CollectRawMaterial({ "animal_hide" });
			cout << "You eat the animal to satisfy food quota for the day" << endl;
			p.SetEnoughFood(true);
			p.SetNumAnimalsKilled(1);
			break;
		}
		else {
			cout << "The animal overpowered you. You lost 15 health." << endl;
			p.SetPlayerHealth(p.GetPlayerHealth() - 15);
		}
		break;
	case '3':
		cout << "You chose to escape from the animal." << endl;
		cout << "You run away safely but gain no rewards." << endl;
		break;
	}
}

void Jungle::PoisonousPlantEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Examine the plant closely and try to harvest", true},
		{"Avoid the plant and continue on your way", true},
	};

	// Display event and options
	cout << endl << "While navigating the jungle, you come across a peculiar-looking plant." << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	// Get valid input from the player
	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		cout << "You examined the plant closely and try to pluck it carefully. " << endl;
		if (generateRandomNumber(0, 1) < 1) {
			cout << "You carefull harvest a medicinal herb" << endl;
			p.CollectRawMaterial({ "herbs" });
		}
		else {
			cout << "You prick yourself and hurt yourself" << endl;
			cout << "You lost 15 health" << endl;
			p.SetPlayerHealth(p.GetPlayerHealth() - 15);
		}
		break;
	default:
		cout << "You wisely chose to avoid the plant and continue your journey unharmed." << endl;
		break;
	}
}

void Jungle::FollowMonkeyEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Follow the monkey and take the fruits", true},
		{"Follow the monkey and observe", true},
		{"Ignore the monkey and move on", true}
	};

	// Build the prompt string
	cout << endl << "You notice a monkey carrying some fruits. It seems to be heading somewhere." << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	// Get valid input from the player
	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		cout << "You took the fruits, but the monkey got angry and attacked!" << endl;
		p.SetPlayerHealth(p.GetPlayerHealth() - 5);
		cout << "You lost 5 health." << endl;
		p.CollectRawMaterial({ "fruits" });
		break;
	case '2':
		cout << "You followed the monkey and found some fruits. The monkey didn't notice." << endl;
		p.CollectRawMaterial({ "fruits" });
		break;
	case '3':
		cout << "You ignored the monkey and continued on your way." << endl;
		break;
	}
}
