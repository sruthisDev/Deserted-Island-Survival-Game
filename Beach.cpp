#include "Beach.h"


Beach::Beach() :Location('B') {
	resourcesAvailable = { "coconuts", "crabs", "shells", "leaves", "rope", "wood"};
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
	int eventProb = generateRandomNumber(0, 100);
	if (eventProb < 20) {
		DriftWoodEvent(p);
	}
	else if (eventProb < 80) {
		FallingCoconutEvent(p);
	}
	return 1;
}

void Beach::DriftWoodEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Collect the Driftwood", false}, // This option is disabled if the player lacks tools
		{"Leave it be", true},
	};

	if (p.hasToolX("axe") || p.hasToolX("knife") || p.hasToolX("spear")) {
		options[0].enabled = true;
	}

	cout << endl << "You see a bundle of driftwood floating near the shore." << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		cout << "You successfully collect the driftwood! It's useful for crafting." << endl;
		p.CollectRawMaterial({ "wood","wood"});
		break;
	case '2':
		cout << "You decide to leave the driftwood be. Perhaps another time!" << endl;
		break;
	}
}


void Beach::FallingCoconutEvent(Player& p) {

	// Build the prompt string
	cout << endl << "Suddenly, a coconut falls from a nearby palm tree!" << endl;
	if (p.GetPlayerHealth() > 60) {
		cout << "You have energy to react and dodge the falling cocounut" << endl;
	}
	else {
		cout << "You are too tired to dodge and the coconut falls on your head" << endl;
	}
	
	cout << "You get:" << endl;
	p.CollectRawMaterial({ "fibers","fibers" });
	cout << "from the coconut and quench your thirst using coconut water" << endl;

	p.SetWater(p.GetWater() + 50);
}
