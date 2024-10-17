#include "Lake.h"

Lake::Lake() :Location('L') {
	resourcesAvailable = { "water", "fish", "reeds", "medicinal_herbs", "mud"};
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
    FishingEvent(p);
	return 1;
}

void Lake::FishingEvent(Player& p) {
    // Define options and their enabled state
    vector<Option> options = {
        {"Try to catch fish with bare hands", true},
        {"Use a spear", p.hasToolX("spear")},
        {"Do nothing", true},
    };

    // Build the prompt string
    cout << endl << "You see fish swimming near the shore." << endl;
    printOptions(options);
    cout << "Select an option (1-" << options.size() << "): ";

    // Get valid input from the player
    char in = checkAndGetInput(options);

    switch (in) {
    case '1':
        cout << "You attempt to catch fish with your bare hands." << endl;
        // Random chance of success
        if (generateRandomNumber(0,3) % 3 == 0) {
            cout << "You managed to catch a fish! It will be a good meal." << endl;
            p.SetEnoughFood(true);
        }
        else {
            cout << "The fish slipped away. Better luck next time." << endl;
        }
        break;
    case '2':
        cout << "You use your fishing spear and catch fish easily." << endl;
        p.SetEnoughFood(true);
        cout << "You caught a fish. It will make a great meal." << endl;
        break;
    case '3':
        cout << "You decide not to attempt catching the fish." << endl;
        break;
    }
}
