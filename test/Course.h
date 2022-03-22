#ifndef COURSE_H
#define COURSE_H
#include <vector>
#include <string>
#include <iostream>

namespace BrooklynPoly{
    class Student;

    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        // Course methods nxeded by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student*);
        void removeStudentsFromCourse(); 
        size_t studFinder(Student* std);

    private:
        std::string name;
        std::vector<Student*> students;
    };
}

#endif