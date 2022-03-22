#include "Student.h"
#include "Course.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.getName() << ": " << endl;
    if (rhs.courses.size() == 0){
        os << "There are no courses!" << endl;
    }
    else{
        for (size_t i = 0; i < rhs.courses.size(); ++i){
            os << rhs.courses[i]->getName() << endl;
        }
    }
    return os;
    }

    Student::Student(const string& name){
    this->name = name;
    }

    const string& Student::getName() const{
        return this->name;
    }

    bool Student::addCourse(Course* clss){
        size_t cidx = coursFinder(clss);
        if (cidx == courses.size()){
            courses.push_back(clss);
            return true;
        }
        return false;
    }

    void Student::removedFromCourse(Course* clss){
        for (size_t i = 0; i < courses.size(); ++i){
            if (courses[i] == clss){
                courses[i] = courses[courses.size()-1];
            }
        }
        courses.pop_back();
    }

    size_t Student::coursFinder(Course* cours){
        for (size_t i = 0; i < courses.size(); ++i){
            if (cours == courses[i]){
                return i;
            }
        }
        return courses.size();
    }

}