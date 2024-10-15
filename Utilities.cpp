#include "Utilities.h"

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
		cout << text ;
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

int generateRandomNumber(int start, int end) {
	static std::mt19937 generator(42); 
	std::uniform_int_distribution<int> distribution(start, end);
	return distribution(generator);
}