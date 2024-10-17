#include "Cave.h"

Cave::Cave() :Location('C') {
	resourcesAvailable = { "stone", "animal_hide"};
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
	int secretEventSuccess = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "You have arrived at the Cave. You find various resources." << endl;
		//cout << "You've discovered a secret place! You have achieved an objective!\n";
		//p.foundMysteryPlace();
		secretEventSuccess = 10;
	}
	else {
		numResources = 1;
		secretEventSuccess = 70;
		cout << "You are again at the Cave. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);

	if (p.hasToolX("torch")) {
		cout << "Having a torch has enabled you to discover the secret place! You have achieved a win objective!\n";
		p.foundMysteryPlace();
	}
	else {
		int eventRandom = generateRandomNumber(0, 100);
		if (eventRandom < secretEventSuccess) {
			cout << "Even in the dark you stumbled across the secret place! You have achieved a win objective!\n ";
			p.foundMysteryPlace();
		}
	}

	StagnantWaterEvent(p);
	BatsEvent(p);
	return 1;
}

void Cave::StagnantWaterEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Drink the water", true},
		{"Leave it", true},
	};

	// Build the prompt string
	cout << endl << "You come across a stagnant pool of water. It looks questionable." << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	// Get valid input from the player
	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		if (generateRandomNumber(0,100) < 50) { // 50% chance of getting sick
			cout << "The water was contaminated. You feel sick and lose some health." << endl;
			p.SetPlayerHealth(p.GetPlayerHealth() - 15);
			cout << "You lost 15 health." << endl;
		}
		else {
			cout << "The water was surprisingly refreshing. You gain some hydration." << endl;
			p.SetWater(p.GetWater() + 10);
			cout << "You gained 10 hydration." << endl;
		}
		break;
	case '2':
		cout << "You decide not to risk it and leave the water alone." << endl;
		break;
	}
}

void Cave::BatsEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Use a whistle to scare the bats away", p.hasToolX("whistle")},
		{"Duck and cover", true},
	};

	// Build the prompt string
	cout << endl << "As you explore the cave, a swarm of bats flies toward you." << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	// Get valid input from the player
	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		cout << "You blow the whistle, and the bats scatter in all directions revealing some resources." << endl;
		break;
		
	case '2':
		cout << "You duck and cover, but a few bats manage to scratch you." << endl;
		p.SetPlayerHealth(p.GetPlayerHealth() - 5);
		cout << "You lost 5 health." << endl;
		break;
	}
}