/*
  rec07_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.

  Alex Zhao Recitation 07
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;
class Registrar;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
    public:
    // Course methods nxeded by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse(); 
    size_t studFinder(Student* std);

    private:
    string name;
    vector<Student*> students;
};



class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
    public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);
    size_t coursFinder(Course* cours);

    private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
    public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

    private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

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

size_t Course::studFinder(Student* std){
    for (size_t i = 0; i < students.size(); ++i){
        if (students[i] == std){
            return i;
        }
    }
    return students.size();
}

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

Course::Course(const string& courseName){
    this->name = courseName;
}

const string& Course::getName() const{
    return this->name;
}

bool Course::addStudent(Student* std){
    //cout << "Adding student" << endl;
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

Student::Student(const string& name){
    this->name = name;
}

const string& Student::getName() const{
    return this->name;
}

bool Student::addCourse(Course* clss){
    //cout << "Addin course" << endl;
    size_t cidx = coursFinder(clss);
    if (cidx == courses.size()){
        courses.push_back(clss);
        return true;
    }
    return false;
}

void Student::removedFromCourse(Course* clss){
    int foundidx;
    for (size_t i = 0; i < courses.size();++i){
        if (clss == courses[i]){
            foundidx = i;
        }
    }
    for (size_t i = foundidx; i < (courses.size()-1); ++i){
        courses[i] = courses[i+1];
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
    //cout << "Entered" << endl;
    size_t coursIdx = findCourse(courseName);
    size_t stdIdx = findStudent(studentName);
    //cout << coursIdx << " " << stdIdx << endl;

    if (coursIdx == courses.size() || stdIdx == students.size()){
        cout << "Student or course doesn't exist"; 
        return false;
    }
    courses[coursIdx]->addStudent(students[stdIdx]);
    students[stdIdx]->addCourse(courses[coursIdx]);
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

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
    
   

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
    
}