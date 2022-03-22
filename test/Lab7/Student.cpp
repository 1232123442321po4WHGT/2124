
#include "Student.h"
#include "Course.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {

Student::~Student() {
//for( size_t i = 0; i < courses.size(); i++ ) {
// delete courses[i];
//}
//courses.clear();
}

string Student::getName() const {
return name;
}

void Student::enroll( Course* course ) {
courses.push_back( course );
}

void Student::cancelCourse( Course* course ) {
for( size_t i = 0; i < courses.size()-1; i++ ) {
if( courses[i] == course ) {
   Course* tmpptr;
   tmpptr = courses[i+1];
   courses[i+1] = courses[i];
   courses[i] = tmpptr;
}
}
courses.pop_back();
}
  
ostream& operator<< (ostream& os, const Student& stu) {
os << stu.name << ": ";
for( size_t i = 0; i < stu.courses.size(); i++ ) {
os << stu.courses[i]->getName() << ", ";
}
return os;
}
  
}