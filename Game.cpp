/****************************
** File: Game.cpp
** Project: CMSC 202 Project 2, Spring 2024
** Author: Eden Zhang
** Date: 3/03/2024
** Section: 30/34
** E-Mail: ezhang1@umbc.edu
**
**  This is the cpp file for the Game.h file. 
**  Holds most the functions that are necessary to run
**  the game and all its features/mechanics
**
************************************************/
#include "Game.h"

// Gets the data file, mainly for the pokedex
Game::Game(string filename)
{
    m_filename = filename;
}

// LoadFile
// After receiving the data file, goes through each pokemon and creates it as an object
// Stores each pokemon object into the pokedex object array for later use
void Game::LoadFile()
{
    int num;
    string name;
    int cp;
    int rarity;
    fstream inputStream;

    inputStream.open(m_filename);

    // Iterates through the data file and 
    // adds objects into m_pokeDex with all the poke info
    if (inputStream.is_open())
    {
        for (int i = 0; i < TOTAL_POKEMON; i++)
        {
            inputStream >> num >> name >> cp >> rarity;
            m_pokeDex[i] = Pokemon(num, name, cp, rarity);
        }
    }

    inputStream.close();

}

// Goes through the whole pokedex array and prints the info in a format
void Game::DisplayPokeDex()
{   
    // Loops through the pokedex and prints the poke names and numbers
    // With proper formatting
    for (int i = 0; i < TOTAL_POKEMON; i++)
    {
        cout << setw(NUM_WIDTH) << m_pokeDex[i].GetNum() << "." << 
        setw(NAME_WIDTH) << m_pokeDex[i].GetName() << endl;
    }
}

// MainMenu
// The player will see this the most where they choose what they want to do
// Depending on what they choose, calls the appropriate functions
void Game::MainMenu()
{
    int user = 0;

    while (user != 6)
    {
        cout << "What would you like to do?:" << endl;
        cout << "1. Display Complete PokeDex" << endl;
        cout << "2. Display your Team" << endl;
        cout << "3. Search for a new Pokemon" << endl;
        cout << "4. Battle your Pokemon" << endl;
        cout << "5. Train your Pokemon" << endl;
        cout << "6. Exit" << endl;
        cin >> user;

        if (user == 1)
        {
            DisplayPokeDex();
        } else if (user == 2)
        {
            DisplayTeam();
        } else if (user == 3)
        {
            CatchPokemon();
        } else if (user == 4)
        {
            BattlePokemon();
        } else if (user == 5)
        {
            TrainPokemon();
        } else if (user == 6)
        {
            cout << "Thanks for playing!" << endl;
        }
    }
}

// CatchPokemon
// Main function for catching pokemon
void Game::CatchPokemon()
{
    // For the randomizer in Catching Pokemon, this is the top number from 0-99
    int const MAX_CHANCE = 100;
    int rarity = CatchMenu();
    int number = rand() % MAX_CHANCE;

    cout << "You start to search..." << endl;
    // Takes the user's choice of rarity and passes it to the
    // appropriate if statements to run the random chance
    switch (rarity)
    {
        case 1:
            if (number < COMMON)
            {
                FoundPokemon(rarity);
            } else
            {
                cout << "No Pokemon was found." << endl;
            }
            break;
        case 2:
            if (number < UNCOMMON)
            {
                FoundPokemon(rarity);
            } else
            {
                cout << "No Pokemon was found." << endl;
            }
            break;
        case 3:
            if (number < ULTRA)
            {
                FoundPokemon(rarity);
            } else 
            {
                cout << "No Pokemon was found." << endl;
            }
            break;
    }
}

// CatchMenu
// Gets the rarity of pokemon that the user wants
int Game::CatchMenu()
{
    int rarity = 0;

    // Makes sure the user gives a number within range
    while (rarity < 1 || rarity > 3)
    {
        cout << "What rarity of Pokemon would you like to catch?:" << endl;
        cout << "1. Common (High Probability)" << endl;
        cout << "2. Uncommon (Normal Probability)" << endl;
        cout << "3. Ultra Rare (Extremely Low Probability)" << endl;
        cin >> rarity;
    }

    return rarity;
}

// FoundPokemon
// Randomly gets the pokemon of the rarity given
// Also changes their CP to be somewhere below their max
Pokemon Game::FoundPokemon(int rarity)
{
    // Helps converting the random numbers into percentages
    int const percent = 100;
    Pokemon randPoke;
    bool found = false;
    int randCP = 0;
    int newCP = 0;
    int loopNum = 0;
    int counter = 0;

    loopNum = rand() % TOTAL_POKEMON;

    // Loops through pokedex until it reaches the random number
    while (found == false)
    {
        for (int i = 0; i < TOTAL_POKEMON; i++)
        {
            if (m_pokeDex[i].GetRarity() == rarity)
            {
                counter++;
                // Variables used to track whether the program 
                // has interated enough to reach the rand number
                if (loopNum == counter)
                {
                    found = true;
                    randPoke = m_pokeDex[i];
                }
            }
        }
    }

    randCP = (rand() % (MAX_FIND - MIN_FIND + 1)) + MIN_FIND;
    // Equation to get the new CP that is a 30-50% decrease of the maxCP
    newCP = randPoke.GetCP() - (randPoke.GetCP() * (double(randCP) / double(percent)));
    randPoke.SetCP(newCP);
    cout << "You found a " << randPoke.GetName() << endl;
    AddPokemon(randPoke);
    return randPoke;
}

// AddPokemon
// Adds the given pokemon to the team array
void Game::AddPokemon(Pokemon newPokemon)
{
    bool emptyChecker = true;
    bool spotFound = false;
    int firstSpot = -1;
    int fullChecker = 0; // Tracker for each full space
    bool pokemonAdded = false;
    int i = 0;

    // Loops through m_team to find an empty space
    while (i < NUM_TEAM && spotFound == false)
    {
        // Loops through every pokemon in the pokedex to check if there are any pokemon in the team
        for (int finder = 0; finder < TOTAL_POKEMON; finder++)
        {
            // If any pokemon is found in the team slot, then marks it as not empty
            if (m_team[i].GetName() == m_pokeDex[finder].GetName())
            {
                emptyChecker = false;
            }
        }

        // If the loop doesn't find any pokemon in the team slot, then it is empty
        if (emptyChecker == true)
        {
            // We signal that to the function and exit the loop
            firstSpot = i;
            spotFound = true;
        } else 
        {
            fullChecker++;
        }

        i++;
        emptyChecker = true;
    }
    
    // Checks that the team isn't full
    if (fullChecker != NUM_TEAM)
    {
        // We take the empty slot and add the Pokemon in
        if (firstSpot >= 0 && firstSpot < NUM_TEAM)
        {
            m_team[firstSpot] = newPokemon;
            cout << m_team[firstSpot].GetName() << " added to your team!" << endl;
        }
    } else
    {
        // Goes through the team and replaces the first Pokemon with the lowerCP
        for (int x = 0; x < NUM_TEAM; x++)
        {
            if (m_team[x].GetCP() < newPokemon.GetCP() && pokemonAdded == false)
            {
                m_team[x] = newPokemon;
                pokemonAdded = true;
                cout << m_team[x].GetName() << " added to your team!" << endl;
            }
        }

        // If the new Pokemon has the lowest CP, then it will not be added
        if (pokemonAdded == false)
        {
            cout << "Your team is full." << endl;
        }
    }   
}

// TeamSize
// Finds how many pokemon is in the team array
int Game::TeamSize()
{
    int teamSize = 0;
    int i = 0;
    bool emptyChecker = true;

    // Loops through m_team
    while (i < NUM_TEAM)
    {
        // Checks each spot in the team for every pokemon
        for (int finder = 0; finder < TOTAL_POKEMON; finder++)
        {
            // If it finds a match with any pokemon in the pokedex, then considers that slot full
            if (m_team[i].GetName() == m_pokeDex[finder].GetName())
            {
                emptyChecker = false;
            }
        }

        // When a spot in the team is full, then increases the team size
        if (emptyChecker == false)
        {
            teamSize++;
        }

        i++;
        emptyChecker = true;
    }

    return teamSize;
}

// Goes through the team array and prints each pokemon's info
void Game::DisplayTeam()
{
    int teamSize = TeamSize();
    int emptyChecker = true;

    if (teamSize > 0)
    {
        // Iterates through the team and prints out each Pokemon with proper spacing
        for (int i = 0; i < NUM_TEAM; i++)
        {
            // Checks to make sure that the spot in team isn't empty
            for (int x = 0; x < TOTAL_POKEMON; x++)
            {
                if (m_team[i].GetName() == m_pokeDex[x].GetName())
                {
                    emptyChecker = false;
                }
            }
            
            // If the space has a pokemon then we can display them, otherwise we skip over it
            if (emptyChecker == false)
            {
                cout << i + 1 << "." << setw(NAME_WIDTH) << m_team[i].GetName() 
                << setw(NUM_WIDTH) << m_team[i].GetCP() << endl;
            }
            emptyChecker = true;
        }
    } else
    {
        cout << "You have no team yet. Search for a Pokemon?" << endl;
    }
}

// FindPokemon
// With the given pokemon name, finds the pokemon's match in pokedex
int Game::FindPokemon(string name)
{

    // Goes through the whole array and sees if there are any matches
    for (int i = 0; i < TOTAL_POKEMON; i++)
    {
        if (name == m_pokeDex[i].GetName())
        {
            // If it finds a match then returns the index
            return i;
        }
    }

    // If the whole pokedex is searched through without finding a match, then ends the function
    return -1;
}

// TrainPokemon
// Takes whatever pokemon the user picks and trains them
void Game::TrainPokemon()
{
    int teamSize = TeamSize();
    int choice = -1;
    int pokeIndex = -1;

    // Checks that the user has a team
    if (teamSize > 0)
    {
        cout << "Which of your pokemon would you like to use?:" << endl;
        DisplayTeam();

        // Checks that the user picked a valid number with the team range
        while (choice < 0 || choice > teamSize)
        {
            cin >> choice;

            if (choice < 0 || choice > teamSize)
            {
                cout << "Please pick a pokemon from your team." << endl;
            }
        }

        // Once a pokemon has been picked then we search for that pokemon's max CP
        pokeIndex = FindPokemon(m_team[choice - 1].GetName());

        // Once maxCP is found, then we can run the Train function to train the pokemon
        m_team[choice - 1].Train(m_pokeDex[pokeIndex].GetCP());

        cout << "Your " << m_team[choice - 1].GetName() << "\'s CP goes up!" << endl;

    } else 
    {
        cout << "You have no team yet. Search for a Pokemon?" << endl;
    }
}

// BattlePokemon
// Simulates a battle with the user's pokemon
void Game::BattlePokemon()
{
    Pokemon Chosen;
    Pokemon enemyPoke;
    int teamSize = TeamSize();
    int choice = -1;
    int randNum = rand() % TOTAL_POKEMON;
    int randCP = 0;
    int faintedCP = 0;

    if (teamSize > 0)
    {
        enemyPoke = m_pokeDex[randNum];

        // Sets the enemy CP at a random CP within the range
        randCP = rand() % (enemyPoke.GetCP() + ENEMY_ADD);
        enemyPoke.SetCP(randCP);

        cout << "You are going to fight a " << enemyPoke.GetName() << endl;
        cout << "The enemy has a CP of " << enemyPoke.GetCP() << endl;

        cout << "Which of your pokemon would you like to use?:" << endl;
        DisplayTeam();

        // Checks that the user picked a valid number with the team range
        while (choice < 0 || choice > teamSize)
        {
            cin >> choice;

            if (choice < 0 || choice > teamSize)
            {
                cout << "Please pick a pokemon from your team." << endl;
            }
        }
        // Sets up the Pokemon's to get ready for battle
        Chosen = m_team[choice - 1];

        // Compares the CP
        if (Chosen.GetCP() > enemyPoke.GetCP())
        {
            cout << Chosen.GetName() << " won the battle!" << endl;
        } else 
        {
            cout << Chosen.GetName() << " lost the battle and fainted." << endl;
            cout << "You should replace it." << endl;
            Chosen.SetCP(faintedCP);
            m_team[choice - 1] = Chosen;
        }
    } else 
    {
        cout << "You have no team yet. Search for a Pokemon?" << endl;
    }
}

// Start
// Main function that starts the game
void Game::Start()
{
    LoadFile();
    MainMenu();
}
