// Name: Kevin Weng
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Date: 9/22/23
// Ranger implementation for term project


#include <iostream>
#include "Ranger.hpp"
#include <cctype>

/**
    Default constructor.
    Default-initializes all private members. Default character name: "NAMELESS". 
    Booleans are default-initialized to False. 
*/
// Constructor
Ranger::Ranger() {
    Character();
    arrows_ = {};
    affinities_ = {};
    has_companion_ = false;
}

// Parameterized Constructor
/**
   Parameterized constructor.
  @param      : The name of the character (a const string reference)
  @param      : The race of the character (a const string reference)
  @param      : The character's vitality (an integer). Default to 0
  @param      : The character's max armor level (an integer). Default to 0
  @param      : The character's level (an integer). Default to 0
  @param      : A flag indicating whether the character is an enemy. Default to false
  @param      : A vector of arrows. Valid arrow types are: [WOOD, FIRE, WATER, POISON, BLOOD]
                Lowercase valid arrow types are retained but converted to uppercase.
                Invalid arrows are those with non-positive quantities or invalid types.
                If the vector contains invalid arrows, those arrows are discarded. 
                Default to empty vector
  @param      : A vector of affinities. Valid Affinities: [FIRE, WATER, POISON, BLOOD]
                String inputs can be in lowercase, but must be converted to uppercase.
                If the vector contains invalid affinities, those affinities are discarded.
                Default to empty vector
  @param      : A flag indicating whether the character is able to recruit an animal companion. 
                Default to false
  @post       : The private members are set to the values of the corresponding parameters
*/
Ranger::Ranger(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, const std::vector<Arrows>& arrows, const std::vector<std::string>& affinities, bool has_companion):
Character(name, race, vitality, armor, level), has_companion_{has_companion}
{
    for (int i = 0; i < arrows.size(); i++) {
        addArrows(arrows[i].type_, arrows[i].quantity_);
    }

    for (int i = 0; i < affinities.size(); i++) {
        addAffinity(affinities[i]);
    }
}

// SETTERS
/**
    @param    : a reference to a boolean indicating whether the character is able to recruit 
                an animal companion
    @post     : sets the private member variable to the value of the parameter.
**/
void Ranger::setCompanion(const bool& has_companion) {
    has_companion_ = has_companion;
}

/**
    @param    : a reference to string representing the arrow type
    @param    : a reference to an integer quantity
    @post     : If the character already has that type of arrow, the quantity in the vector 
                is updated. If not, the arrow is added to the vector. 
                Valid arrow types are: [WOOD, FIRE, WATER, POISON, BLOOD]
                Lowercase valid arrow types are retained but converted to uppercase.
                Quantity of arrows must be greater than 0
                Invalid arrows are those with non-positive quantities or invalid types.
                If the arrows are invalid, they are not added.
    @return   : True if the arrows were added successfully, false otherwise
**/
bool Ranger::addArrows(const std::string& arrow_type, int quantity) { // checks to see if it contains any numbers, if it does, it'll be invalid and if it doesn't, it'll convert it to uppercase
    std::string empty_arrow = "";
    for (int i = 0; i < arrow_type.length(); i++) {
        if (!isalpha(arrow_type[i])) {
            return false;
        } else {
            empty_arrow += char(toupper(arrow_type[i]));
        }
    }
    
    if ((empty_arrow != "WOOD" && empty_arrow != "FIRE" && empty_arrow != "WATER" && empty_arrow != "POISON" && empty_arrow != "BLOOD") || quantity <= 0) {
        return false;
    }

    for (int i = 0; i < arrows_.size(); i++) { // loops through the vector and checks if the arrow is equal to the type, if it is, how ever many arrows will be added to the quantity variable
        if (empty_arrow == arrows_[i].type_) {
            arrows_[i].quantity_ += quantity;
            return true;
        }
    }

    Arrows arr1;
    arr1.quantity_ = quantity;
    arr1.type_ = empty_arrow;
    arrows_.push_back(arr1);
    return true;
}

/**
    @param    : a reference to string representing the arrow type
    @post     : If the character has the listed arrow AND enough arrows to fire one, 
                the quantity of remaining arrows in the vector is updated.
                Lowercase valid arrow types are accepted but converted to uppercase.
                If firing the last arrow, simply decrement the quantity to 0.
    @return   : True if the character had the listed arrow AND enough arrows, False otherwise.
**/
bool Ranger::fireArrow(const std::string& arrows) { // converts the input into uppercase and sets it to a temporary variable
    std::string empty_arrow = "";
    for (int i = 0; i < arrows.length(); i++) {
        if (isalpha(arrows[i])) {
            empty_arrow += char(toupper(arrows[i]));
        }
    }

    for (int i = 0; i < arrows_.size(); i++) { // loops through the vector and if the index is equal to whatever the user inputted, and the quantity is greater than 0, it'll subtract an arrow from that index's arrow quantity
        if (arrows_[i].type_ == empty_arrow && arrows_[i].quantity_ > 0) {
             arrows_[i].quantity_--;
             return true;
        }
    }
    return false;
}

/**
    @param  : a reference to string representing an affinity 
    @post   : If the affinity does not already exist in the vector, add it to the vector.
              Valid Affinities: [FIRE, WATER, POISON, BLOOD] 
              String inputs can be in lowercase, but must be converted to uppercase when 
              setting the variable.
              There should be no duplicate affinities.
              If the affinity is invalid, it is NOT added.
    @return : True if the affinity was added successfully, false otherwise
**/
bool Ranger::addAffinity(const std::string& affinities) { // checks to see if there is numbers in the input, if there is, it'll make it invalid, if it isn't, it'll convert it to uppercase and store it in a temporary variable
    std::string empty_affinity = "";
    for (int i = 0; i < affinities.length(); i++) {
        if (!isalpha(affinities[i])) {
            return false;
        } else {
            empty_affinity += char(toupper(affinities[i]));
        }
    }

    if (empty_affinity == "FIRE" || empty_affinity == "WATER" || empty_affinity == "POISON" || empty_affinity == "BLOOD") { // 
        for (int i = 0; i < affinities_.size(); i++) {
            if (affinities_[i] == empty_affinity) {
                return false;
            }
        }
        affinities_.push_back(empty_affinity);
        return true;
    } else {
        return false;
    }
}

// GETTERS
/**
  @return     : a vector of the Character's arrows
**/
std::vector<Arrows> Ranger::getArrows() const {
    return arrows_;
}

/**
  @return     : a vector of the Character's affinities
**/
std::vector <std::string> Ranger::getAffinities() const {
    return affinities_;
}

/**
    @return   : a boolean indicating whether the character is able to recruit an animal companion
**/
bool Ranger::getCompanion() const {
    return has_companion_;
}

