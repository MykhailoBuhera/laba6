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

int main() {
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
                    cout << "4 Exit" << endl;
                    cout << "Choose operation";
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
                        break;
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
                cout << "2 Exit" << endl;
                cout << "Choose operation ";
                cin >> choice;

                if (choice == 1) {
                    viewCourses(courses);
                    logUserAction("Student viewed courses");
                }
                else if (choice == 2) {
                    break;
                }
                else {
                    cout << "Invalid option Try agai\n";
                }
            }
        }
        else {
            cout << "Exiting program..." << endl;
        }
    }
    catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}