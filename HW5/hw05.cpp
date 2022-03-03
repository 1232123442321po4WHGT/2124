//hw05.cpp Alex Zhao
//This homework is a continuation of the fourth homework with some 
//differences, namely using the heap. 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Warrior class: This is where object and method creation everything 
//Related to warriors is 
class Warrior{

    friend ostream& operator<<(ostream& os, const Warrior& warr){
        os << "     " << warr.name << ": " << warr.strength;
        return os;
    }

    public:
    Warrior(const string& name, int strength) : name(name), 
    strength(strength), employed(false){}
    //In order to check the status of whether a warrior is hired or not, 
    //I'll be using a bool value of employed(bool) which I'll keep track of

    const string& getName() const {
        return name;
    }

    const int getStrength() const {
        return strength;
    }

    void setStrength(int power){
        strength = power;
    }

    bool employmentStatus(){
        return employed;
    }

    //the two setters: In hindsight I could've just done a setEmployment method
    //that passes in a true/false
    void hiring(){
        employed = true;
    }
    void firing(){
        employed = false;
    }

    private:
    bool employed;
    string name;
    int strength;
};

//Noble class, everything related to noble + battle methods are in here
class Noble{

    friend ostream& operator<<(ostream& os, const Noble& nbl){
        os << nbl.name << " has an army of " << nbl.warriors.size() << endl;
        for (size_t i = 0; i < nbl.warriors.size(); ++i){
            os << *nbl.warriors[i] << endl;
        }
        return os;
    }

    public:
    Noble(const string& name) : name(name){}

    const string& getname() const {
        return name;
    }

    void setWarr(float ratio){
        for (Warrior* warr: warriors){
            warr->setStrength(int(warr->getStrength() * ratio));
        }
    }

    void hire(Warrior* warr){
        if (warr->employmentStatus() == false){
            warriors.push_back(warr);
            total += warr->getStrength();
            warr->hiring();
        }
    }

    void fire(Warrior* warr){
        if (warr->employmentStatus() == false){
            cout << "This warrior is unemployed!" << endl;
        }
        else{
            for (size_t i = 0; i < warriors.size(); ++i){
                if (warr->getName() == warriors[i]->getName()){
                    cout << "You don't work for my anymore " << warr->getName();
                    cout << "! --" << name << "." << endl;
                    for (size_t swap = i; swap < warriors.size() - 1; ++swap){
                        warriors[swap] = warriors[swap + 1];
                    }
                    total -= warr->getStrength();
                    warriors.pop_back();
                }
            }
        }
        warr->firing();
    }

    void battle(Noble& nbl){
        float remaining = -1;
        cout << name << " battles " << nbl.name << endl;
        if (total == 0 && nbl.total == 0){
            cout << "Oh no they're both dead! Yuck!" << endl;

        }
        else if (total == 0 && nbl.total != 0){
            cout << "He's dead, " << nbl.getname() << endl;
        }
        else if (total != 0 && nbl.total == 0){
            cout << "He's dead, " << name << endl;
        }
        else if (total == nbl.total){
            cout << "Mutual annihilation! " << name << " and ";
            cout << nbl.getname() << " die at each other's hands." << endl;
            setWarr(0);
            nbl.setWarr(0);
            total = 0;
            nbl.total = 0;
        }
        else if (total > nbl.total){
            cout << name << " defeats " << nbl.name << endl;
            remaining = 1 - nbl.total / total;
            setWarr(remaining);
            total -= nbl.total;
            nbl.setWarr(0);
            nbl.total = 0;
        }
        else if (total < nbl.total){
            cout << nbl.name << " defeats " << name << endl;
            remaining = 1 - total / nbl.total;
            nbl.setWarr(remaining);
            nbl.total -= total;
            setWarr(0);
            total = 0;
        }
    }

    private:
    string name;
    vector<Warrior*> warriors;
    float total = 0; 
};

//function prototypes
void fileOpen (ifstream& ifs);
void streamToVec (ifstream& ifs);
Warrior* getWarr (const vector<Warrior*>& warriors, const string& name);
Noble* getNbl (const vector<Noble*>& nbllist, const string& name);
void clearWarr (vector<Warrior*> warriors);
void clearNbl (vector<Noble*> nbllist);
void dispWarr (const vector<Warrior*> warriors);
void dispNbl (const vector<Noble*> nbllist);

//Main method
int main(){
    ifstream ifs;
    fileOpen(ifs);
    streamToVec(ifs);
}

//Checks to see if file is openable or not and handles accordingly
void fileOpen(ifstream& ifs){
    ifs.open("nobleWarriors.txt");
    if (!ifs){
        cout << "File not found" << endl;
    }
}

//Reads from the file and delegates functions according to first word
void streamToVec(ifstream& ifs){
    string type, warrName, nblName1, nblName2;
    vector<Warrior*> warriors;
    vector<Noble*> nbllist;
    int strength;
    Noble* nblp1;
    Noble* nblp2;

    while(ifs >> type){
        if (type == "Warrior"){
            //this handles pushing back a warrior into the vector, handles duplicates
            ifs >> warrName >> strength;

            if (getWarr(warriors, warrName) != nullptr){
                cout << "This warrior already exists!" << endl;
            }
            else{
                warriors.push_back(new Warrior(warrName, strength));
            }
        }
        else if (type == "Noble"){
            ifs >> nblName1;
            if (getNbl(nbllist, nblName1) != nullptr){
                cout << "The noble already exists!" << endl;
            }
            else{
                nbllist.push_back(new Noble(nblName1));
            }
        }
        else if (type == "Hire"){
            ifs >> nblName1 >> warrName;
            if (getNbl(nbllist, nblName1) == nullptr){
                cout << "This noble does not exist." << endl;
            }
            else{
                if (getWarr(warriors, warrName) == nullptr){
                    cout << "The warrior: " << warrName << " does not exist." << endl;
                }
                else if (getWarr(warriors, warrName)->employmentStatus() == true){
                    cout << "Attempt to hire " << warrName << " by ";
                    cout << nblName1 << " failed!" << endl;
                }
                else{
                    getNbl(nbllist, nblName1)->hire(getWarr(warriors, warrName));
                }
            }
        }
        else if (type == "Fire"){
            ifs >> nblName1 >> warrName;
            if (getNbl(nbllist, nblName1) == nullptr){
                cout << "Noble does not exist" << endl;
            }
            else{
                getNbl(nbllist, nblName1)->fire(getWarr(warriors, warrName));
            }
        }
        else if (type == "Battle"){
            ifs >> nblName1 >> nblName2;
            nblp1 = getNbl(nbllist, nblName1);
            nblp2 = getNbl(nbllist, nblName2);
            if (nblp1 == nullptr || nblp2 == nullptr){
                cout << "At least one of these nobles don't exist!" << endl;
            }
            else{
                nblp1->battle(*nblp2);
            }
        }
        else if (type == "Clear"){
            clearWarr(warriors);
            clearNbl(nbllist);
            warriors.clear();
            nbllist.clear();

        }
        else{
            cout << "Status" << endl;
            cout << "============" << endl;
            dispNbl(nbllist);
            cout << endl;
            dispWarr(warriors);
        }
    }

}

//getWarr returns the pointer to the warrior object
Warrior* getWarr(const vector<Warrior*>& warriors, const string& name){
    for (size_t i = 0; i < warriors.size(); ++i){
        if (name == warriors[i]->getName()){
            return warriors[i];
        }
    }
    return nullptr;
}

//getNbl returns the pointer to the noble object
Noble* getNbl(const vector<Noble*>& nbllist, const string& name){
    for (size_t i = 0; i < nbllist.size(); ++i){
        if (name == nbllist[i]->getname()){
            return nbllist[i];
        }
    }
    return nullptr;
}

//This clears the entire vector of warriors
void clearWarr(vector<Warrior*> warriors){
    for (size_t i = 0; i < warriors.size(); ++i){
        delete warriors[i];
    }
}

//This cleares the entire vector of nobles
void clearNbl(vector<Noble*> nbllist){
    for (size_t i = 0; i < nbllist.size(); ++i){
        delete nbllist[i];
    }
}

void dispWarr(const vector<Warrior*> warriors){
    int unemployed = 0;
    cout << "Unemployed Warriors: " << endl;
    for (Warrior* warr : warriors){
        if (warr->employmentStatus() == false){
            unemployed += 1;
        }
    }
    if (unemployed == 0){
        cout << "None" << endl;
    }
    else{
        for (size_t i = 0; i < warriors.size(); ++i){
            if (warriors[i]->employmentStatus() == false){
                cout << *warriors[i] << endl;
            }
        }
    }
}

void dispNbl(const vector<Noble*> nbllist){
    cout << "Nobles: " << endl;
    if (nbllist.size() == 0){
        cout << "None" << endl;
    }
    else{
        for (size_t i = 0; i < nbllist.size(); ++i){
            cout << *nbllist[i] << endl;
        }
    }
}