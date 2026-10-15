#pragma once

#include "Student.h"
#include "User.h"
#include <string>

using namespace std;

class StudentManager {
private:
    string filePath;

public:
    StudentManager(const string& filePath = "data/students.txt");

    Student loadProfile(User& user);
    bool saveProfile(Student& student);
};