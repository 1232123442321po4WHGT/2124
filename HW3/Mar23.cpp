#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Vehicle{
    public:
    void roll(){
        cout << "rolling" << endl;
    }
};
class LandVehicle : public Vehicle{};
class WaterVehicle : public Vehicle{};
class JetSki : public WaterVehicle{};
class Car : public Vehicle{};
class Helicopter : public Vehicle{};

class Animal{
    public:
    void eat(){
        cout << "Animal is eating" << endl;
    }
};

class Lion : public Animal{};
class Tiger : public Animal{
    public:
    void eat(){
        cout << "Tiger is eating" << endl;
    }
};
class Bear : public Animal{};

int main(){
    Bear yogi;
    yogi.eat();

    Tiger tigger;
    tigger.eat();

    Vehicle car;
    car.roll();
}

