#include "Course.h"
#include "Student.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {

    Course::~Course() {
    }

    string Course::getName() const {
    return name;
    }

    void Course::enroll( Student* student ) {
        students.push_back( student );
    }

    void Course::cancel() {
    for( size_t i = 0; i < students.size(); i++ ) {
        students[i]->cancelCourse( this );
        students[i] = nullptr;
    }
    students.clear();
    };
    
    ostream& operator<< (ostream& os, const Course& cor) {
    os << cor.name << ": ";
    for( size_t i = 0; i < cor.students.size(); i++ ) {
    os << cor.students[i]->getName() << ", ";
    }
    return os;
    }
  
}