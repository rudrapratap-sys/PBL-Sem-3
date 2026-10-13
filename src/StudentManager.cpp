#include "StudentManager.h"

#include "Utils.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

StudentManager::StudentManager(const string& filePath) : filePath(filePath) {
}

Student StudentManager::loadProfile(User& user) {
    Student student(user);

    ifstream file(filePath);
    if (!file) {
        return student;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts = Utils::split(line, '|');
        if (parts.size() >= 8 && parts[0] == user.getUserId()) {
            student.setBranch(parts[1]);

            try {
                student.setYear(stoi(parts[2]));
            } catch (...) {
                student.setYear(1);
            }

            try {
                student.setCgpa(stod(parts[3]));
            } catch (...) {
                student.setCgpa(0.0);
            }

            student.setTargetRole(parts[4]);
            student.setPreferredCategory(parts[5]);
            student.setSkills(Utils::splitAndTrim(parts[6], ','));
            student.setInterests(Utils::splitAndTrim(parts[7], ','));
            return student;
        }
    }

    return student;
}

bool StudentManager::saveProfile(Student& student) {
    vector<string> lines;
    bool updated = false;

    ifstream input(filePath);
    string line;
    while (getline(input, line)) {
        vector<string> parts = Utils::split(line, '|');
        if (!parts.empty() && parts[0] == student.getUserId()) {
            updated = true;
            continue;
        }
        lines.push_back(line);
    }

    stringstream profileLine;
    profileLine << student.getUserId() << "|"
                << student.getBranch() << "|"
                << student.getYear() << "|"
                << fixed << setprecision(2) << student.getCgpa() << "|"
                << student.getTargetRole() << "|"
                << student.getPreferredCategory() << "|"
                << Utils::join(student.getSkills(), ',') << "|"
                << Utils::join(student.getInterests(), ',');

    lines.push_back(profileLine.str());

    ofstream output(filePath);
    if (!output) {
        return false;
    }

    for (string& savedLine : lines) {
        output << savedLine << "\n";
    }

    return updated || true;
}
