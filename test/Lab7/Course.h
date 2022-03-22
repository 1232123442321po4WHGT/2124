#ifndef COURSE_H
#define COURSE_H
#include <vector>
#include <string>
#include <iostream>

namespace BrooklynPoly {

    class Student;

    class Course {
        friend std::ostream& operator<< (std::ostream& os, const Course& cor);
        public:
        ~Course();
        Course( std::string aName ) : name(aName) {}
        std::string getName() const;
        void enroll( Student* student );
        void cancel();
        
        private:
        std::vector<Student*> students;
        std::string name;
    };

}

#endif

