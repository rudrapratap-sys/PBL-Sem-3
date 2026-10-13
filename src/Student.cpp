#include "Student.h"

#include "Utils.h"

#include <iomanip>
#include <iostream>

using namespace std;

Student::Student() : year(1), cgpa(0.0), preferredCategory("Any") {
}

Student::Student(const User& user)
    : User(user),
      year(1),
      cgpa(0.0),
      preferredCategory("Any") {
}

string Student::getBranch() {
    return branch;
}

int Student::getYear() {
    return year;
}

double Student::getCgpa() {
    return cgpa;
}

string Student::getTargetRole() {
    return targetRole;
}

string Student::getPreferredCategory() {
    return preferredCategory;
}

vector<string> Student::getSkills() {
    return skills;
}

vector<string> Student::getInterests() {
    return interests;
}

void Student::setBranch(const string& branch) {
    this->branch = Utils::trim(branch);
}

bool Student::setYear(int year) {
    if (year < 1 || year > 4) {
        return false;
    }
    this->year = year;
    return true;
}

bool Student::setCgpa(double cgpa) {
    if (cgpa < 0.0 || cgpa > 10.0) {
        return false;
    }
    this->cgpa = cgpa;
    return true;
}

void Student::setTargetRole(const string& targetRole) {
    this->targetRole = Utils::trim(targetRole);
}

void Student::setPreferredCategory(const string& preferredCategory) {
    string cleaned = Utils::trim(preferredCategory);
    this->preferredCategory = cleaned.empty() ? "Any" : cleaned;
}

void Student::setSkills(const vector<string>& skills) {
    this->skills.clear();
    for (const string& skill : skills) {
        addSkill(skill);
    }
}

void Student::setInterests(const vector<string>& interests) {
    this->interests.clear();
    for (const string& interest : interests) {
        string cleaned = Utils::trim(interest);
        if (!cleaned.empty()) {
            this->interests.push_back(cleaned);
        }
    }
}

bool Student::addSkill(const string& skill) {
    string cleaned = Utils::trim(skill);
    if (cleaned.empty()) {
        return false;
    }

    for (const string& existingSkill : skills) {
        if (Utils::equalsIgnoreCase(existingSkill, cleaned)) {
            return false;
        }
    }

    skills.push_back(cleaned);
    return true;
}

bool Student::removeSkill(const string& skill) {
    for (auto it = skills.begin(); it != skills.end(); ++it) {
        if (Utils::equalsIgnoreCase(*it, skill)) {
            skills.erase(it);
            return true;
        }
    }
    return false;
}

void Student::displayProfile() {
    cout << "\n--- Student Profile ---\n";
    cout << "User ID              : " << getUserId() << "\n";
    cout << "Name                 : " << getName() << "\n";
    cout << "Email                : " << getEmail() << "\n";
    cout << "Branch               : " << (branch.empty() ? "Not added" : branch) << "\n";
    cout << "Year                 : " << year << "\n";
    cout << "CGPA                 : " << fixed << setprecision(2) << cgpa << " / 10\n";
    cout << "Target Role          : " << (targetRole.empty() ? "Not selected" : targetRole) << "\n";
    cout << "Preferred Category   : " << preferredCategory << "\n";
    cout << "Skills               : " << (skills.empty() ? "No skills added" : Utils::join(skills, ',')) << "\n";
    cout << "Interests            : " << (interests.empty() ? "No interests added" : Utils::join(interests, ',')) << "\n";
}
