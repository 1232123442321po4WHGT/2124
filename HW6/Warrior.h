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
    void hiring();
    void firing();
    void killed();
    void setStrength(double strength);
    void runaway();
    void setNoble(Noble* noble);
    bool isHired() const;
    const string& getName() const;
    double getStrength() const;

    private:
    string name;
    double strength;
    bool employed;
    bool isDead;
    Noble* noble;
    };
}
#endif