/****************************
** File: Pokemon.cpp
** Project: CMSC 202 Project 2, Spring 2024
** Author: Eden Zhang
** Date: 3/03/2024
** Section: 30/34
** E-Mail: ezhang1@umbc.edu
**
**  This is the cpp file for the Pokemon.h file. 
**  Holds most of the helper functions that are necessary for 
**  Game.cpp to use in the mechanics of the game.
**
************************************************/
#include "Pokemon.h"

// Pokemon()
// Empty constructor for creating pokemon objects
Pokemon::Pokemon()
{
    
}

// Main constructor of pokemon objects with all their info
Pokemon::Pokemon(int num, string name, int cp, int rarity)
{
    m_num = num;
    m_name = name;
    m_CP = cp;
    m_rarity = rarity;
}

// Getter function for the CP of the Pokemon
int Pokemon::GetCP()
{
    return m_CP;
}

// Getter function for the rarity of the Pokemon
int Pokemon::GetRarity()
{
    return m_rarity;
}

// Getter function for the name of the Pokemon
string Pokemon::GetName()
{
    return m_name;
}

// Getter function for the number of the Pokemon
int Pokemon::GetNum()
{
    return m_num;
}

// Setter function for the rarity of the pokemon
void Pokemon::SetRarity(int newRarity)
{
    m_rarity = newRarity;
}

// Setter function for the name of the pokemon
void Pokemon::SetName(string newName) 
{
    m_name = newName;
}

// Setter function for the cp of the pokemon
void Pokemon::SetCP(int newCP)
{
    m_CP = newCP;
}

// Function that increases the CP of the Pokemon by Train_Value 
// up to a maxCP
void Pokemon::Train(int maxCP)
{
    // Only does anything if the current CP is less than the max CP
    if (m_CP < maxCP)
    {
        m_CP += TRAIN_VALUE;
        // After training, checks to make sure that the current CP isn't over the max
        if (m_CP > maxCP)
        {
            m_CP = maxCP;
            cout << "Your Pokemon has reached its maximum CP." << endl;
        }
    } else
    {
        cout << "Your Pokemon has reached its maximum CP." << endl;
    }
}
