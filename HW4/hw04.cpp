// Alex Zhao, hw04.cpp
// This progam is an extension of the third homework
// this time using pointers and including nobles
// new hiring and firing methods

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Class prototypes
class Noble;
//class Warrior;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior){
        os << "     " << warrior._name << ": " << warrior._strength << endl;
        return os;
    }

    public:
    Warrior (const string& name, double strength): 
    _name(name), _strength(strength), _hired(false), _warr(nullptr) {}

    const string& getName() const{
        return _name;
    }

    double getStrength() const{
        return _strength;
    }

    void setStrength(double ratio){
        double alive_meter = 1-ratio;
        _strength = (alive_meter) * _strength;
    }

    void hiring(){
        _hired = true;
    }

    bool employed(){
        return _hired;
    }

    private:
    bool _hired;
    Noble* _nbl;
    Warrior* _warr;
    string _name;
    double _strength;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble){

        //for loop iterator?
        os << noble._name << " has an army of " << noble._army.size() << endl;
        for (size_t i = 0; i < noble._army.size(); ++i){
            os << *noble._army[i];
        }
        return os;
    }

    public:
    Noble (const string& name) : _name(name) {
        alive = true;
    }

    const string& get_name() const {
        return _name;
    }

    void death(){
        alive = false;
    }

    bool isAlive() const {
        if (alive == true){
            return true;
        }
        return false;
    }

    bool hire(Warrior& warr){
        if (alive == false){
            cout << "This warrior is dead, cannot be hired" << endl;
            return false;
        }
        else if (warr.employed() == true){
            cout << "This warrior has already been hired" << endl;
            return false;
        }
        else{
            //warr.setNoble(this);
            _army.push_back(&warr);
            warr.hiring();
            return true;
        }
    }

    bool fire(Warrior& fired){
        size_t idx;
        if (alive == false){
            cout << "This noble is dead, cannot fire a dead warrior" << endl;
            return false;
        }
        else if (fired.employed() == false){
            cout << "This warrior is already unemployed" << endl;
            return false;
        }
        else{
            idx = find(fired);
            cout << "You don't work for me anymore " << fired.getName();
            cout << ". -- " << _name << endl;

            for (size_t swap = idx; swap < _army.size(); ++swap){
                _army[swap] = _army[swap+1];
            }
            _army.pop_back();
            //fired.setNoble(nullptr);
            return true;
        }
    }

    size_t find (Warrior& warr){
        for (size_t i = 0; i < _army.size(); ++i){
            if (&warr == _army[i]){
                return i;
            }
        }
        cout << "The warrior was not found" << endl;
        return _army.size();
    }

    double get_army_strength(){
        double total = 0;
        for (Warrior* warr: _army){
            total += warr->getStrength();
        }
        return total;
    }

    void set_army_strength(double ratio){
        for (Warrior* warr: _army){
            warr->setStrength(ratio);
        }
    }

    void battle(Noble& enemy){
        double yourStrength = get_army_strength();
        double enemyStrength = enemy.get_army_strength();
        double ratio;

        cout << _name << " battles " << enemy.get_name() << "." << endl;

        if (alive == false && enemy.alive == false){
            cout << "Oh no they're both dead, yuck!" << endl;
        }
        else if (alive == false && enemy.alive == true){
            cout << "He's dead, " << enemy.get_name() << endl;
        }
        else if (alive == true && enemy.alive == false){
            cout << "He's dead, " << _name << endl;
        }
        else if (yourStrength == enemyStrength){
            cout << "Mutual annihilation: " << _name << " and ";
            cout << enemy.get_name() << " die at each other's hands" << endl;

            death();
            enemy.death();
            set_army_strength(1);
            enemy.set_army_strength(1);
        }
        else if (yourStrength > enemyStrength){
            ratio = enemyStrength / yourStrength;
            victory(enemy, ratio);
        }
        else if (yourStrength < enemyStrength){
            ratio = yourStrength / enemyStrength;
            enemy.victory(*this, ratio);
        }
        
    }

    void victory(Noble& enemy, double ratio){
        cout << _name << " defeats " << enemy.get_name() << endl;
        set_army_strength(ratio);
        enemy.set_army_strength(1);
        enemy.death();
    }

    private:
    string _name;
    vector<Warrior*> _army;
    bool alive;
    Warrior* _warr;
};


int main() {
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
    art.fire(cheetah);
    cout << art << endl;
	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
}
