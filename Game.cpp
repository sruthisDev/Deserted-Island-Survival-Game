#include "Game.h"

//Default constructor 
Game::Game() {  
    world = nullptr;
    rows = 0;
    cols = 0;
    playerRow = 0;
    playerCol = 0;
    gameStatus = true;
    numAnimalsToKill = 0;
    numToolsToCollect = 0;
    numDaysToSurvive = 0;
    waterPerMove = 5;
    dmgWhenHungryPerMove = 5;
    dmgWhenThirstyPerMove = 5;
    regularWinCondition = false;
    visitInitialSpecialLocation = false;
}
//destructor
Game::~Game() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete world[i][j];
        }
        delete[] world[i];
    }
    delete[] world;
}

//This function is called when the player wins the game.
void Game::WinGame() {
    cout << "\033[33m";
    cout << R"(
#########################################################################
You have successfully survived on the COMP-180 Island and won the game!
#########################################################################
               ~~~~~~~~~~~~~~~    
            ~~~~            ~~~~  
         ~~~~                  ~~~~  
       ~~~~                      ~~~~
)";
    // Change the text color to green.
    cout << "\033[32m";
    cout << R"(
      ~~~~          \O/            ~~~~
     ~~~~            |             ~~~~
     ~~~~           / \           ~~~~
)";
    cout << "\033[33m";
    cout << R"(
      ~~~~                        ~~~~
       ~~~~                      ~~~~
         ~~~~                  ~~~~
            ~~~~            ~~~~
               ~~~~~~~~~~~~~~~
        ~~~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~~
#########################################################################
)" << endl;
    cout << "\033[0m"; // // Reset the text color to default.
}

//This function is called when the player lost the game.
void Game::GameOver() {
    cout << "\033[33m";
    cout << R"(
#########################################################################
Unfortunately, you have not survived on COMP-180 Island and lost the game!
#########################################################################
               ~~~~~~~~~~~~~~~    
            ~~~~            ~~~~  
         ~~~~                  ~~~~  
       ~~~~                      ~~~~
)";

    // Set text color to light red for the center structure 
    cout << "\033[91m"; // ANSI escape code for light red
    cout << R"(
      ~~~~          X X            ~~~~
     ~~~~            |           ~~~~
     ~~~~           / \           ~~~~
)";
    cout << "\033[33m";
    cout << R"(
      ~~~~                        ~~~~
       ~~~~                      ~~~~
         ~~~~                  ~~~~
            ~~~~            ~~~~
               ~~~~~~~~~~~~~~~
        ~~~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~~
#########################################################################
)" << endl;
    cout << "\033[0m";
}

//This function loads the data from the  text file to a 2d vector
void Game::ReadDataFile(vector<vector<string>>& data) {
    ifstream inputFile("InputDataFile.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    int rows, cols;
    inputFile >> rows >> cols; // grid dimensions
    inputFile.ignore();
    data.resize(rows, vector<string>(cols)); // resize the grid as required

    string line;
    int currentRow = 0;
    while (getline(inputFile, line) && currentRow < rows) {
        istringstream iss(line);
        vector<string> temp;
        string word;
        while (iss >> word) {
            temp.push_back(word);
        }

        // Check if the number of words in the line matches the number of columns
        if (temp.size() != cols) {
            cout << "Error in format of the input file" << endl;
            exit(1);
        }

        // Assign the values to the data vector
        for (int j = 0; j < cols; ++j) {
            data[currentRow][j] = temp[j];
        }
        ++currentRow;
    }

    istringstream iss(line);
    int wordCount = 0;
    vector<string> words;
    string tempWord;
    while (iss >> tempWord) {
        words.push_back(tempWord);
    }
    if (words.size() == cols) {
        cout << "Looks like there is an additional row for defining the map, ignoring line " << currentRow + 1 << endl;
    }
    else {
        if (words[0] == "initPlayerRow") {
            if (words.size() == 2) {
                this->playerRow = stoi(words[1]);
            }            
        }
        else {
            cout << "This row should contain playerRow initialization" << endl;
            exit(1);
        }
    }
    
    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<string> words;
        string tempWord;
        while (iss >> tempWord) {
            words.push_back(tempWord);
        }

        // Skip empty lines
        if (words.empty()) {
            continue;
        }

        // Process player column initialization
        if (words[0] == "initPlayerRow") {
            if (words.size() == 2) {
                this->playerRow = stoi(words[1]);
            }
            else {
                cout << "Invalid format for playerCol initialization." << endl;
                exit(1);
            }
        }
        // Process player column initialization
        else if (words[0] == "initPlayerCol") {
            if (words.size() == 2) {
                this->playerCol = stoi(words[1]);
            }
            else {
                cout << "Invalid format for playerCol initialization." << endl;
                exit(1);
            }
        }
        // Process regular win condition
        else if (words[0] == "regularWinCondition") {
            if (words.size() == 2) {
                if (words[1] == "0" || words[1] == "false") {
                    this->regularWinCondition = false;
                }
                else {
                    this->regularWinCondition = true;
                }
            }
            else {
                cout << "Invalid format for regular win condition." << endl;
                exit(1);
            }
        }
        // If line does not match known keywords
        else {
            cout << "Unrecognized line: " << line << endl;
        }
    }
    inputFile.close();
}

//This function returns a locations object as per the data in the file 
Location* Game::GetLocation(string className) {
    if (className == "Lake" || className == "lake" || className == "LAKE") {
        return new Lake();
    }
    else if (className == "Beach" || className == "beach" || className == "BEACH") {
        return new Beach();
    }
    else if (className == "Jungle" || className == "jungle" || className == "JUNGLE") {
        return new Jungle();
    }
    else if (className == "Cave" || className == "cave" || className == "CAVE") {
        return new Cave();
    }
    else if (className == "Mountain" || className == "mountain" || className == "MOUNTAIN") {
        return new Mountain();
    }
    else {
        return new Location(); // Returns a default locations object.
    }

}

//This function sets the game environment
void Game::SetUpGame(vector < vector<string>>& data) {
    rows = data.size(); // sets number of rows
    cols = data[0].size(); // sets number of columns 
    
    if ((data[this->playerRow][playerCol] != "0") && (data[this->playerRow][playerCol] != "o")) {
        cout << "Looks like the initial player location assigned is a special location. It is suggestible that initial location is not a special location." << endl;
        char in = checkAndGetInput({'y','n'},"Do you want to treat this as special location or ignore?(y/n)");
        if (in == 'y') {
            data[this->playerRow][this->playerCol] = "location" ;
        }
        else {
            this->visitInitialSpecialLocation = true;
        }
    }

    world = new Location * *[rows];
    for (int i = 0; i < rows; i++) {
        world[i] = new Location * [cols];
        for (int j = 0; j < cols; j++) {
            world[i][j] = GetLocation(data[i][j]); // assigns the location based on the data given in the text file
        }
    }

    
}

void Game::SetUpGame(int userRows, int userCols, int userPlayerRow, int userPlayerCol) {
    rows = userRows;
    cols = userCols;
    playerRow = userPlayerRow;
    playerCol = userPlayerCol;
    world = new Location * *[rows];
    for (int i = 0; i < rows; ++i) {
        world[i] = new Location * [cols];
        for (int j = 0; j < cols; ++j) {

            world[i][j] = new Location();

            if (i == 0 ||  i == 5) {
                world[i][j] = new Beach();
            }
            
            if (i == 1 || i == 3) {
                world[i][j] = new Mountain();
            }

            if (i == 2) {
                world[i][j] = new Cave();
            }
            if (i == 6) {
                world[i][j] = new Jungle();
            }

            

        }
    }
    
}
//This function draws the grid as per the given size 
void Game::DrawGame() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == playerRow && j == playerCol) {
                cout << "P";
            }
            else {
                world[i][j]->draw();
            }
        }
        cout << endl;
    }    
}

// Calculates the win conditions based on the game's data grid.
void Game::calculateWinConditions(vector<vector<string>>& data) {
    if (this->regularWinCondition) {
        this->numDaysToSurvive = static_cast<int>((data[0].size() * data.size()) / 2); // Calculate required survival days.
        this->numAnimalsToKill = 3;
        this->numToolsToCollect = static_cast<int>(((data[0].size() * data.size()) / 5)); // Calculate the number of tools to collect.

        if (this->numToolsToCollect <= 0) {
            this->numToolsToCollect = 1;
        }
    }
    else {
        this->numDaysToSurvive = 5;
        this->numAnimalsToKill = 1;
        this->numToolsToCollect = 2;
    }

}

bool Game::CheckWinConditions(Player&p){
    
    if (p.GetNumOfTools() >= this->numToolsToCollect) {
        p.toolsWinCondition = true;
    }

    if (p.GetNumAnimalsKilled() >= this->numAnimalsToKill) {
        p.animalsKilledWinCondition = true;
    }

    if (p.GetSurvivalDays() >= this->numDaysToSurvive) {
        p.survivalDaysWinCondition = true;
    }

    if (p.survivalDaysWinCondition && p.animalsKilledWinCondition && p.HasVisitedMysteryPlace() && p.toolsWinCondition) {
        cout << "\n \nWin Conditions Met: " << endl;
        cout << "Required number of tools were crafted (" << p.GetNumOfTools() << ")" << endl;
        cout << "Required number of animals were killed (" << p.GetNumAnimalsKilled() << ") " << endl;
        cout << "Survived for total (" << p.GetSurvivalDays() << ") days. " << endl;;
        cout << "Found the caves secret place" << endl;
        return true;
    }

    return false;
}

// Main game loop where the player interacts with the game.
void Game::PlayGame() {
    vector < vector<string>> data;
    ReadDataFile(data);
    SetUpGame(data);
    //SetUpGame(10, 10, 4, 5);
    calculateWinConditions(data);

    char move;
    bool keepPlaying = true;
    bool wrongPosition = false;

    system("cls"); 
    SET_COLOR(33);  
    // Display game introduction and location details.
    cout << endl;
    cout << "========================================\n";
    cout << "        DESERTED ISLAND SURVIVAL            \n";
    cout << "========================================\n";     
    cout << "Adventure awaits as you strive to survive.\n";
    cout << "Face various challenges like wild animals \n";
    cout << "storms, gather resources and navigate the \n";
    cout << "island's diverse locations." << endl << endl;
    SET_COLOR(33);
    // Display winning conditions for the game.
    cout << "Beach(B):    Contains various resources found on beach like Coconuts " << endl;
    cout << "Cave(C):     Hidden Treasure crucial for winning the game" << endl;
    cout << "Jungle(J):   Trove of rich resources, visit to gain" << endl;
    cout << "Lake(L):     Site for quenching thirst" << endl;
    cout << "Mountain(M): Rare resources are found here" << endl;
    cout << "Location(*): Basic location" << endl;
    cout << "In the grid the locations are represented by the characters shown above after you have visited them" << endl;
    cout << endl;
    cout << "========================================\n";
    
    SET_COLOR(32);
    cout << "Win Conditions are:" << endl;
    cout << "1) Survive " << this->numDaysToSurvive << " days" << endl;
    cout << "2) Kill " << this->numAnimalsToKill << " animals" << endl;
    cout << "3) Find the secret place" << endl;
    cout << "4) Collect a minimum of " << this->numToolsToCollect << " tools to ensure surival for longer" << endl;
    RESET_COLOR();
    cout << "\nUse 'W' to move up, 'S' to move down, 'A' to move left, 'D' to move right.\n\n";

    if (this->visitInitialSpecialLocation == true) {
        DrawGame();
        world[this->playerRow][this->playerCol]->visit(p);
    }
    else {
        world[playerRow][playerCol]->visit(p, 1);
    }    

    do {
        DrawGame();
        wrongPosition = false;
        move = checkAndGetInput({ 'w', 'a', 's', 'd' }, "Move (WASD): ");

        // change player postion based on input.
        switch (move) {
        case 'w':
            if (playerRow > 0) {
                --playerRow;
            }
            else {
                wrongPosition = true;
                cout << "Player is at '" << playerRow+1 << "' row cant take this move from this position" << endl;
            }
            break;
        case 's':
            if (playerRow < rows - 1) {
                ++playerRow;
            }
            else {
                wrongPosition = true;
                cout << "Player is at '" << playerRow+1 << "' row cant take this move from this position" << endl;
            }
            break;
        case 'a':
            if (playerCol > 0){
                --playerCol;
            }else {
                wrongPosition = true;
                cout << "Player is at '" << playerCol+1 << "' column cant take this move from this position" << endl;
            }
            break;
        case 'd':
            if (playerCol < cols - 1) {
                ++playerCol;
            }
            else {
                wrongPosition = true;
                cout << "Player is at '" << playerCol+1 << "' column cant take this move from this position" << endl;
            }
            break;
        }
        if (!wrongPosition) {
            world[playerRow][playerCol]->visit(p); // Visit a new location.

            //These update the player stats at the end of the day
            p.SetSurvivalDays(1); // Increment survival days.
            if (!p.GetEnoughFood()) {
                cout << endl << "Not enough food today" << endl;
                p.SetPlayerHealth(p.GetPlayerHealth() - this->dmgWhenHungryPerMove);
                cout << "Lose 5 health" << endl;
            }
            p.PrintStatus(); // Print player's current status.
            p.SetEnoughFood(false);

            if (this->CheckWinConditions(p)) {
                WinGame(); // Player won the game.
                break;
            }
            if (p.GetPlayerHealth() <= 0) {
                GameOver(); // Player lost the game.
                break;
            }

            p.SetWater(p.GetWater() - this->waterPerMove);       //Daily toll of water consumption
            if (p.GetWater() <= 10) {
                cout << "Hydration level too low. Health will be impacted" << endl;
                p.SetPlayerHealth(p.GetPlayerHealth() - this->dmgWhenThirstyPerMove);
            }
            // Prompt for continuing the game.
            char continuePlaying = checkAndGetInput({ 'y','n' }, "Continue exploring ? (y / n) : ");
            if (continuePlaying == 'n') {
                keepPlaying = false;
            }
            else if (continuePlaying == 'y') {
                keepPlaying = true;
            }

            SET_COLOR(34);
            cout << endl;
            cout << "------------- Next Day -------------" << endl << endl;;
            RESET_COLOR();
        }
        

    } while (keepPlaying);
}