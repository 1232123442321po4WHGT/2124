#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//warrior class method definitions under warriorcraft namespace
namespace WarriorCraft{
    Warrior::Warrior(const string& name, double strength): name(name), strength(strength), 
        employed(false), alive(true), noble(nullptr){}

    ostream& operator<<(ostream& os, const Warrior& warrior){
        os << warrior.name << " : " << warrior.strength;
        return os;
    }
    const string& Warrior::getName() const {
        return name;
    }
    double Warrior::getStrength() const {
        return strength;
    }
    void Warrior::setStrength(double strength){
        this->strength = strength;
    }
    void Warrior::setNoble(Noble* noble){
        this->noble = noble;
    }
    bool Warrior::isHired() {
        return employed;
    }
    void Warrior::hiring(){
        this->employed = true;
    }
    void Warrior::firing(){
        this->employed = false;
    }
    void Warrior::killed(){
        this->alive = false;
    }

    void Warrior::runaway(){
        cout << name << " flees in terror, abandoning his lord, ";
        cout << noble->getName() << endl; 
        noble->deleteWarr(*this);
    }


}