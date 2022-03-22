#ifndef STUDENT_H
#define STUDENT_H
#include <vector>
#include <string>
#include <iostream>

namespace BrooklynPoly {

    class Course;

    class Student {
        friend std::ostream& operator<< (std::ostream& os, const Student& stu);
        public:
        ~Student();
        Student( std::string aName ) : name(aName) {}
        std::string getName() const;
        void enroll( Course* course );
        void cancelCourse( Course* course );
        private:
        std::vector<Course*> courses;
        std::string name;
    };
}

#endif