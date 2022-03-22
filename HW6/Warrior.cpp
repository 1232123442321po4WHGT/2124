#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft{
    Warrior::Warrior(const string& name, double strength): name(name), strength(strength), 
        isHired(false), isDead(false), noble(nullptr){}
    void Warrior::setIsHired(bool isHired){
        this->isHired = isHired;
    }
    void Warrior::setIsDead(bool isDead){
        this->isDead = isDead;
    }
    void Warrior::setStrength(double strength){
        this-> strength = strength;
    }
    void Warrior::runaway(){
        //Tarzan flees in terror, abandoning his lord, King Arthur
        cout << name << " flees in terror, abandoning his lord, ";
        cout << noble->getName() << endl; 
        noble->deleteWarrior(*this); //because I deleted warrior here, set noble = null already
        //has to print before this line
    }
    bool Warrior::getIsHired() const {
        return isHired;
    }
    const string& Warrior::getName() const {
        return name;
    }
    double Warrior::getStrength() const {
        return strength;
    }
    void Warrior::setNoble(Noble* noble){
        this->noble = noble;
    }


    ostream& operator<<(ostream& os, const Warrior& warrior){
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
}