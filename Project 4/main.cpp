// Name: KEVIN WENG
// Date: 10/19/23
// Email: KEVIN.WENG35@MYHUNTER.CUNY.EDU
// Project test file

#include <iostream>
using namespace std;
#include "Tavern.hpp"
#include "Barbarian.hpp"
#include "Mage.hpp"
#include "Ranger.hpp"
#include "Scoundrel.hpp"

int main () {
    Tavern test_dummy("characters.csv");
    test_dummy.displayCharacters();
}