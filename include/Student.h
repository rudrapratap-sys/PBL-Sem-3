#pragma once

#include "User.h"

#include <string>
#include <vector>

using namespace std;

class Student : public User {
private:
    string branch;
    int year;
    double cgpa;
    string targetRole;
    string preferredCategory;
    vector<string> skills;
    vector<string> interests;

public:
    Student();
    explicit Student(const User& user);

    string getBranch();
    int getYear();
    double getCgpa();
    string getTargetRole();
    string getPreferredCategory();
    vector<string> getSkills();
    vector<string> getInterests();

    void setBranch(const string& branch);
    bool setYear(int year);
    bool setCgpa(double cgpa);
    void setTargetRole(const string& targetRole);
    void setPreferredCategory(const string& preferredCategory);
    void setSkills(const vector<string>& skills);
    void setInterests(const vector<string>& interests);

    bool addSkill(const string& skill);
    bool removeSkill(const string& skill);
    void displayProfile();
};
