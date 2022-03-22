#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Noble;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    string name;
    double strength;
    bool isHired;
    bool isDead;
    Noble* noble;
public:
    Warrior(const string& name, double strength);
    void setIsHired(bool isHired);
    bool getIsHired() const;
    void setIsDead(bool isDead);
    void setStrength(double strength);
    double getStrength() const;
    void runaway();
    void setNoble(Noble* noble);
    const string& getName() const;

};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble);
private:
    string name;
    double strength;
    bool isDead;
    vector<Warrior*> armyOfWarriors;

    void setStrengthWinner(Noble& winner, Noble& loser);
    void setStrengthLoser(Noble& noble);
    size_t lookForAWarrior(Warrior& warrior) const;
public: 
    Noble(const string& name);
    void setStrength(double strength);
    void setIsDead(bool isDead);
    bool getIsDead() const;
    double getStrength() const;
    const string& getName() const;
    bool findAWarrior(const string& name) const;// I  use this publicly - for the command
    bool deleteWarrior(Warrior& warrior);
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    void battle(Noble& noble);
};

// const string& Noble::getName() const {
//     return name;
// }

//Warrior methods  here
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

//Noble methods here
/*
This method takes in the Noble that wins and the Noble that loses
and resets the strength of the noble that wins.
*/
void Noble::setStrengthWinner(Noble& winner, Noble& loser){
    double ratio = loser.getStrength() / winner.getStrength();
    for(Warrior* const warrior : winner.armyOfWarriors){
        double curr_strength = warrior->getStrength();
        warrior->setStrength(curr_strength*(1-ratio));
    }
    winner.setStrength(winner.getStrength() * (1 - ratio));
}

/*
This method takes in the Noble that loses and announces 
that the Noble and all his Warriors are now dead
*/
void Noble::setStrengthLoser(Noble& noble){
    for(Warrior* const warrior : noble.armyOfWarriors){
        warrior->setStrength(0);
        warrior->setIsDead(true);
    }
    noble.setStrength(0);
    noble.setIsDead(true);
}

//since this is internal, warrior can be passed in as pointer!!! easier to compare?

size_t Noble::lookForAWarrior(Warrior& warrior) const{
    size_t wIndex = armyOfWarriors.size();
    for(size_t i = 0; i < armyOfWarriors.size(); ++i){
        if(armyOfWarriors[i] ==  &warrior){
            wIndex = i;
            //just added, haven't tested this break
            break;
        }
    }
    if(wIndex == armyOfWarriors.size()){
        cerr << "You didn't hire this warrior, cannot fire" << endl;
        //exit(1);
    }
    return wIndex;
}
bool Noble::deleteWarrior(Warrior& warrior){
    size_t wIndex = lookForAWarrior(warrior);
    if(wIndex == armyOfWarriors.size()){
        return false;
    }
    for(size_t i = wIndex; i < armyOfWarriors.size(); ++i){
        armyOfWarriors[i] = armyOfWarriors[i+1];
    }
    armyOfWarriors.pop_back();
    strength -= warrior.getStrength();
    warrior.setIsHired(false);
    warrior.setNoble(nullptr);
    return true;
}
Noble::Noble(const string& name): name(name){}
void Noble::setStrength(double strength){
    this->strength = strength;
}
void Noble::setIsDead(bool isDead){
    this->isDead = isDead;
}
bool Noble::getIsDead() const {
    return isDead;
}
double Noble::getStrength() const {
    return strength;
}

const string& Noble::getName() const {
    return name;
}

/*
This method returns true if a warrior 
of the specified name is found in the army
*/
bool Noble::findAWarrior(const string& name) const {
    for(Warrior* warrior: armyOfWarriors){
        if(name == warrior->getName()){
            return true;
        }
    }
    return false;
}
bool Noble::hire(Warrior& warrior){

    //If the Noble is dead, he cannot hire anyone
    //Or if the warrior is already hired, 
    //the noble cannot hire him
    if(isDead || warrior.getIsHired()){
        return false;
    }
    else{
        warrior.setIsHired(true);
        warrior.setNoble(this);
        armyOfWarriors.push_back(&warrior);
        strength+= warrior.getStrength();
        return true;
    }
}
bool Noble::fire(Warrior& warrior){// pass in ref here b/c main pass in by  ref, easier for user than add by pointer

    ///this - use lookForWarrior() - this is extra, excessive
    size_t count =  0;
    for(Warrior* theWarrior: armyOfWarriors){
        if(theWarrior->getName() == warrior.getName()){
            count ++;
        }
    }
    if(count == 0){
        return false;
    }
    /// to this: why???

    //If the Noble is dead, he cannot fire anyone
    if(isDead){
        return false;
    }
    else{
        //look for warrior 1  -- already look here, look for even reference!!!
        size_t wIndex = lookForAWarrior(warrior);
        if(!deleteWarrior(warrior)){
            cerr << "Couldn't remove the Warrior" << endl;
            return false;
        }
        return true;
    }
}

/*
This method starts the battle by taking in the Noble this object 
this fighting against, and then change each warrior's strength
according to the following rules:
If a Noble has less strength then he and all of his Warriors are dead and 
the stronger Noble and each Warrior loses only the amount of strength 
that is proportional to his enemy's total army strength over his total
army strength
If two warriors have the same strength, they both lose all strength
Then, this method prints out the result of the battle.
*/
void Noble::battle(Noble& noble){

    cout << this->name << " battles " << noble.getName() << endl;
    double enemyStrength = noble.getStrength();
    if(this->isDead && noble.getIsDead()){
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    }
    else if(this->isDead){
        cout << "He's dead, " << noble.getName() << endl;
    }
    else if(noble.getIsDead()){
        cout << "He's dead, " << this->name << endl;
    }
    else if(this->strength < enemyStrength){
        cout << noble.getName() << " defeats " << this->name << endl;
        setStrengthWinner(noble, *this);
        setStrengthLoser(*this);
    }
    else if(this->strength == enemyStrength){
        cout << "Mutual Annihalation: " << this->name << " and "
        << noble.getName() << " die at each other's hands" << endl;
        setStrengthLoser(*this);
        setStrengthLoser(noble);
    }
    else{
        cout << this->name << " defeats " << noble.getName() << endl;
        setStrengthWinner(*this, noble);
        setStrengthLoser(noble);
    }
}
ostream& operator<<(ostream& os, const Noble& noble){
    if(noble.armyOfWarriors.size() == 0){
        os << "NONE";
    }
    else{
        os << noble.name << " has an army of " << noble.armyOfWarriors.size();
        for(Warrior* warrior: noble.armyOfWarriors){
            os << endl;
            os << "\t" << *warrior;
        }
    }
    return os;
}

//command functions
void lookForWarrior(const string& name, const vector<Warrior*> warriors){

}
/*
This method performs creates the Warrior 
with the specified name and push the Warrior in 
a vector of all Warrior pointers
*/
void WarriorCommand(const string& name, double strength, vector<Warrior*>& warriors){
     //Should not be exiting if a noble/warrior isn't 
    //  found since this is not crucial to the whole program. 
    //  One mistake in the file that is being 
    //  read should not kill the whole program

    for(Warrior* warrior: warriors){
        if(warrior->getName() == name){
            cerr << "This warrior already exists" << endl;
            //exit(1);
        }
    }
    warriors.push_back(new Warrior(name, strength));
}

/*
This method performs creates the Noble 
with the specified name and push the Noble in 
a vector of Noble pointers
*/
void NobleCommand(const string& name, vector<Noble*>& nobles){
    for(Noble* noble: nobles){
        if(noble->getName() == name){
            cerr << "This noble already exists" << endl;
            //exit(1);
        }
    }
    nobles.push_back(new Noble(name));
}
/*
This method prints out all the Nobles and Warriors
*/
void StatusCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors){
   
    size_t numOfNoblesInHeap = 0;
    //Print out all the Nobles
    for(Noble* noble: nobles){
        if(noble){
            cout << *noble << endl;
            numOfNoblesInHeap++;
        }
    }

    //If all Nobles are not in the heap, numOfNoblesInHeap = 0
    if(nobles.size() - numOfNoblesInHeap == nobles.size()){
        cout << "NONE" << endl;
    }
    cout << "Unemployed Warriors:" << endl;
    size_t numOfWarriorsInHeap = 0;
    int numOfHiredWarriors = 0;

    //Print out all the unemployed Warriors
    for(Warrior* warrior: warriors){
        //Check if the Warrior is still in the heap
        if(warrior){
            numOfWarriorsInHeap++;
        }
        //
        if(warrior->getIsHired()){
            numOfHiredWarriors ++;
        }
        else{
            cout << *warrior << endl;
        }
    }

    //If all Warriors are not in the heap, 
    //numOfWarriorsInHeap = 0
    
    if(warriors.size() - numOfHiredWarriors == 0 ||
        warriors.size() - numOfWarriorsInHeap == warriors.size()){
        cout << "NONE" << endl;
    }
}
/*
This method looks for the Noble and Warrior with 
the specified name and allow the Noble to hire that
Warrior
*/
void HireCommand(const string& name1, const string& name2,
    vector<Noble*>& nobles, vector<Warrior*>& warriors){

    Noble* theNoble;
    Warrior* theWarrior;

    //Look for the noble with the specified name
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble =  noble;
            break;
        }
    }

    //Check if the Noble exists
    if(!theNoble){
        cerr << "This Noble does not exist" << endl;
        //exit(1);
    } 

    //Look for all available workers to 
    //find the worker with the specified name

    for(Warrior* warrior: warriors){
        if(name2 == warrior->getName()){
            theWarrior =  warrior; 
            break;
        }
    }

    //Check if the Warrior exists
    if(!theWarrior){
        cerr << "This Warrior does not exist" << endl;
        //exit(1);
    }
    theNoble->hire(*theWarrior);//**** hire(theWarrior*)?
}
/*
This method looks for the Noble and Warrior with 
the specified name and allow the Noble to fire that
Warrior
*/
void FireCommand(const string& name1, const string& name2, 
    vector<Noble*>& nobles, vector<Warrior*>& warriors){

    Noble* theNoble;
    Warrior* theWarrior;
    //Look for the noble with the specified name
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble =  noble;
            break;
        }
    }
    //Check if the Noble exists
    if(!theNoble){
        cerr << "This Noble does not exist" << endl;
        //exit(1);
    }
    
    //Check if the Warrior is in the Noble's army
    if(!theNoble->findAWarrior(name2)){
        cerr << "This Warrior is not in" << theNoble->getName()
        << "'s army" << endl;
        //exit(1);
    }
    //Look for the warrior with the specified name
    for(Warrior* warrior: warriors){
        if(name2 == warrior->getName()){
            theWarrior =  warrior; 
            break;
        }
    }
    //Fire the warrior
    theNoble->fire(*theWarrior);
    cout << "You don't work for me anymore " << theWarrior->getName() <<
        "! -- " << theNoble->getName() << "." << endl;
}
/*
This method finds the Noble associated the two 
Nobles of specified names and let the first Noble 
battle the second Noble
*/
void BattleCommand(const string& name1, const string& name2, vector<Noble*>& nobles){
    Noble* theNoble1;
    Noble* theNoble2;
    //Look for the noble with the specified name
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble1 =  noble;
            break;
        }
    }
    //Look for the enemy noble with the specified name
    for(Noble* noble: nobles){
        if(name2 == noble->getName()){
            theNoble2 =  noble;
            break;
        }
    }
    //Check if the Noble exists
    if(!theNoble1){
        cerr << "This Noble does not exist" << endl;
        //exit(1);
    }
    //Check if the enemy Noble exists
    if(!theNoble2){
        cerr << "The enemy Noble does not exist" << endl;
        //exit(1);
    }

    //Start the battle
    theNoble1->battle(*theNoble2);
}

/*
This method clears out all the Nobles and Warriors 
created on the heap
*/
void ClearCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors){
   //Delete each element in the vector of Noble pointers
    for(Noble*& noble: nobles){
        delete noble;
        noble = nullptr;
    }
    nobles.clear();
    //Delete each element in the vector of Warrior pointers
    for(Warrior*& warrior: warriors){
        delete warrior;
        warrior = nullptr;
    }
    warriors.clear();
}


int main(){
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
	
    cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;

    cheetah.runaway();
    cout << art << endl;
	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}