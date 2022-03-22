#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft{
    Noble::Noble(const string& name): name(name), strength(0), isDead(false){}
    /*
    This method takes in the Noble that wins and the Noble that loses
    and resets the strength of the noble that wins.
    */
    void Noble::setStrengthWinner(Noble& winner, Noble& loser){
        double ratio = loser.getStrength() / winner.getStrength();
        for(Warrior* const warrior : winner.armyOfWarriors){
            double curr_strength = warrior->getStrength();
            warrior->setStrength(curr_strength*(1-ratio));
        }
        winner.setStrength(winner.getStrength() * (1 - ratio));
    }

    /*
    This method takes in the Noble that loses and announces 
    that the Noble and all his Warriors are now dead
    */
    void Noble::setStrengthLoser(Noble& noble){
        for(Warrior* const warrior : noble.armyOfWarriors){
            warrior->setStrength(0);
            warrior->setIsDead(true);
        }
        noble.setStrength(0);
        noble.setIsDead(true);
    }
     /*
    This method takes in a Warrior and 
    returns the index of the warrior in the army vector
    if the Warrior address could be found in the army
    */
    size_t Noble::lookForAWarrior(Warrior& warrior){
        size_t wIndex = armyOfWarriors.size();
        for(size_t i = 0; i < armyOfWarriors.size(); ++i){
            if(armyOfWarriors[i] ==  &warrior){
                wIndex = i;
            }
        }
        if(wIndex == armyOfWarriors.size()){
            cerr << "You didn't hire this warrior, cannot fire" << endl;
        }
        return wIndex;
    }
    /*
    This method takes in a Warrior, delete that Warrior from
    the army vector and returns true if it was successfully deleted,
    false otherwise
    */
    bool Noble::deleteWarrior(Warrior& warrior){
        size_t wIndex = lookForAWarrior(warrior);
        if(wIndex == armyOfWarriors.size()){
            return false;
        }
        for(size_t i = wIndex; i < armyOfWarriors.size(); ++i){
            armyOfWarriors[i] = armyOfWarriors[i+1];
        }
        armyOfWarriors.pop_back();
        strength -= warrior.getStrength();
        warrior.setIsHired(false);
        warrior.setNoble(nullptr);
        return true;
    }
    void Noble::setStrength(double strength){
        this->strength = strength;
    }
    void Noble::setIsDead(bool isDead){
        this->isDead = isDead;
    }
    bool Noble::getIsDead() const {
        return isDead;
    }
    double Noble::getStrength() const {
        return strength;
    }

    const string& Noble::getName() const {
        return name;
    }

    /*
    This method returns true if a warrior 
    of the specified name is found in the army
    */
    bool Noble::findAWarrior(const string& name){
        for(Warrior* warrior: armyOfWarriors){
            if(name == warrior->getName()){
                return true;
            }
        }
        return false;
    }

    /*
    This method takes in a Warrior and return true if 
    the Warrior was hired successfully,
    otherwise it returns false
    */
    bool Noble::hire(Warrior& warrior){

        //If the Noble is dead, he cannot hire anyone
        //Or if the warrior is already hired, 
        //the noble cannot hire him
        if(isDead || warrior.getIsHired()){
            return false;
        }
        else{
            warrior.setIsHired(true);
            warrior.setNoble(this);
            armyOfWarriors.push_back(&warrior);
            strength+= warrior.getStrength();
            return true;
        }
    }
     /*
    This method takes in a Warrior and return true if 
    the Warrior was fired successfully,
    otherwise it returns false
    */
    bool Noble::fire(Warrior& warrior){// pass in ref here b/c main pass in by  ref, easier for user than add by pointer

        size_t count =  0;
        for(Warrior* theWarrior: armyOfWarriors){
            if(theWarrior->getName() == warrior.getName()){
                count ++;
            }
        }
        if(count == 0){
            return false;
        }

        //If the Noble is dead, he cannot fire anyone
        if(isDead){
            return false;
        }
        else{
            //look for warrior 1
            size_t wIndex = lookForAWarrior(warrior);
            if(!deleteWarrior(warrior)){
                cerr << "Couldn't remove the Warrior" << endl;
                return false;
            }
            return true;
        }
    }

    /*
    This method starts the battle by taking in the Noble this object 
    this fighting against, and then change each warrior's strength
    according to the following rules:
    If a Noble has less strength then he and all of his Warriors are dead and 
    the stronger Noble and each Warrior loses only the amount of strength 
    that is proportional to his enemy's total army strength over his total
    army strength
    If two warriors have the same strength, they both lose all strength
    Then, this method prints out the result of the battle.
    */
    void Noble::battle(Noble& noble){

        cout << this->name << " battles " << noble.getName() << endl;
        double enemyStrength = noble.getStrength();
        if(this->isDead && noble.getIsDead()){
            cout << "Oh, NO! They're both dead!  Yuck!" << endl;
        }
        else if(this->isDead){
            cout << "He's dead, " << noble.getName() << endl;
        }
        else if(noble.getIsDead()){
            cout << "He's dead, " << this->name << endl;
        }
        else if(this->strength < enemyStrength){
            cout << noble.getName() << " defeats " << this->name << endl;
            setStrengthWinner(noble, *this);
            setStrengthLoser(*this);
        }
        else if(this->strength == enemyStrength){
            cout << "Mutual Annihalation: " << this->name << " and "
            << noble.getName() << " die at each other's hands" << endl;
            setStrengthLoser(*this);
            setStrengthLoser(noble);
        }
        else{
            cout << this->name << " defeats " << noble.getName() << endl;
            setStrengthWinner(*this, noble);
            setStrengthLoser(noble);
        }
    }
    ostream& operator<<(ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.armyOfWarriors.size();
        if(noble.armyOfWarriors.size() == 0){
            //os << "NONE";
        }
        else{
            for(Warrior* warrior: noble.armyOfWarriors){
                os << endl;
                os << "\t" << *warrior;
            }
        }
        return os;
    }

}   