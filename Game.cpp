#include "Game.h"

#define SET_COLOR(code) std::cout << "\033[" << (code) << "m"
#define RESET_COLOR() std::cout << "\033[0m"

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
}

Game::~Game() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete world[i][j];
        }
        delete[] world[i];
    }
    delete[] world;
}

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
    cout << "\033[0m";
}

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

    // Set text color to light red for the center structure (the defeated player)
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

void Game::ReadDataFile(vector<vector<string>>& data) {
    ifstream inputFile("InputDataFile.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    int rows, cols;
    inputFile >> rows >> cols;
    inputFile.ignore();
    data.resize(rows, vector<string>(cols));

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
    string word;
    while (iss >> word) {
        ++wordCount;
    }
    if (wordCount == cols) {
        cout << "Looks like there is an additional row for defining the map, ignoring line " << currentRow + 1 << endl;
    }
    
    while (getline(inputFile, line)) {
       //Process Rest of the file
    }
}

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
        return new Location();
    }

}

void Game::SetUpGame(vector < vector<string>>& data) {
    rows = data.size();
    cols = data[0].size();
    
    world = new Location * *[rows];
    for (int i = 0; i < rows; i++) {
        world[i] = new Location * [cols];
        for (int j = 0; j < cols; j++) {
            world[i][j] = GetLocation(data[i][j]);
        }
    }

    this->playerRow = 0;
    this->playerCol = 0;
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

void Game::calculateWinConditions(vector<vector<string>>& data) {
    this->numDaysToSurvive = (data[0].size() * data.size()) / 2;
    this->numAnimalsToKill = 0;
    this->numToolsToCollect = ((data[0].size() * data.size()) / 3) + 5;
}

void Game::PlayGame() {
    vector < vector<string>> data;
    ReadDataFile(data);
    SetUpGame(data);
    //SetUpGame(10, 10, 4, 5);
    calculateWinConditions(data);

    world[playerRow][playerCol]->visit(p,1);
    char move;
    bool keepPlaying = true;
    bool wrongPosition = false;

    system("cls"); 
    SET_COLOR(33);  
    cout << endl;
    cout << "========================================\n";
    cout << "        DESERTED ISLAND SURVIVAL            \n";
    cout << "========================================\n";     
    cout << "Adventure awaits as you strive to survive.\n";
    cout << "Face various challenges like wild animals \n";
    cout << "storms, gather resources and navigate the \n";
    cout << "island's diverse locations." << endl << endl;
    SET_COLOR(33);
    cout << "Beach:    Gather resources " << endl;
    cout << "Cave:     Hidden Treasure" << endl;
    cout << "Jungle:   dsd" << endl;
    cout << "Lake:     dsd" << endl;
    cout << "Mountain: date" << endl;
    cout << endl;
    cout << "========================================\n";
    
    SET_COLOR(32);
    cout << "Win Conditions are:" << endl;
    cout << "1) Survive " << this->numDaysToSurvive << " days" << endl;
    cout << "2) Kill " << this->numAnimalsToKill << " animals" << endl;
    cout << "3) Find the secret treasure" << endl;
    cout << "4) Collect a minimum of " << this->numToolsToCollect << " tools to ensure surival for longer" << endl;
    RESET_COLOR();
    cout << "\nUse 'W' to move up, 'S' to move down, 'A' to move left, 'D' to move right.\n\n";

    

    do {
        DrawGame();
        wrongPosition = false;
        move = checkAndGetInput({ 'w', 'a', 's', 'd' }, "Move (WASD): ");

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
            world[playerRow][playerCol]->visit(p);
            p.SetSurvivalDays(1);
            p.PrintStatus();

            if (p.CheckWinConditions()) {
                WinGame();
                break;
            }
            if (p.GetPlayerHealth() < 0) {
                GameOver();
                break;
            }

            char continuePlaying = checkAndGetInput({ 'y','n' }, "Continue exploring ? (y / n) : ");
            if (continuePlaying == 'n') {
                keepPlaying = false;
            }
            else if (continuePlaying == 'y') {
                keepPlaying = true;
            }
            else {
                cout << "kindly slecet (y/n): ";
                cin >> continuePlaying;
                if (continuePlaying == 'n') {
                    keepPlaying = false;
                }
                else if (continuePlaying == 'y') {
                    keepPlaying = true;
                }
            }
            SET_COLOR(34);
            cout << endl;
            cout << "------------- Next Day -------------" << endl << endl;;
            RESET_COLOR();
        }
        

    } while (keepPlaying);
}