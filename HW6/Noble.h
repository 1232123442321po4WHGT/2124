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
        const string& getName() const;
        double getStrength() const;
        void setStrength(double strength);
        bool isAlive() const;
        void killed();
        bool deleteWarr(Warrior& warrior);
        bool findAWarrior(const string& name);// I  use this publicly
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        void battle(Noble& noble);
        
        private:
        string name;
        double strength;
        bool alive;
        vector<Warrior*> armyOfWarriors;

        void setStrengthVictor(Noble& winner, Noble& loser);
        void setStrengthLoser(Noble& noble);
        size_t warrFinder(Warrior& warrior);
    };
}

#endif