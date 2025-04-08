#pragma once
#include <string>

class Course {
private:
    std::string name;   // Назва курсу
    std::string code;   // Код курсу
    int credits;        // Кількість кредитів

public:
    // Конструктор класу
    Course(const std::string& courseName, const std::string& courseCode, int courseCredits)
        : name(courseName), code(courseCode), credits(courseCredits) {
    }

    // Методи для отримання даних курсу
    std::string getCode() const { return code; }
    std::string getName() const { return name; }
    int getCredits() const { return credits; }
};
