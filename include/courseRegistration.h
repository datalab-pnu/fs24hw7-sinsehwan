#ifndef CR
#define CR

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "student.h"
#include "ioBuffer.h"

using namespace std;

class CourseRegistration
{
    private:
        int courseID = 0;
        vector<int> studentID;
        int creditHours = 0;
        vector<string> courseGrade;
        // 8장 추가
        int semester = 0;
        int studentIndex = 0;
    public:
        CourseRegistration() = default;
        CourseRegistration(int cID, int c, int smst) : courseID(cID), creditHours(c), semester(smst){}

        void setCourseID(int i){ courseID = i; }
        int getCourseID(){ return courseID; }
        int getCourseID() const { return courseID; }
        // register student
        void addStudent(Student s);
        void addStudent(int sID, string grade);
        vector<int>& getStudentID() { return studentID; }
        const vector<int>& getStudentID() const { return studentID; }

        void setCreditHours(int c) {creditHours = c;}
        int getCreditHours(){ return creditHours; }
        int getCreditHours() const { return creditHours; }

        void setCourseGrade(int studentID, string grade);
        vector<string>& getCourseGrade() { return courseGrade; }
        const vector<string>& getCourseGrade() const { return courseGrade; }

        friend ostream& operator<<(ostream& ostr, const CourseRegistration& c);
        friend istream& operator>>(istream& istr, CourseRegistration& c);

        int Pack(IOBuffer& Buffer) const;
        int Unpack(IOBuffer& Buffer);

        void clear();

        char * Key () const; // return key of object

        // 8장 추가 코드
        ostream& printStudentLine(ostream& stream, int sid = -1, int smst = -1);
        // 다음 학생 id반환. 없으면 -1반환
        int getNextSID();
};

#endif