// Name: Kevin Weng
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Date: 9/22/23
// Barbarian implementation for term project


#include <iostream>
#include "Barbarian.hpp"
#include <cctype>

// Constructor
/**
    Default constructor.
    Default-initializes all private members. Default character name: "NAMELESS". 
    Booleans are default-initialized to False. 
    Default weapons: "NONE". 
*/
Barbarian::Barbarian() {
    Character();
    enraged_ = false;
    main_weapon_ = "NONE";
    secondary_weapon_ = "NONE";

}

/**
    Parameterized constructor.
    @param      : The name of the character (a const string reference)
    @param      : The race of the character (a const string reference)
    @param      : The character's vitality (an integer). Default to 0
    @param      : The character's max armor level (an integer). Default to 0
    @param      : The character's level (an integer). Default to 0
    @param      : A flag indicating whether the character is an enemy. Default to false
    @param      : The character's main weapon (a const string reference). 
                  String inputs can be in lowercase, but must be converted to uppercase 
                  when setting the variable. Only alphabetical characters are allowed.
                  Default to "NONE"
    @param      : The character's offhand weapon (a const string reference). 
                  String inputs can be in lowercase, but must be converted to uppercase 
                  when setting the variable. Only alphabetical characters are allowed.
                  Default to "NONE"
    @param      : A flag indicating whether the character is enraged. Default to false
    @post       : The private members are set to the values of the corresponding parameters. 
                : If the main and secondary weapons are not provided or invalid, the variables                    are set to "NONE".
*/
Barbarian::Barbarian(std::string name, std::string race, int vitality, int armor, int level, bool enemy, std::string main_weapon, std::string secondary_weapon, bool enraged):
Character(name, race, vitality, armor, level, enemy), main_weapon_{main_weapon}, secondary_weapon_{secondary_weapon}, enraged_{enraged}
{
    setMainWeapon(main_weapon);
    setSecondaryWeapon(secondary_weapon);
}

// SETTERS
/**
    @param    : a reference to a string representing the Character's main weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
                If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.
**/
bool Barbarian::setMainWeapon(const std::string& main_weapon) {
    std::string empty_weapon = "";
    for (int i = 0; i < main_weapon.length(); i++) {
        if (isalpha(main_weapon[i])) {
            empty_weapon += char(toupper(main_weapon[i]));
        }
    }

    if (empty_weapon != "") {
        main_weapon_ = empty_weapon;
        return true;
    }
    return false;
}

/**
    @param    : a reference to a string representing the Character's secondary weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
              : If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.
**/
bool Barbarian::setSecondaryWeapon(const std::string& secondary_weapon) { // converts the input value to uppercase and store it in a temporary variable
    std::string empty_secondary_weapon = "";
    for (int i = 0; i < secondary_weapon.length(); i++) {
        if (isalpha(secondary_weapon[i])) {
            empty_secondary_weapon += char(toupper(secondary_weapon[i]));
        } 
    }

    if (empty_secondary_weapon != "") {
        secondary_weapon_ = empty_secondary_weapon;
        return true;
    }
    return true;
}

/**
  @param      : a reference to a bool
  @post       : sets the private member variable to the value of the parameter.
**/
void Barbarian::setEnrage(const bool& enraged) {
    enraged_ = enraged;
}

/**
  @post   : sets the enraged variable to the opposite of what it was
**/
void Barbarian::toggleEnrage() {
    if (enraged_ == true) {
        enraged_ = false;
    } else {
        enraged_ = true;
    }
}

// GETTERS
/**
    @return   : a string of the Character's main weapon
**/
std::string Barbarian::getMainWeapon() const {
    return main_weapon_;
}

/**
   @return    : a string of the Character's secondary weapon
**/
std::string Barbarian::getSecondaryWeapon() const {
    return secondary_weapon_;
}

/**
  @return  : a boolean of whether the Character is enraged
**/
bool Barbarian::getEnrage() const {
    return enraged_;
}

