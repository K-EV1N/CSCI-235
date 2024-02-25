// Name: KEVIN WENG
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Date:9/27/23
// This is the Tavern interface

#ifndef TAVERN_HPP
#define TAVERN_HPP
#include "ArrayBag.hpp"
#include "Character.hpp"
#include <iostream>

class Tavern : public ArrayBag <Character> {
    public:
    /**
    Default constructor.
    Default-initializes all private members. 
*/
        Tavern();

        // SETTERS

        // GETTERS
        /** 
    @return:  The integer level count of all the characters currently in the Tavern
 **/
        int getLevelSum() const;

        /** 
    @return:  The integer enemy count of the Tavern
 **/
        int getEnemyCount() const;

/** @param:   A const reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to the tavern (i.e. items_),                 false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count 
              if the character is an enemy.
 **/
        bool enterTavern(const Character& kevin_enter);

        /** @param:   A const reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from the tavern (i.e. items_),               false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count
              if the character is an enemy.
 **/
        bool exitTavern(const Character& kevin_exit);

/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Computes the average level of the Tavern rounded to the NEAREST integer.
 **/
        int calculateAvgLevel() const;

        /** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Computes the enemy percentage of the Tavern rounded up to 2 decimal places.
 **/
        double calculateEnemyPercentage() const;

        /** 
    @param:   A const reference to a string representing a character Race with value in 
              ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]
    @return:  An integer tally of the number of characters in the Tavern of the given race. 
              If the argument string does not match one of the expected race values, 
              the tally is zero. NOTE: no pre-processing of the input string necessary, only                  uppercase input will match.
 **/
        int tallyRace(const std::string& race);

        /**
@post:      Outputs a report of the characters currently in the tavern in the form:
            "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average             level is: [x] \n[x]% are enemies.\n"
            Note that the average level should be rounded to the NEAREST integer, and the enemy             percentage should be rounded to 2 decimal places.

            Example output: 
            Humans: 3
            Elves: 5
            Dwarves: 8
            Lizards: 6
            Undead: 0

            The average level is: 7
            46.67% are enemies.
*/
        void tavernReport();

    private:
        int all_character_levels_;
        int enemy_count_;

};

#endif