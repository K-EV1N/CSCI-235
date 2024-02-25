// Name: KEVIN WENG
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Date: 9/27/23
// This is the Tavern implementation for term project

#include "Tavern.hpp"
#include "ArrayBag.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <cmath>


/**
    Default constructor.
    Default-initializes all private members. 
*/

Tavern::Tavern() { // default constructor
    ArrayBag(); // Initializes the private member variables to default values
    all_character_levels_ = 0;
    enemy_count_ = 0;   
}

/** @param:   A const reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to the tavern (i.e. items_), false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count 
              if the character is an enemy.
 **/

bool Tavern::enterTavern(const Character& kevin_enter) { // Adds the character level, add the enemy count if it's an enemy when the character gets added
    if (add(kevin_enter)) {
            all_character_levels_ += kevin_enter.getLevel(); // If a character gets added, it will add the character level to the private member variable all_character_levels
            if (kevin_enter.isEnemy()) { // If the character is an enemy, the private member variable enemy_count_ will increment by 1
                enemy_count_++;
            }
            return true;
        }
    return false;
}

/** @param:   A const reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from the tavern (i.e. items_), false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count
              if the character is an enemy.
 **/

bool Tavern::exitTavern(const Character& kevin_exit) { // Removes the character level, remove the enemy count if it was an enemy, when the character gets removed
    if (remove(kevin_exit)) {
        all_character_levels_ -= kevin_exit.getLevel(); // If a character gets removed, it will remove it's levels from all_character_levels
        if (kevin_exit.isEnemy()) { // If the charaacter is an enemy, enemy_count_ will decrement by 1
            enemy_count_--;
        }
        return true;
    }
    return false;
}


// GETTERS
/** 
    @return:  The integer level count of all the characters currently in the Tavern
 **/

int Tavern::getLevelSum() const {
    return all_character_levels_;
}

/** 
    @return:  The integer enemy count of the Tavern
 **/

int Tavern::getEnemyCount() const {
    return enemy_count_;
}

/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Computes the average level of the Tavern rounded to the NEAREST integer.
 **/

int Tavern::calculateAvgLevel() const { // Calculates the average character levels
    double level = 0.0;

    level = round(double(all_character_levels_) / getCurrentSize());
    return level;
}

/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Computes the enemy percentage of the Tavern rounded up to 2 decimal places.
 **/

double Tavern::calculateEnemyPercentage() const { // Calcuate the average enemy percentage
    double enemy_percent = 0.0;
    double value = 0.0;

    enemy_percent = (double(enemy_count_) / getCurrentSize());
    value = (std::ceil((enemy_percent * 10000)) / 100.0);

    return value;
}

/** 
    @param:   A const reference to a string representing a character Race with value in 
              ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]
    @return:  An integer tally of the number of characters in the Tavern of the given race. 
              If the argument string does not match one of the expected race values, 
              the tally is zero. NOTE: no pre-processing of the input string necessary, only uppercase input will match.
 **/

int Tavern::tallyRace(const std::string& race) {
    int tallymark = 0;
    
        for (int i = 0; i < getCurrentSize(); i++) { // Loops through the array bag
            if (items_[i].getRace() == race) { // Checks each index of the character is equal to the valid character races, ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]. The tally will increase if they're equal
                tallymark++;
            }
    }   return tallymark; // If it's not equal to the valid races, it will just come to this line of code and return tallymark which has the value 0
}

/**
@post:      Outputs a report of the characters currently in the tavern in the form:
            "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n"
            Note that the average level should be rounded to the NEAREST integer, and the enemy percentage should be rounded to 2 decimal places.

            Example output: 
            Humans: 3
            Elves: 5
            Dwarves: 8
            Lizards: 6
            Undead: 0

            The average level is: 7
            46.67% are enemies.
*/

void Tavern::tavernReport() {
    std::cout << "Humans: " << tallyRace("HUMAN");
    std::cout << "\nElves: " << tallyRace("ELF");
    std::cout << "\nDwarves: " << tallyRace("DWARF");
    std::cout << "\nLizards: " << tallyRace("LIZARD");
    std::cout << "\nUndead: " << tallyRace("UNDEAD");
    std::cout << "\n\n";

    std::cout << "The average level is: " << calculateAvgLevel() << std::endl;
    std::cout << calculateEnemyPercentage() << "%" << " are enemies." << std::endl;
}