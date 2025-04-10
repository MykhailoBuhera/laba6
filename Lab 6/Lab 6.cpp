// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Student.h"
#include "Course.h"
#include "Grade.h"
using namespace std;

vector<Course> loadCoursesFromFile() {
    vector<Course> courses;
    ifstream file("courses.txt");
    if (!file) return courses; // return empty if file not found
    string code, name;
    int credits;
    while (file >> code >> name >> credits) {
        courses.push_back(Course(code, name, credits));
    }
    return courses;
}

void saveAllCoursesToFile(const vector<Course>& courses) {
    ofstream file("courses.txt", ios::trunc);
    if (!file) throw runtime_error("Cannot open course file for writing");
    for (const auto& course : courses) {
        file << course.getCode() << " " << course.getName() << " " << course.getCredits() << endl;
    }
    file.close();
}

void logUserAction(const string& action) {
    ofstream log("history.txt", ios::app);
    if (!log) throw runtime_error("Cannot open history log");
    log << action << endl;
    log.close();
}

void viewCourses(const vector<Course>& courses) {
    cout << "\n--- Courses ---\n";
    for (const auto& course : courses) {
        cout << "Name " << course.getName()
            << ", Code " << course.getCode()
            << ", Credits " << course.getCredits() << endl;
    }
}
void saveAllStudentsToFile(const vector<Student>& students) {
    ofstream file("students.txt", ios::trunc);
    if (!file) throw runtime_error("Cannot open students file");
    for (const auto& s : students) {
        file << s.getName() << " " << s.getAge() << " " << s.getStudentId() << endl;
    }
}
vector<Student> loadStudentsFromFile() {
    vector<Student> students;
    ifstream file("students.txt");
    if (!file) return students;
    string name;
    int age, id;
    while (file >> name >> age >> id) {
        students.push_back(Student(name, age, id));
    }
    return students;
}
void saveAllProfessorsToFile(const vector<Professor>& professors) {
    ofstream file("profesor.txt", ios::trunc);
    if (!file) throw runtime_error("Cannot open professors file");
    for (const auto& p : professors) {
        file << p.getName() << " " << p.getAge() << " "
            << p.getSubject() << " " << p.getExperience() << endl;
    }
}
vector<Professor> loadProfessorsFromFile() {
    vector<Professor> professors;
    ifstream file("profesor.txt");
    if (!file) return professors;
    string name, subject;
    int age, experience;
    while (file >> name >> age >> subject >> experience) {
        professors.push_back(Professor(name, age, subject, experience));
    }
    return professors;
}

int main() {
    vector<Student> students = loadStudentsFromFile();
    vector<Professor> professors = loadProfessorsFromFile();
    string password;
    int choice = 0;
    vector<Course> courses = loadCoursesFromFile();

    try {
        cout << "_________________________________" << endl;
        cout << "Student Information System" << endl;
        cout << "0 EXIT" << endl;
        cout << "1 Admin menu" << endl;
        cout << "2 Student menu" << endl;
        cout << "Choose operation " << endl;
        cout << "_________________________________" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the password: \n";
            cin >> password;
            if (password == "admin1") {
                while (true) {
                    cout << "\nAdmin Menu" << endl;
                    cout << "1 Add new course" << endl;
                    cout << "2 View all courses" << endl;
                    cout << "3 Delete course" << endl;
                    cout << "4 Add new student" << endl;
                    cout << "5 view all student" << endl;
                    cout << "6 delet student" << endl;
                    cout << "7 Add new profesor" << endl;
                    cout << "8 view all profesor" << endl;
                    cout << "9 Delet profesor" << endl;
                    cout << "10 Exit" << endl;
                    cout << "Choose operation\n";
                    cin >> choice;

                    if (choice == 1) {
                        string courseCode, courseName;
                        int courseCredits;
                        cout << "Enter course code ";
                        cin >> courseCode;
                        auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
                            return c.getCode() == courseCode;
                            });
                        if (it != courses.end()) {
                            cout << "Course with this code already exists" << endl;
                            continue;
                        }
                        cout << "Enter course name ";
                        cin >> courseName;
                        cout << "Enter course credits ";
                        cin >> courseCredits;

                        Course course(courseCode, courseName, courseCredits);
                        courses.push_back(course);
                        cout << "Saving courses to file..." << endl;
                        saveAllCoursesToFile(courses);
                        cout << "Course saved" << endl;
                        logUserAction("Course added" + courseCode);
                    }
                    else if (choice == 2) {
                        viewCourses(courses);
                    }
                    else if (choice == 3) {
                        string courseCode;
                        cout << "Enter course code to delete ";
                        cin >> courseCode;
                        auto it = remove_if(courses.begin(), courses.end(), [&](const Course& c) {
                            return c.getCode() == courseCode;
                            });
                        if (it != courses.end()) {
                            courses.erase(it, courses.end());
                            saveAllCoursesToFile(courses);
                            cout << "Course delete" << endl;
                            logUserAction("Admin deleted course " + courseCode);
                        }
                        else {
                            cout << "Course not find" << endl;
                        }
                    }
                    else if (choice == 4) {
                        string name;
                        int age, id;
                        cout << "Enter student name: ";
                        cin >> name;
                        cout << "Enter student age: ";
                        cin >> age;
                        cout << "Enter student ID: ";
                        cin >> id;

                        students.push_back(Student(name, age, id));
                        saveAllStudentsToFile(students);
                        cout << "Student added.\n";
                        logUserAction("Admin added student " + name);
                    }
                    else if (choice == 5) {
                        cout << "\n--- All Students ---\n";
                        for (const auto& student : students) {
                            student.printInfo();
                            cout << "---------------------\n";
                        }
                        logUserAction("Admin viewed all students");
                    }
                    else if (choice == 6) {
                        int id;
                        cout << "Enter student ID to delete: ";
                        cin >> id;
                        auto it = remove_if(students.begin(), students.end(), [&](const Student& s) {
                            return s.getStudentId() == id;
                            });
                        if (it != students.end()) {
                            students.erase(it, students.end());
                            saveAllStudentsToFile(students);
                            cout << "Student deleted.\n";
                            logUserAction("Admin deleted student ID " + to_string(id));
                        }
                        else {
                            cout << "Student not found.\n";
                        }
                    }
                    else if (choice == 7) {
                        string name, subject;
                        int age, experience;
                        cout << "Enter professor name: ";
                        cin >> name;
                        cout << "Enter professor age: ";
                        cin >> age;
                        cout << "Enter professor subject: ";
                        cin >> subject;
                        cout << "Enter years of experience: ";
                        cin >> experience;

                        professors.push_back(Professor(name, age, subject, experience));
                        saveAllProfessorsToFile(professors);
                        cout << "Professor added.\n";
                        logUserAction("Admin added professor " + name);
                    }
                    else if (choice == 8) {
                        cout << "\n--- All Professors ---\n";
                        for (const auto& prof : professors) {
                            prof.printInfo();
                            cout << "-----------------------\n";
                        }
                        logUserAction("Admin viewed all professors");
                    }

                    else if (choice == 9) {
                        string name;
                        cout << "Enter professor name to delete: ";
                        cin >> name;
                        auto it = remove_if(professors.begin(), professors.end(), [&](const Professor& p) {
                            return p.getName() == name;
                            });
                        if (it != professors.end()) {
                            professors.erase(it, professors.end());
                            saveAllProfessorsToFile(professors);
                            cout << "Professor deleted.\n";
                            logUserAction("Admin deleted professor " + name);
                        }
                        else {
                            cout << "Professor not found.\n";
                        }
                    }

                    else {
                        cout << "Invalid option Try again\n";
                    }
                }
            }
            else {
                cout << "wrong password!!!!!!!!!" << endl;
            }
        }
        else if (choice == 2) {
            while (true) {
                cout << "\nStudent Menu" << endl;
                cout << "1 View available courses" << endl;
                cout << "2 view profesor" << endl;
                cout << "3 Exit" << endl;
                cout << "Choose operation ";
                cin >> choice;

                if (choice == 1) {
                    viewCourses(courses);
                    logUserAction("Student viewed courses");
                }
                else if (choice == 2) {
                    cout << "\n--- All Professors ---\n";
                    for (const auto& prof : professors) {
                        prof.printInfo();
                        cout << "-----------------------\n";
                    }
                    logUserAction("Student viewed all professors");
                }
                else if (choice == 3) {
                    break;
                }
                else {
                    cout << "Invalid option Try agai\n";
                }
            }
        }
        else {
            cout << "Exiting program" << endl;
        }
    }
    catch (exception& e) {
        cerr << "Error " << e.what() << endl;
    }

    return 0;
}