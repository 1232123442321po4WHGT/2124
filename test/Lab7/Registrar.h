#ifndef REGISTRAR_H
#define REGISTRAR_H
#include <vector>
#include <string>
#include <iostream>

namespace BrooklynPoly {

class Course;
class Student;

class Registrar {
friend std::ostream& operator<< (std::ostream& os, const Registrar& reg);
public:
~Registrar();
void addCourse( const std::string& name );
void addStudent( const std::string& name );
void enrollStudentInCourse( const std::string& student, const std::string& course );
void cancelCourse( const std::string& course );
void purge();
private:
std::vector<Course*> courses;
std::vector<Student*> students;
};

}

#endif

