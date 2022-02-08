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

struct Warrior{
    string type;
    string name;
    int strength;
};

void openfile (ifstream& ifs);
void streamToVec (vector<Warrior>& warriors, ifstream& ifs);
void addWarrior (vector<Warrior>& warriors, ifstream& ifs, string name, int strength);
void displayStatus (vector<Warrior>& warriors);


int main(){
    ifstream ifs;
    vector<Warrior> warriors;

    
    openfile(ifs);
    streamToVec(warriors, ifs);
}

void openfile(ifstream& ifs){
    //This function opens the file warriors.txt
    string fighters;
    ifs.open("warriors.txt");
}
/*
void streamToVec(vector<HC>& hydrocarbons, ifstream& ifs){
    //cout << "streamtovec" << endl;
    HC currChem_;
    string chem;
    char c, h;
    int cc, hc;

    while (ifs >> chem >> c >> cc >> h >> hc)
    {
        currChem_.names.push_back(chem);
        currChem_.carbons = cc;
        currChem_.hydros = hc;
        insert(hydrocarbons, chem, cc, hc);
    }
    //hydrocarbons.push_back(currChem_);
}
*/

//function that parses all the lines
//Then that function calls on the actual line parser
void streamToVec(vector<Warrior>& warriors, ifstream& ifs){
    Warrior currWar_;
    string type;

    while(ifs >> type){
        //cout << "reading" << endl;
        if (type == "Warrior"){
            string name;
            int strength;
            cout << "Warrior" << endl;
            ifs >> name >> strength;
            addWarrior(warriors, ifs, name, strength);

            /*
            while(ifs >> name >> strength){
                currWar_.name = name;
                currWar_.strength = strength;
                warriors.push_back(currWar_);
            }
            */

            //addWarrior(warriors, ifs);
        }
        
        /*
        else if (type == "Status"){
            displayStatus(warriors);
        }
        else if (type == "Battle"){
            battle(warriors);
        }
        */
    }
}

void addWarrior(vector<Warrior>& warriors, ifstream& ifs, string name, int strength){
    Warrior currWar_;
    /*
    string name;
    int strength;
    */

    currWar_.name = name;
    currWar_.strength = strength;
    /*
    while(ifs >> name >> strength){
        currWar_.name = name;
        currWar_.strength = strength;
    }*/

}

void displayStatus(vector<Warrior>& warriors){
    for(size_t i = 0; i < warriors.size(); ++i){
        cout << "this" << endl;
        cout << warriors[i].name << warriors[i].strength << endl;
    }
}