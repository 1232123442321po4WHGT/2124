#include "Course.h"
#include "Student.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.getName() << endl;
    if (rhs.students.size() == 0){
        os << "No students in the course!" << endl;
    }
    else{
        for (size_t i = 0; i < rhs.students.size();++i){
            os << rhs.students[i]->getName() << endl;
        }
    }
    return os;
    }

    size_t Course::studFinder(Student* std){
    for (size_t i = 0; i < students.size(); ++i){
        if (students[i] == std){
            return i;
        }
    }
    return students.size();
    }

    Course::Course(const string& courseName){
        this->name = courseName;
    }

    const string& Course::getName() const{
        return this->name;
    }

    bool Course::addStudent(Student* std){
        size_t idx = studFinder(std);
        if (idx == students.size()){
            students.push_back(std);
            return true;
        }
        return false;
    }

    void Course::removeStudentsFromCourse(){
        for (size_t i = 0; i < students.size(); ++i){
            students[i]->removedFromCourse(this);
        }
        while (students.size() != 0){
            students.pop_back();
        }
    }
}