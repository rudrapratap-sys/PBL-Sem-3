
#pragma once

#include "User.h"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Student : public User {
private:
    string branch;
    int year;
    double cgpa;
    string targetRole;
    string preferredCategory;

    // Skill name -> proficiency score (0 to 10)
    unordered_map<string, int> skills;

    vector<string> interests;

public:
    // Constructors
    Student();
    explicit Student(const User& user);

    // Getters
    string getBranch();
    int getYear();
    double getCgpa();
    string getTargetRole();
    string getPreferredCategory();

    unordered_map<string, int> getSkills();
    vector<string> getInterests();
    bool predictOpportunities();

    // Setters
    void setBranch(const string& branch);
    bool setYear(int year);
    bool setCgpa(double cgpa);
    void setTargetRole(const string& targetRole);
    void setPreferredCategory(const string& preferredCategory);

    // Takes input like "Python:5, C:3, C++:9"
    void setSkills(const string& input);

    void setInterests(const vector<string>& interests);

    // Skill management
    bool addSkill(const string& skill, int proficiency);
    bool removeSkill(const string& skill);

    // Display profile
    void displayProfile();
};
