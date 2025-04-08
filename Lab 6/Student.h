#pragma once
#include "Course.h"
#include <iostream>
#include <string>
using namespace std;

// Staff class definition
class Staff {
protected:
    string name;
    int age;

public:
    Staff(const string& name, int age) : name(name), age(age) {}
    virtual ~Staff() = default;

    string getName() const { return name; }
    int getAge() const { return age; }

    virtual void printInfo() const = 0;  // Pure virtual method
};

// Student class definition
class Student : public Staff {
private:
    int studentId;

public:
    Student(const string& name, int age, int studentId)
        : Staff(name, age), studentId(studentId) {
    }

    int getStudentId() const { return studentId; }

    void printInfo() const override {
        cout << "Student Name: " << name
            << "\nAge: " << age
            << "\nStudent ID: " << studentId << endl;
    }
};

// Professor class definition
class Professor : public Staff {
private:
    string subject;
    int experience;

public:
    Professor(const string& name, int age, const string& subject, int experience)
        : Staff(name, age), subject(subject), experience(experience) {
    }

    string getSubject() const { return subject; }
    int getExperience() const { return experience; }

    void printInfo() const override {
        cout << "Professor Name: " << name
            << "\nAge: " << age
            << "\nSubject: " << subject
            << "\nExperience: " << experience << " years" << endl;
    }
};
