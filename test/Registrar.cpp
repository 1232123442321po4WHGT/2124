#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Courses: " << endl;
    for (size_t i = 0; i < rhs.courses.size(); ++i){
        os << *(rhs.courses[i]) << " ";
    }
    os << "Students: " << endl;
    for (size_t i = 0; i < rhs.students.size(); ++i){
        os << *(rhs.students[i]) << endl;
    }
    return os;
    }

    Registrar::Registrar(){}

    size_t Registrar::findCourse(const string& finder) const{
        for (size_t i = 0; i < students.size(); ++i){
            if (finder == students[i]->getName()){
                return i;
            }
        }
        return students.size();
    }

    size_t Registrar::findStudent(const string& finder) const{
        for (size_t i = 0; i < courses.size(); ++i){
            if (finder == courses[i]->getName()){
                return i;
            }
        }
        return courses.size();
    }

    bool Registrar::addCourse(const string& clss){
        if (this->findCourse(clss) == courses.size()){
            courses.push_back(new Course(clss));
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const string& std){
        if (this->findStudent(std) == students.size()){
            students.push_back(new Student(std));
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
        size_t coursIdx = findCourse(courseName);
        size_t stdIdx = findStudent(studentName);

        if (coursIdx == courses.size() || stdIdx == students.size()){
            cout << "Student or course doesn't exist"; 
            return false;
        }
        courses[coursIdx]-> addStudent(students[stdIdx]);
        students[stdIdx]-> addCourse(courses[coursIdx]);
        return true;
    }

    bool Registrar::cancelCourse(const string& courseName){
        size_t coursIdx = findCourse(courseName);

        if (coursIdx == courses.size()){
            cout << "Course not found" << endl;
            return false;
        }
        courses[coursIdx]-> removeStudentsFromCourse();
        courses[coursIdx] = courses[courses.size()-1];
        courses.pop_back();
        return true;
    }

    void Registrar::purge(){
        for (size_t i = 0; i < courses.size(); ++i){
            delete courses[i];
        }
        while (courses.size() > 0){
            courses.pop_back();
        }

        for (size_t i = 0; i < students.size(); ++i){
            delete students[i];
        }
        while(students.size() > 0){
            students.pop_back();
        }
    }
}