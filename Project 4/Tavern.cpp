// NAME: KEVIN WENG
// EMAIL: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// DATE: 10/26/23
// This is the Tavern implementation for term project

#include "Tavern.hpp"
#include "Barbarian.hpp"
#include "Mage.hpp"
#include "Ranger.hpp"
#include "Scoundrel.hpp"
#include "Character.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}



/** 
    @param:   A reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character* a_character)
{
  if(add(a_character))
  {
    level_sum_ += a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
}

/** @param:   A reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}

/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive integer
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/

Tavern::Tavern(const std::string& file) {
  
  std::ifstream read(file); // Read file

  if (!read.is_open()) {
    std::cout << "ERROR: file can't be opened" << std::endl;
  }

  std::string str;
  std::getline(read, str);

  std::string name, race, subclass, main, offhand, school_faction, affinity;
  int level, vitality, armor;
  bool enemy, summon, disguise, enraged;
  std::string temp;

  Character* characters = nullptr; // pointer that points to nullptr
  std::string parse = ""; 
  while (std::getline(read, parse)) {
    std::stringstream input_string(parse);
    
    getline(input_string, name, ','); // grabs the line until ',' and stores their corresponding value to its variable, stores in 'name' in this case
    getline(input_string, race, ',');
    getline(input_string, subclass, ',');
    
    getline(input_string, temp, ',');
    std::istringstream(temp) >> level;  

    getline(input_string, temp, ',');
    std::istringstream(temp) >> vitality;

    getline(input_string, temp, ',');
    std::istringstream(temp) >> armor;

    getline(input_string, temp, ',');
    std::istringstream(temp) >> enemy;


    getline(input_string, main, ',');
    std::vector <Arrows> temp_arrows; // empty vector
    std::istringstream newtemp(main);
    while(getline(newtemp, temp, ';')) { // Grabs the line stopping at the ';'
      std::istringstream newvariable(temp);
      std::string newArrowType;
      int newArrowQuantity;

      newvariable >> newArrowType >> newArrowQuantity;
      Arrows newArrows;
      newArrows.type_ = newArrowType;
      newArrows.quantity_ = newArrowQuantity;

      temp_arrows.push_back(newArrows); // 
    }

    getline(input_string, offhand, ',');
    getline(input_string, school_faction, ',');

    getline(input_string, temp, ',');
    std::istringstream(temp) >> summon;

    getline(input_string, affinity, ',');
    std::vector <std::string> empty_vector;
    std::string empty_string = "";

   std::istringstream affinities_stream(affinity);
    while (std::getline(affinities_stream, parse, ';')) {
      empty_vector.push_back(parse); // Pushing whatever you stored in parse into the new vector
    }

    
    for (int i = 0; i < affinity.length(); i++) { // Loops through the length of the word
      if (affinity[i] != ';') { // If the index of infinity does not equal to ';
        empty_string += affinity[i]; // Add whatever the value is into the empty string
        
      } else if (affinity[i] == ';' || affinity[i] == affinity.length()-1) { // checks to see if the index is a ';' or the last letter
        empty_vector.push_back(empty_string); // It will push back whatever it has in the empty_string into the empty vector
        empty_string = ""; // Resets the string to an empty
      }
    }
    
    getline(input_string, temp, ',');
     std::istringstream(temp) >> disguise;
    
    
    getline(input_string, temp, ',');
    std::istringstream(temp) >> enraged;


     if (subclass == "BARBARIAN") {
      characters = new Barbarian(name, race, vitality, armor, level, enemy, main, offhand, enraged);
     } else if (subclass == "MAGE") {
      characters = new Mage(name, race, vitality, armor, level, enemy, school_faction, main, summon);
     } else if (subclass == "SCOUNDREL") {
      characters = new Scoundrel(name, race, vitality, armor, level, enemy, main, school_faction, disguise);
    } else if (subclass == "RANGER") {
      characters = new Ranger(name, race, vitality, armor, level, enemy, temp_arrows, empty_vector, summon);
    }
    enterTavern(characters);
  }
}

/**
    @post: For every character in the tavern, displays each character's information
*/

void Tavern::displayCharacters() {
  for (int i = 0; i < getCurrentSize(); i++) { // Loops through the current size of the array
    items_[i] -> display(); // Calls the display function for each of the index in items_.
  }
}

/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information

*/

void Tavern::displayRace(const std::string& race) {
  for (int i = 0; i < getCurrentSize(); i++) { // Loops through the current size of the array
    if (items_[i] -> getRace() == race) { // See if the index race is equal to the race being entered
      items_[i] -> display(); // It will call the display function if it is
    }
  }
}
/**
    @post: Every character in the tavern eats a tainted stew.
*/

void Tavern::taintedStew() {
  for (int i = 0; i < getCurrentSize(); i++) { // Loops through the current size of the array
    items_[i] -> eatTaintedStew(); // Checks each index and calls the eatTaintedStew function
  }
}
