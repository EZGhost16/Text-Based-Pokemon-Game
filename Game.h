#ifndef GAME_H
#define GAME_H
#include "Pokemon.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//**Constants**
const int NUM_TEAM = 4; //Number of Pokemon on each team
const int TOTAL_POKEMON = 151; //Total Pokemon in PokeDex
const int COMMON = 45; //Less than this to find a common Pokemon - 45%
const int UNCOMMON = 25; //Less than this to find an uncommon Pokemon 25%
const int ULTRA = 1; //Less than this to find an ultra rare Pokemon 1%
const int MAX_FIND = 50; //Maximum reduction when finding a new Pokemon
const int MIN_FIND = 30; //Minimum reduction when finding a new Pokemon
const int ENEMY_ADD = 200; //Enemy will have 0 - max CP + 200 for their CP
const int NAME_WIDTH = 12; //Used to set the column width of the name
const int NUM_WIDTH = 6; //Used to set the column width of num and CP

class Game {
public:
  // Name: Game Constructor
  // Desc - Sets m_filename based on string passed
  // Preconditions - Input file passed
  // Postconditions - m_filename updated
  Game(string filename);
  // Name: LoadFile
  // Desc - Opens file and reads in each Pokemon into m_PokeDex
  // Preconditions - Input file passed and populated with Pokemon
  // Postconditions - m_pokeDex populated with Pokemon
  void LoadFile();
  // Name: DisplayPokeDex
  // Desc - Display all Pokemon in the m_pokeDex
  // Preconditions - m_pokeDex populated with Pokemon
  // Postconditions - None
  void DisplayPokeDex();
  // Name: MainMenu
  // Desc - Displays main menu
  // Preconditions - m_pokeDex populated
  // Postconditions - Keeps calling until quit chosen
  void MainMenu();
  // Name: CatchPokemon
  // Desc - Main function for catching pokemon. Does the following:
  //        1. Calls CatchMenu and stores rarity chosen
  //        2. Randomly chooses a number between 0 - 99
  //        3. If random number is less than rarity, calls FoundPokemon
  //        4. If random number is greater than rarity, indicates none found
  //        5. Call AddPokemon if new Pokemon is caught
  // Preconditions - m_pokeDex has maximum CP for Pokemon
  // Postconditions - After random Pokemon of that rarity is chosen,
  //                  this function reduces the CP of between 30-50%
  //                  and adds to m_team
  void CatchPokemon();
  // Name: CatchMenu
  // Desc - User chooses which rarity of Pokemon to try and catch
  // Preconditions - m_pokeDex has rarities of 1-3
  // Postconditions - Returns choice of 1-3
  int CatchMenu();
  // Name: FoundPokemon
  // Desc - Based on rarity passed in, randomly chooses one Pokemon
  //        from the m_pokeDex, updates the CP, and adds to m_team
  // Preconditions - m_pokeDex has maximum CP for Pokemon
  // Postconditions - After random Pokemon of that rarity is chosen,
  //                  this function reduces the CP of between 30-50%
  //                  and adds to m_team
  Pokemon FoundPokemon(int rarity);
  // Name: AddPokemon
  // Desc - Figures out where to insert newly found Pokemon
  //        If m_team has opening, inserts into first open slot
  //        If m_team is full, inserts into first slot with lower CP
  //        If m_team is full, and new Pokemon has lower CP, does not insert
  //        Tells user if not inserted
  // Preconditions - None
  // Postconditions - New Pokemon is added to m_team if possible
  //                  or user is notified that there is no room
  void AddPokemon(Pokemon newPokemon);
  // Name: TeamSize
  // Desc - Iterates through m_team to see how many team members exist
  // Preconditions - m_team exists
  // Postconditions - Returns 0 if empty otherwise up to 4
  int TeamSize();
  // Name: DisplayTeam
  // Desc - Iterates through m_team to display information about team
  // Preconditions - m_team exists
  // Postconditions - None
  void DisplayTeam();
  // Name: FindPokemon
  // Desc - Iterates through m_pokeDex to see if matching name exists
  //        Returns index if found else -1
  // Preconditions - m_pokeDex exists
  // Postconditions - Returns index of match, else -1
  int FindPokemon(string name);
  // Name: TrainPokemon
  // Desc - If m_team size is 0. If 0, tells user and returns to main menu
  //        If m_team size > 0, displays team (DisplayTeam)
  //        Asks user to chose one team member
  //        Calls Train on chosen team member and passes corresponding CP
  //             value from m_pokeDex (m_pokeDex holds max CP for all)
  // Preconditions - m_team and m_pokeDex exists
  // Postconditions - Calls Train on chosen team member
  void TrainPokemon();
  // Name: BattlePokemon
  // Desc - If m_team size is 0. If 0, tells user and returns to main menu
  //        If m_team size > 0, randomly chooses Pokemon to fight from
  //        m_pokeDex. Asks which team member to use in battle.
  //        Random enemy has a CP of 0 - max CP + 200.
  //        Compares CP for random enemy and team member.
  //        If team member wins, indicates and returns to main menu
  //        If team member loses, indicates, sets CP to 0, returns to menu
  // Preconditions - m_team exists
  // Postconditions - Either the player wins or team member's CP is set to 0
  void BattlePokemon();
  // Name: Start
  // Desc - Calls LoadFile then MainMenu
  // Preconditions - m_fileName is populated
  // Postconditions - Exits game when done running
  void Start();
private:
  Pokemon m_pokeDex[TOTAL_POKEMON]; //Master list of all Pokemon in game
  Pokemon m_team[NUM_TEAM]; //Users team of Pokemon
  string m_filename; //Name of the file passed from main
};
#endif

