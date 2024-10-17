Deserted Island Survival

Deserted Island Survival is a console-based adventure game where you must navigate different locations on a deserted island, face various challenges, collect resources, and craft tools to survive. The goal is to stay alive while completing certain objectives within the game world.

Game Overview

You are stranded on a deserted island and must survive by exploring different locations, gathering resources, and overcoming obstacles such as wild animals, harsh weather, and scarce resources. Your key metrics for survival include managing water and health. 
The game includes five distinct locations with unique events and resources: Cave, Lake, Mountain, Beach, and Jungle.

Input File Format

The game reads an input file to set up the world map. The file name should be "InputDataFile.txt" and should follow this format:

    First Line: Specifies the number of rows and columns in the grid.
    Subsequent Lines: Defines the grid layout, with each location represented by a name (ex "beach," "lake", "jungle","cave","mountain") or "0" or "o" for an empty spot.
    Next Line: playerInitial Row
    Next Line: playerIntial Col {These together define the starting location of the player}
    Next Line: regularWinCondition {This is disabled by default ensuring for easier win. To test win condition can be set to 0}


Example:
//File start
5 6
lake jungle mountain cave beach 0
o o o beach 0 0
o o o jungle 0 0
o o o beach 0 0
o o o beach 0 0
initPlayerRow 1
initPlayerCol 0
regularWinCondition 0
//File end this is set to win pretty quickly
This sample file is provided as part of the zip

Each location has various resources whose types can be for food, for water and for crafting purposes. Each location has a min of two events that occur randomly based on probability. Furthermore visiting same location again gives lesser resources.

Recipes for Tools:

    Axe:

        wood (beach, mountain, jungle)

        stone (cave, mountain, jungle)

    Bandage:

        medical_herbs (lake)

    Spear:

        wood (beach, mountain, jungle)

        stone (cave, mountain, jungle)

        rope (beach)

    Sleeping Bag:

        leaves (beach, mountain, jungle)

        reeds (lake)

    Rope:

        coconuts (beach, jungle)

    Clothing:

        animal_hide (cave, mountain, jungle)

        leaves (beach, mountain, jungle)

    Container:

        wood (beach, mountain, jungle)

        rope (beach)

    Mud Pack:

        mud (lake)

        medical_herbs (lake)

    Whistle:

        animal_bone (mountain, jungle)

        wood (beach, mountain, jungle)

    Torch:

        animal_fat (Secret location)