#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft{
    class Warrior;
    class Noble{
        friend ostream& operator<<(ostream& os, const Noble& noble);

    public: 
    Noble(const string& name);
    void setStrength(double strength);
    void setIsDead(bool isDead);
    bool getIsDead() const;
    double getStrength() const;
    const string& getName() const;
    bool findAWarrior(const string& name);// I  use this publicly
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    void battle(Noble& noble);
    bool deleteWarrior(Warrior& warrior);

    private:
    string name;
    double strength;
    bool isDead;
    vector<Warrior*> armyOfWarriors;

    void setStrengthWinner(Noble& winner, Noble& loser);
    void setStrengthLoser(Noble& noble);
    size_t lookForAWarrior(Warrior& warrior);
    };
}
#endif