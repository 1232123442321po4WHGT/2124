#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//warrior header
//adding onto the warriorcraft namespace, declaring a noble class and defining
//warrior class
namespace WarriorCraft{
    class Noble;
    class Warrior{
        friend ostream& operator<<(ostream& os, const Warrior& warrior);
    
        public:
        Warrior(const string& name, double strength);

        const string& getName() const;
        double getStrength() const;
        void setStrength(double strength);
        void setNoble(Noble* noble);
        bool isHired();
        void hiring();
        void firing();
        void killed();
        void runaway();

        private:
        Noble* noble;
        string name;
        double strength;
        bool employed;
        bool alive;
    };
}

#endif