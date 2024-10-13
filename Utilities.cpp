#include "utilities.h"

bool checkInVector(std::vector<char>& options, char& input) {
	for (size_t i = 0; i < options.size(); i++) {
		if (input == options[i]) {
			return true;
		}
	}
	return false;
}

char checkAndGetInput(std::vector<char> options, string text) {
	char input = ' ';
	while (true) {
		cout << text << endl;
		cin >> input;
		input = tolower(input);
		if (checkInVector(options, input)) {
			break;
		}
		else {
			cout << "Invalid Input " << endl;
		}
	}
	return input;
}

int generateRandomNumber() {
	static std::mt19937 generator(42); // Seed initialized once
	std::uniform_int_distribution<int> distribution(0, 100);
	return distribution(generator);
}