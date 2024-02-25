#include "Character.hpp"
#include <iostream>
using namespace std;

int main() {
    Character Ron("you123", "elf", -3, 2, -3, true);
    cout << Ron.getName() << endl;
    cout << Ron.getRace() << endl;
    cout << Ron.getVitality() << endl;
    cout << Ron.getArmor() << endl;
    cout << Ron.getLevel() << endl;
    cout << Ron.isEnemy() << endl;


}