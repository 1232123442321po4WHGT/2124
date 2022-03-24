/*
Alex Zhao
This is the single file for the warriors and nobles program
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Noble;

//Warrior class
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
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    void battle(Noble& noble);
    
    private:
    string name;
    double strength;
    bool alive;
    vector<Warrior*> army;

    void setStrengthVictor(Noble& winner, Noble& loser);
    void setStrengthLoser(Noble& noble);
    size_t warrFinder(Warrior& warrior);
};

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

Noble::Noble(const string& name): name(name), strength(0), alive(true){}

ostream& operator<<(ostream& os, const Noble& noble){
    os << noble.name << " has an army size of " << noble.army.size();
    for (size_t i = 0; i < noble.army.size(); ++i){
        os << "\n    " << *(noble.army[i]);
    }
    return os;
}
const string& Noble::getName() const {
    return name;
}
double Noble::getStrength() const {
    return strength;
}
void Noble::setStrength(double strength){
    this->strength = strength;
}
bool Noble::isAlive() const {
    return alive;
}
void Noble::killed(){
    this->alive = false;
}

void Noble::setStrengthVictor(Noble& winner, Noble& loser){
    double lossRatio = loser.getStrength() / winner.getStrength();
    double remainingHealthRatio = 1 - lossRatio;
    double winningHealth = winner.getStrength();
    winner.setStrength(remainingHealthRatio * winningHealth);
    for (size_t i = 0; i < winner.army.size(); ++i){
        double curr = winner.army[i]->getStrength();
        winner.army[i]->setStrength(remainingHealthRatio * curr);
    }
}

void Noble::setStrengthLoser(Noble& noble){
    for(Warrior* const warrior : noble.army){
        warrior->setStrength(0);
        warrior->killed();
    }
    noble.setStrength(0);
    noble.killed();
}

size_t Noble::warrFinder(Warrior& warrior){
    for (size_t i = 0; i < army.size(); ++i){
        if (army[i] == &warrior){
            return i;
        }
    }
    return army.size();
}

bool Noble::deleteWarr(Warrior& warrior){
    size_t idx = warrFinder(warrior);
    if(idx == army.size()){
        return false;
    }
    else{
        strength -= warrior.getStrength();
        for(size_t i = idx; i < army.size(); ++i){
            army[i] = army[i+1];
        }
        army.pop_back();
        warrior.setNoble(nullptr);
        warrior.firing();
        return true;
    }
}

bool Noble::hire(Warrior& warrior){
    if(warrior.isHired() || alive == false){
        cout << "Couldn't hire this warrior!" << endl;
        return false;
    }
    else{
        warrior.hiring();
        warrior.setNoble(this);
        army.push_back(&warrior);
        strength+= warrior.getStrength();
        return true;
    }
}

bool Noble::fire(Warrior& warrior){
    size_t idx;
    idx = warrFinder(warrior);

    if(alive == false || idx == army.size()){
        cout << "Couldn't fire the warrior!" << endl;
        return false;
    }
    else{
        bool fireSuccess = deleteWarr(warrior);
        if (fireSuccess == true){
            cout << "You don't work for me anymore, ";
            cout << warrior.getName() << " -- " << name << endl;
            return true;
        }
        else{
            cout << "Couldn't fire the warrior!" << endl;
            return false;  
        }
    }
}

void Noble::battle(Noble& noble){
    cout << this->name << " battles " << noble.getName() << endl;
    double enemyStrength = noble.getStrength();
    if(noble.isAlive() == false && this->alive == false){
        cout << "Oh no, they're both dead! Yuck!" << endl;
    }
    else if(noble.isAlive() == false){
        cout << "He's dead, " << this->name << endl;
    }
    else if(this->alive == false){
        cout << "He's dead, " << noble.getName() << endl;
    }
    else if(this->strength == enemyStrength){
        cout << "Mutual annihilation: " << this->name << " and ";
        cout << noble.getName() << " die at each other's hands" << endl;
        setStrengthLoser(noble);
        setStrengthLoser(*this);
    }
    else if(this->strength < enemyStrength){
        cout << noble.getName() << " defeats ";
        cout << this->name << "!" << endl;
        setStrengthVictor(noble, *this);
        setStrengthLoser(*this);
    }
    else if(this->strength > enemyStrength){
        cout << this->name << " defeats ";
        cout << noble.getName() << "!" << endl;
        setStrengthVictor(*this, noble);
        setStrengthLoser(noble);
    }
    else{
        cout << "Something went wrong!" << endl;
    }
}

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();
	cout << endl << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha 
	     << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha 
	     << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}