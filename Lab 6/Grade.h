#pragma once

#include <iostream>
#include <string>
using namespace std;

class Grade {
private:
    string courseCode;
    int studentId;
    float grade;

public:
    Grade() = default;
    Grade(const string& courseCode, int studentId, float grade);

    string getCourseCode() const;
    int getStudentId() const;
    float getGrade() const;
};
