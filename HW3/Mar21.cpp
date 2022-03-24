#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Operator Overloading

class Cat{
    public:
    Cat(const string& the_name, const string& the_color, double the_weight): 
    name(the_name), weight(the_weight), color(the_color){}

    private: 
    string name;
    string color;
    double weight;
};

//operator<< is a type of overloading

//operator= is a type of overloading
//checks for self assignment, free old memory if needed
//allocate new memory if needed
//copy values
//return proper type and object

//operator[] index operator
//access a specific value in a vector

//operator expressions to functions
//for instance when we do val1 + val2, we're invisibly calling a function

//pre increment operator++

/*
int main(){
    int num = 0;
    int num2 = ++num;
    //num is now 1
    //num2 is assigned 1
    cout << num << endl;
}
*/

//post increment operator++
/*
int main(){
    int num = 0;
    int num2 = num++;
    //num is now 1
    //num2 is assigned 0;
    cout << num2 << endl;
}
*/

