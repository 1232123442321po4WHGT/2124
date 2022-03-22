#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {

    Registrar::~Registrar() {
    for( size_t i = 0; i < courses.size(); i++ ) {
        delete courses[i];
        courses[i] = NULL;
    }
    courses.clear();
    for( size_t i = 0; i < students.size(); i++ ) {
        delete students[i];
        students[i] = NULL;
        }
        students.clear();
    }

    void Registrar::addStudent( const string& name ) {
        Student* stu = new Student( name );
        students.push_back( stu );
    }

    void Registrar::addCourse( const string& name ) {
        Course* cor = new Course( name );
        courses.push_back( cor );
    }

    void Registrar::enrollStudentInCourse( const string& student, const string& course ) {
        Student* stuptr = nullptr;
        Course* corptr = nullptr;
        for( size_t i = 0; i < courses.size(); i++ ) {
            if( courses[i]->getName() == course ) {
                corptr = courses[i];
                break;
            }
        }
        for( size_t i = 0; i < students.size(); i++ ) {
            if( students[i]->getName() == student ) {
                stuptr = students[i];
                break;
            }
        }
        if( stuptr != nullptr && corptr != nullptr ) {
            stuptr->enroll(corptr);
            corptr->enroll(stuptr);
        }
    }

    void Registrar::cancelCourse( const string& course ) {
        Course* corptr = nullptr;
        for( size_t i = 0; i < courses.size(); i++ ) {
            if( courses[i]->getName() == course ) {
                corptr = courses[i];
                break;
            }
        }
        if( corptr != nullptr ) {
            corptr->cancel();
            for( size_t i = 0; i < courses.size()-1; i++ ) {
                if( courses[i]->getName() == course ) {
                    Course* tmpptr;
                    tmpptr = courses[++i];
                    courses[++i] = courses[i];
                    courses[i] = tmpptr;
                }
            }
            courses.pop_back();
        }
    }

    void Registrar::purge() {
        for( size_t i = 0; i < courses.size(); i++ ) {
            delete courses[i];
            courses[i] = NULL;
        }
        courses.clear();

        for( size_t i = 0; i < students.size(); i++ ) {
            delete students[i];
            students[i] = NULL;
        }
        students.clear();
    }

    ostream& operator<< (ostream& os, const Registrar& reg) {
    os << "Courses:" << endl;
    for( size_t i = 0; i < reg.courses.size(); i++ ) {
        os << '\t' << *reg.courses[i] << endl;
    }
    os << "Students:" << endl;
    for( size_t i = 0; i < reg.students.size(); i++ ) {
        os << '\t' << *reg.students[i] << endl;
    }
    return os;
    }
  
}