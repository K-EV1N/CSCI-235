// Name: KEVIN WENG
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Date: 9/29/23
// Project test file

#include <iostream>
using namespace std;
#include "Character.hpp"
#include "ArrayBag.hpp"
#include "Tavern.hpp"

int main() {

Character kevin("kevin", "HUMAN", 5, 6, 3, false);
Character nancy("nancy", "HUMAN", 5, 6, 3, false);
Character caily("caily", "HUMAN", 5, 3, 6, false);
Character jason("jason", "HUMAN", 5, 4, 3, false);
Tavern myTavern;


cout << "Name: " << kevin.getName() << endl;
cout << "Race: " << kevin.getRace() << endl;
cout << "Vitality: " << kevin.getVitality() << endl;
cout << "Armor: " << kevin.getArmor() << endl;
cout << "Level: " << kevin.getLevel() << endl;
cout << "\n";

cout << "Name: " << nancy.getName() << endl;
cout << "Race: " << nancy.getRace() << endl;
cout << "Vitality: " << nancy.getVitality() << endl;
cout << "Armor: " << nancy.getArmor() << endl;
cout << "Level: " << nancy.getLevel() << endl;
cout << "\n";

cout << "Name: " << caily.getName() << endl;
cout << "Race: " << caily.getRace() << endl;
cout << "Vitality: " << caily.getVitality() << endl;
cout << "Armor: " << caily.getArmor() << endl;
cout << "Level: " << caily.getLevel() << endl;
cout << "\n";

cout << "Name: " << jason.getName() << endl;
cout << "Race: " << jason.getRace() << endl;
cout << "Vitality: " << jason.getVitality() << endl;
cout << "Armor: " << jason.getArmor() << endl;
cout << "Level: " << jason.getLevel() << endl;
cout << "\n";

cout << "Enters Tavern: " << myTavern.enterTavern(kevin) << endl;
cout << "Enters Tavern: " << myTavern.enterTavern(nancy) << endl;
cout << "Enters Tavern: " << myTavern.enterTavern(caily) << endl;
cout << "Enters Tavern: " << myTavern.enterTavern(jason) << endl;
cout << "\n";

// cout << "Exits Tavern: " << myTavern.exitTavern(kevin) << endl;
// cout << "Exits Tavern: " << myTavern.exitTavern(nancy) << endl;
// cout << "Exits Tavern: " << myTavern.exitTavern(caily) << endl;
// cout << "Exits Tavern: " << myTavern.exitTavern(jason) << endl;

myTavern.tavernReport();
}