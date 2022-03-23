#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft{
    Warrior::Warrior(const string& name, double strength): name(name), strength(strength), 
        employed(false), isDead(false), noble(nullptr){}

    void Warrior::hiring(){
        this->employed = true;
    }

    void Warrior::firing(){
        this->employed = false;
    }
    void Warrior::killed(){
        this->isDead = isDead;
    }
    void Warrior::setStrength(double strength){
        this-> strength = strength;
    }
    void Warrior::runaway(){
        //Tarzan flees in terror, abandoning his lord, King Arthur
        cout << name << " flees in terror, abandoning his lord, ";
        cout << noble->getName() << endl; 
        noble->deleteWarr(*this);
    }
    bool Warrior::isHired() const {
        return employed;
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