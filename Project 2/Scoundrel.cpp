// Name: Kevin Weng
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Date: 9/22/23
// Scoundrel implementation for term project


#include <iostream>
#include "Scoundrel.hpp"
#include <cctype>

/**
    Default constructor.
    Default-initializes all private members. 
    Default character name: "NAMELESS". Booleans are default-initialized to False. 
    Default dagger: WOOD. Default faction: "NONE". 
*/
// Constructor
Scoundrel::Scoundrel() {
    Character();
    dagger_ = WOOD;
    has_disguise_ = false;
    faction_ = "NONE";
}

/**
    Parameterized constructor.
    @param      : The name of the character (a const string reference)
    @param      : The race of the character (a const string reference)
    @param      : The character's vitality (an integer). Default to 0
    @param      : The character's max armor level (an integer). Default to 0
    @param      : The character's level (an integer). Default to 0
    @param      : A flag indicating whether the character is an enemy. Default to false.
    @param      : The character's dagger type (a const string reference).
                  String inputs can be in lowercase, but must be converted to 
                  uppercase when setting the dagger enum. Default to WOOD
    @param      : The character's Faction (a const string reference). 
                  Valid Factions: [CUTPURSE, SHADOWBLADE, SILVERTONGUE] 
                  String inputs can be in lowercase, but must be converted to 
                  uppercase when setting the variable. Default to "NONE"
    @param      : A flag indicating whether the character has a disguise. Default to false
    @post       : The private members are set to the values of the corresponding 
                  parameters.
                 If the dagger type is not provided or invalid, the variable should 
                  be set to WOOD. 
                 If the Faction is not provided or invalid, the variable should be 
                  set to "NONE". 
*/
// Paramterized Constructor
Scoundrel::Scoundrel(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, std::string dagger, std::string faction, bool disguise):
Character(name, race, vitality, armor, level, enemy), faction_{faction}, has_disguise_{disguise}
{
    setDagger(dagger);

    if (!setFaction(faction)) {
        faction_ = "NONE";
    }
}

// SETTERS
/**
   @param     : a reference to a string representing the dagger type
   @post      : sets the private member variable to the value of the parameter. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the dagger type is not valid (i.e, is one of the following: 
                [WOOD, BRONZE, IRON, STEEL, MITHRIL, ADAMANT, RUNE]), 
                the variable should be set to WOOD. 
**/
void Scoundrel::setDagger(const std::string& dagger) { // converts the input to uppercase and set it to a temporary variable
    std::string empty_dagger;
    for (int i = 0; i < dagger.length(); i++) {
        if (isalpha(dagger[i])) {
            empty_dagger += char(toupper(dagger[i]));
        }
    }

    if (empty_dagger == "WOOD") { // if the value stored in the temporary variable is these, it'll store it to the private dagger variable
        dagger_ = WOOD;
    } else if (empty_dagger == "BRONZE") {
        dagger_ = BRONZE;
    } else if (empty_dagger == "IRON") {
        dagger_ = IRON;
    } else if (empty_dagger == "STEEL") {
        dagger_ = STEEL;
    } else if (empty_dagger == "MITHRIL") {
        dagger_ = MITHRIL;
    } else if (empty_dagger == "ADAMANT") {
        dagger_ = ADAMANT;
    } else if (empty_dagger == "RUNE") {
        dagger_ = RUNE;
    } else {
        empty_dagger = WOOD;
    }
}

/**
    @param    : a reference to a string representing the character's Faction
    @post     : sets the private member variable to the value of the parameter. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the provided faction is not one of the following: 
               [NONE, CUTPURSE, SHADOWBLADE, SILVERTONGUE], 
               do nothing and return false.
    @return   : true if setting the variable was successful, false otherwise.
**/
bool Scoundrel::setFaction(const std::string& faction) { // converts the input to uppercase and set it to a temporary variable
    std::string empty_faction = "";
    for (int i = 0; i < faction.length(); i++) {
        if (isalpha(faction[i])) {
            empty_faction += char(toupper(faction[i]));
        }
    }

    if (empty_faction == "NONE" || empty_faction == "CUTPURSE" || empty_faction == "SHADOWBLADE" || empty_faction == "SILVERTONGUE") { // if the value stored in the temporary variable, it'll store the value to the private faction variable
        faction_ = empty_faction;
        return true;
    } else {
        return false;
    }
}

/**
  @param  : a reference to boolean
  @post   : sets the private member variable indicating whether the character has a disguise
**/
void Scoundrel::setDisguise(const bool& disguise) {
    has_disguise_ = disguise;
}

// GETTERS
/**
  @return     : the string indicating the character's dagger type
**/
std::string Scoundrel::getDagger() const { // if the private dagger variable stores any of these, it'll return the strings depending on what it is
    if (dagger_ == WOOD) {
        return "WOOD";
    } else if (dagger_ == BRONZE) {
        return "BRONZE";
    } else if (dagger_ == IRON) {
        return "IRON";
    } else if (dagger_ == STEEL) {
        return "STEEL";
    } else if (dagger_ == MITHRIL) {
        return "MITHRIL";
    } else if (dagger_ == ADAMANT) {
        return "ADAMANT";
    } else if (dagger_ == RUNE) {
        return "RUNE";
    }
    return "NONE";
}

/**
  @return  : the string indicating the character's Faction
**/
std::string Scoundrel::getFaction() const {
    return faction_;
}

/**
  @return  : the visual aid flag
**/
bool Scoundrel::hasDisguise() const {
    return has_disguise_;
}