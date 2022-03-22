#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft{
    class Noble;

    class Warrior{
        friend ostream& operator<<(ostream& os, const Warrior& warrior);
    
    public:
    Warrior(const string& name, double strength);
    void setIsHired(bool isHired);
    void setIsDead(bool isDead);
    void setStrength(double strength);
    void runaway();
    void setNoble(Noble* noble);
    bool getIsHired() const;
    const string& getName() const;
    double getStrength() const;

    private:
    string name;
    double strength;
    bool isHired;
    bool isDead;
    Noble* noble;
    };
}
#endif