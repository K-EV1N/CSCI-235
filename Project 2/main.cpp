#include "Mage.hpp"
#include "Scoundrel.hpp"
#include "Ranger.hpp"
//#include "Barbarian.hpp"
#include <iostream>
using namespace std;

int main() {
/*
// Mage Test
    Mage kevin("testing123", "ELF", -3, 10, 5, false, "illusion", "wand", false);

cout << "Name: " << kevin.getName() << endl;
cout << "Race: " << kevin.getRace() << endl;
cout << "Vitality: " << kevin.getVitality() << endl;
cout << "Armor: " << kevin.getArmor() << endl;
cout << "Level: " << kevin.getLevel() << endl;
cout << "Enemy: " << kevin.isEnemy() << endl;
cout << "School: " << kevin.getSchool() << endl;
cout << "Weapon: " << kevin.getCastingWeapon() << endl;
cout << "Summon: " << kevin.hasIncarnateSummon() << endl;
*/

/*
// Scoundrel Test
Scoundrel kevin("testing123", "ELF", -3, 10, 5, false, "wood", "shadowblade", false);
cout << "Name: " << kevin.getName() << endl;
cout << "Race: " << kevin.getRace() << endl;
cout << "Vitality: " << kevin.getVitality() << endl;
cout << "Armor: " << kevin.getArmor() << endl;
cout << "Level: " << kevin.getLevel() << endl;
cout << "Enemy: " << kevin.isEnemy() << endl;
cout << "Dagger : " << kevin.getDagger() << endl;
cout << "Faction : " << kevin.getFaction() << endl;
cout << "Disguise : " << kevin.hasDisguise() << endl;
*/



/*// Ranger Test
vector <Arrows> arrow;
Arrows arr1;
arr1.type_ = "wood";
arr1.quantity_ = 2;
arrow.push_back(arr1);
for (int i = 0; i < arrow.size(); i++) {

} */


Ranger kevin("testing123", "ELF", -3, 10, 5, false);
cout << "Name: " << kevin.getName() << endl;
cout << "Race: " << kevin.getRace() << endl;
cout << "Vitality: " << kevin.getVitality() << endl;
cout << "Armor: " << kevin.getArmor() << endl;
cout << "Level: " << kevin.getLevel() << endl;
cout << "Enemy: " << kevin.isEnemy() << endl;
kevin.addArrows("fire", 5);
kevin.addArrows("blood", 1);
kevin.addAffinity("fire");
kevin.addAffinity("poison");
kevin.setCompanion(true);

vector<Arrows> arrow = kevin.getArrows();
for (int i = 0; i < arrow.size(); i++) {
    cout << "Arrow Quantity: " << arrow[i].quantity_ << endl;
    cout << "Arrow Type: " << arrow[i].type_ << endl;
}


for (string s: kevin.getAffinities()) {
    cout << "Affinity: " << s << endl;
}

kevin.fireArrow("FIRE");

vector<Arrows> updated_arrow = kevin.getArrows();


for (int i = 0; i < arrow.size(); i++) {
    cout << "Arrow Quantity: " << updated_arrow[i].quantity_ << endl;
    cout << "Arrow Type: " << updated_arrow[i].type_ << endl;
}

cout << "Vector of Arrows: ";


vector<Arrows> updated = kevin.getArrows();
for (int i = 0; i < updated.size(); i++) {
    cout << updated[i].type_ << ", " << updated[i].quantity_ << ", " << endl;
}


cout << "Companion: " << kevin.getCompanion() << endl;


/*
// Barbarian Test
Barbarian kevin("testing123", "ELF", -3, 10, 5, false, "sword", "shield", false);
cout << "Name: " << kevin.getName() << endl;
cout << "Race: " << kevin.getRace() << endl;
cout << "Vitality: " << kevin.getVitality() << endl;
cout << "Armor: " << kevin.getArmor() << endl;
cout << "Level: " << kevin.getLevel() << endl;
cout << "Enemy: " << kevin.isEnemy() << endl;
cout << "Main Weapon: " << kevin.getMainWeapon() << endl;
cout << "Secondary Weapon: " << kevin.getSecondaryWeapon() << endl;
cout << "Enraged: " << kevin.getEnrage() << endl;
*/
    return 0;
}