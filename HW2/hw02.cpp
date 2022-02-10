/*
Alex Zhao
This program pits warriors against each other and computes their
respective strengths after each engagement
*/
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//warrior struct
struct Warrior{
    string type;
    string name;
    int strength;
};

//prototypes
void openfile (ifstream& ifs);
void streamToVec (vector<Warrior>& warriors, ifstream& ifs);
void addWarrior (vector<Warrior>& warriors,const string name,const int strength);
size_t find(const vector<Warrior>& warriors, const string name);
void battle(vector<Warrior>& warriors, const string name1, const string name2);
void displayStatus (const vector<Warrior>& warriors);


//main function
int main(){
    ifstream ifs;
    vector<Warrior> warriors;

    openfile(ifs);
    streamToVec(warriors, ifs);
    ifs.close();
}

//function to open the file
void openfile(ifstream& ifs){
    //This function opens the file warriors.txt
    string fighters;
    ifs.open("warriors.txt");
}

//function that parses all the lines
//Then that function calls on the actual line parser
void streamToVec(vector<Warrior>& warriors, ifstream& ifs){
    Warrior currWar_;
    string type;

    while(ifs >> type){
        if (type == "Warrior"){
            string name;
            int strength;
            ifs >> name >> strength;
            addWarrior(warriors, name, strength);
        }
        else if (type == "Status"){
            displayStatus(warriors);
        }
        else if (type == "Battle"){
            string name1, name2;
            ifs >> name1 >> name2;
            battle(warriors, name1, name2);
        }
    }
}

//function to add a warrior object to the vector
void addWarrior(vector<Warrior>& warriors,const string name,const int strength){
    Warrior currWar_;
    size_t found = find(warriors, name);

    if (found == warriors.size()){
        currWar_.name = name;
        currWar_.strength = strength;
        warriors.push_back(currWar_);
    } else{
        cout << "There's already a warrior with that name" << endl;
    }
}

//function to return an object's index, or if not found return the size
size_t find(const vector<Warrior>& warriors, const string name){
    for (size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i].name == name){
            return i;
        }
    }
    return warriors.size();
}

//function to check and process all battle cases
void battle(vector<Warrior>& warriors, const string name1, const string name2){
    size_t warr1 = find(warriors, name1);
    size_t warr2 = find(warriors, name2);
    
    if (warr1 == warriors.size() || warr2 == warriors.size()){
        cout << "At least one of these warriors doesn't exist" << endl;
    }
    else if(warriors[warr1].strength == 0 && warriors[warr2].strength == 0){
        cout << warriors[warr1].name << " battles ";
        cout << warriors[warr2].name << endl;
        cout << "Oh No they're both dead! Yuck!" << endl;
    }
    else if (warriors[warr1].strength == warriors[warr2].strength ){
        cout << warriors[warr1].name << " battles ";
        cout << warriors[warr2].name << endl;
        warriors[warr1].strength = 0;
        warriors[warr2].strength = 0;
        cout << "Mutual Annihilation: " << warriors[warr1].name << " and ";
        cout << warriors[warr2].name << " die at each other's hands." << endl;
    }
    else if (warriors[warr1].strength == 0 && warriors[warr2].strength != 0){
        cout << warriors[warr1].name << " battles ";
        cout << warriors[warr2].name << endl;
        cout << "He's dead, " << warriors[warr2].name << endl;
    }
    else if (warriors[warr2].strength == 0 && warriors[warr1].strength != 0){
        cout << warriors[warr1].name << " battles ";
        cout << warriors[warr2].name << endl;
        cout << "He's dead, " << warriors[warr1].name << endl;
    }
    else if (warriors[warr1].strength > warriors[warr2].strength){
        cout << warriors[warr1].name << " battles ";
        cout << warriors[warr2].name << endl;
        warriors[warr1].strength -= warriors[warr2].strength;
        warriors[warr2].strength = 0;
        cout << warriors[warr1].name << " defeats ";;
        cout << warriors[warr2].name << "!" << endl;
    }
    else if (warriors[warr1].strength < warriors[warr2].strength){
        cout << warriors[warr1].name << " battles ";
        cout << warriors[warr2].name << endl;
        warriors[warr2].strength -= warriors[warr1].strength;
        warriors[warr1].strength = 0;
        cout << warriors[warr2].name << " defeats ";
        cout << warriors[warr1].name << "!" << endl;
    }
}

//function to display the status of the warriors
void displayStatus(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); ++i){
        cout << "Warrior: " << warriors[i].name << ", ";
        cout << "Strength: " << warriors[i].strength << endl;
    }
}