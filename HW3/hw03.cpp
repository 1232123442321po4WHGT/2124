// Alex Zhao
// This progam is an extension of the second homework
// adding weapons this time around and using classes


#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior{

    //BE CAREFUL ABOUT THIS PART, NEEDS CHANGE PROBABLY
    friend ostream& operator <<(ostream& os, Warrior rhs){
        cout << "Warrior: " << rhs._name << ", weapon: ";
        cout << rhs._weapon.get_name() << ", " << rhs._weapon.get_strength();
        return os;
    }
    public:
    
    class Weap_class{
        friend ostream& operator<< (ostream& os, const Weap_class& inside);

        public:
        Weap_class(){}
        Weap_class(const string& weap_name, int& weap_strengh):
        wname(weap_name), wstrength(weap_strengh){}

        //getters for weapon stats

        string get_name(){
            return wname;
        }

        int get_strength(){
            return wstrength;
        }

        void set_strength(int s){
            wstrength = s;
        }

        private:
        string wname;
        int wstrength;

    };

    Warrior(){}
    Warrior(const string& the_name, const string& the_weapon_name, 
    int the_strength): _name(the_name), _weapon(the_weapon_name, the_strength){}

    string getName(){
        return _name;
    }

    void battle(Warrior& warr){
        Warrior warr1, warr2;
        cout << _name << " battles " << warr.getName() << endl;
        int strength1, strength2;
        strength1 = _weapon.get_strength();
        strength2 = warr._weapon.get_strength();

        if (strength1 == 0 && strength2 == 0){
            cout << "Oh no they're both dead! yuck!" << endl;
        }
        else if (strength1 == strength2){
            cout << "Mutual annihilation: " << _name << " and ";
            cout << warr.getName() << " die at each other's hands" << endl;
            strength1 = 0;
            strength2 = 0;
        }
        else if (strength1 == 0 && strength2 != 0){
            cout << "He's dead, " << warr.getName() << "." << endl;
        }
        else if (strength1 != 0 && strength2 == 0){
            cout << "He's dead, " << _name << "." << endl;
        }
        else if (strength1 > strength2){
            cout << _name << " defeats " << warr.getName() << "!" << endl;
            strength1 -= strength2;
            strength2 = 0;
        }
        else if (strength2 > strength1){
            cout << warr.getName() << " defeats " << _name << "!" << endl;
            strength2 -= strength1;
            strength1 = 0;
        }
    }

    private:
    string _name;
    Weap_class _weapon;


};

// Something wrong here
/*
ostream& operator<< (ostream& os, Warrior& lhs){

}
*/

void fileOpen (ifstream& ifs);
void streamToVec (vector<Warrior>& warriors, ifstream& ifs);
size_t find (vector<Warrior>& warriors, const string name);
Warrior& findWarrObj (vector<Warrior>& warriors, const string name);


int main(){
    ifstream ifs;
    vector<Warrior> warriors;

    fileOpen(ifs);
    streamToVec(warriors, ifs);
    ifs.close();
}

void fileOpen(ifstream& ifs){
    do{
        ifs.open("warriors.txt");
    } while (!ifs);
}

void streamToVec(vector<Warrior>& warriors, ifstream& ifs){
    Warrior currWar, warr1, warr2;
    string type, name, weapon, fighter1, fighter2;
    size_t idx, idx1;
    int strength;

    while (ifs >> type){
        if (type == "Warrior"){
            ifs >> name >> weapon >> strength;
            //Need a function for adding a warrior
            idx = find(warriors, name);
            if (idx == warriors.size()){
                currWar = Warrior(name, weapon, strength);
                warriors.push_back(currWar);
            }
            else{
                cout << "There is already a warrior with that name!" << endl;
            }
        }
        else if (type == "Status"){
            cout << "There are: " << warriors.size() << " warriors" << endl;
            for (size_t i = 0; i < warriors.size(); ++i){
                cout << warriors[i] << endl;
            }
        }
        else if (type == "Battle"){
            ifs >> fighter1 >> fighter2;
            //This gives the indexes of fighters
            idx = find(warriors, fighter1);
            idx1 = find(warriors, fighter2);
            //this gives the actual warrior objects
            warr1 = findWarrObj(warriors, fighter1);
            warr2 = findWarrObj(warriors, fighter2);
            //I know I could just do warriors[idx] but I like it this way

            if (idx == warriors.size() || idx1 == warriors.size()){
                cout << "At least one of these warriors don't exist!" << endl;
            }
            else{
                warr1.battle(warr2);
            }
        }
    }
}

size_t find(vector<Warrior>& warriors, const string name){
    for (size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i].getName() == name){
            return i;
        }
    }
    return warriors.size();
}

//Hold on, am I returning a copy or the original?
Warrior& findWarrObj(vector<Warrior>& warriors, const string name){
    for (size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i].getName() == name){
            return warriors[i];
        }
    }
}