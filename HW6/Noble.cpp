#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft{
    Noble::Noble(const string& name): name(name), strength(0), alive(true){}
    
    ostream& operator<<(ostream& os, const Noble& noble){
        os << noble.name << " has an army size of " << noble.army.size();
        for (size_t i = 0; i < noble.army.size(); ++i){
            os << "\n    " << *(noble.army[i]);
        }
        return os;
    }
    const string& Noble::getName() const {
        return name;
    }
    double Noble::getStrength() const {
        return strength;
    }
    void Noble::setStrength(double strength){
        this->strength = strength;
    }
    bool Noble::isAlive() const {
        return alive;
    }
    void Noble::killed(){
        this->alive = false;
    }

    void Noble::setStrengthVictor(Noble& winner, Noble& loser){
        double lossRatio = loser.getStrength() / winner.getStrength();
        double remainingHealthRatio = 1 - lossRatio;
        double winningHealth = winner.getStrength();
        winner.setStrength(remainingHealthRatio * winningHealth);
        for (size_t i = 0; i < winner.army.size(); ++i){
            double curr = winner.army[i]->getStrength();
            winner.army[i]->setStrength(remainingHealthRatio * curr);
        }
    }

    void Noble::setStrengthLoser(Noble& noble){
        for(Warrior* const warrior : noble.army){
            warrior->setStrength(0);
            warrior->killed();
        }
        noble.setStrength(0);
        noble.killed();
    }

    size_t Noble::warrFinder(Warrior& warrior){
        for (size_t i = 0; i < army.size(); ++i){
            if (army[i] == &warrior){
                return i;
            }
        }
        return army.size();
    }

    bool Noble::deleteWarr(Warrior& warrior){
        size_t idx = warrFinder(warrior);
        if(idx == army.size()){
            return false;
        }
        else{
            strength -= warrior.getStrength();
            //shifting the values after index forward one slot
            for(size_t i = idx; i < army.size(); ++i){
                army[i] = army[i+1];
            }
            army.pop_back();
            warrior.setNoble(nullptr);
            warrior.firing();
            return true;
        }
        
    }

    bool Noble::hire(Warrior& warrior){
        if(warrior.isHired() || alive == false){
            cout << "Couldn't hire this warrior!" << endl;
            return false;
        }
        else{
            warrior.hiring();
            warrior.setNoble(this);
            army.push_back(&warrior);
            strength+= warrior.getStrength();
            return true;
        }
    }

    bool Noble::fire(Warrior& warrior){
        size_t idx;
        idx = warrFinder(warrior);

        if(alive == false || idx == army.size()){
            cout << "Couldn't fire the warrior!" << endl;
            return false;
        }
        else{
            bool fireSuccess = deleteWarr(warrior);
            if (fireSuccess == true){
                cout << "You don't work for me anymore, ";
                cout << warrior.getName() << " -- " << name << endl;
                return true;
            }
            else{
                cout << "Couldn't fire the warrior!" << endl;
                return false;  
            }
        }
    }

    void Noble::battle(Noble& noble){
        cout << this->name << " battles " << noble.getName() << endl;
        double enemyStrength = noble.getStrength();
        if(noble.isAlive() == false && this->alive == false){
            cout << "Oh no, they're both dead! Yuck!" << endl;
        }
        else if(noble.isAlive() == false){
            cout << "He's dead, " << this->name << endl;
        }
        else if(this->alive == false){
            cout << "He's dead, " << noble.getName() << endl;
        }
        else if(this->strength == enemyStrength){
            cout << "Mutual annihilation: " << this->name << " and ";
            cout << noble.getName() << " die at each other's hands" << endl;
            setStrengthLoser(noble);
            setStrengthLoser(*this);
        }
        else if(this->strength < enemyStrength){
            cout << noble.getName() << " defeats ";
            cout << this->name << "!" << endl;
            setStrengthVictor(noble, *this);
            setStrengthLoser(*this);
        }
        else if(this->strength > enemyStrength){
            cout << this->name << " defeats ";
            cout << noble.getName() << "!" << endl;
            setStrengthVictor(*this, noble);
            setStrengthLoser(noble);
        }
        else{
            cout << "Something went wrong!" << endl;
        }
    }
}   