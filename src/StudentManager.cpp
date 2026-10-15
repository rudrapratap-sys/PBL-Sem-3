#include "StudentManager.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

StudentManager::StudentManager(const string& filePath) {
    this->filePath = filePath;
}

Student StudentManager::loadProfile(User& user) {
    Student student(user);

    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        vector<string> parts = Utils::split(line, '|');

        if (parts.size() < 8)
            continue;

        if (parts[0] == user.getUserId()) {
            student.setBranch(parts[1]);
            student.setYear(stoi(parts[2]));
            student.setCgpa(stod(parts[3]));
            student.setTargetRole(parts[4]);
            student.setPreferredCategory(parts[5]);

            // Skills are stored as "Python:5, C++:8"
            student.setSkills(parts[6]);

            // Load interests
            student.setInterests(
                Utils::splitAndTrim(parts[7], ',')
            );

            return student;
        }
    }

    return student;
}

bool StudentManager::saveProfile(Student& student) {
    vector<string> lines;
    string line;
    bool found = false;

    // Read existing profiles
    ifstream file(filePath);

    while (getline(file, line)) {
        vector<string> parts = Utils::split(line, '|');

        if (!parts.empty() && parts[0] == student.getUserId()) {
            found = true;
            continue;
        }

        lines.push_back(line);
    }

    file.close();

    // Create the profile line
    stringstream data;

    data << student.getUserId() << "|"
         << student.getBranch() << "|"
         << student.getYear() << "|"
         << fixed << setprecision(2) << student.getCgpa() << "|"
         << student.getTargetRole() << "|"
         << student.getPreferredCategory() << "|";

    // Save skills with their proficiency scores
    auto skills = student.getSkills();

    for (auto it = skills.begin(); it != skills.end(); ++it) {
        data << it->first << ":" << it->second;

        auto next = it;
        ++next;

        if (next != skills.end())
            data << ", ";
    }

    data << "|";

    // Save interests
    data << Utils::join(student.getInterests(), ',');

    // Add the updated profile
    lines.push_back(data.str());

    // Write all profiles back to the file
    ofstream output(filePath);

    if (!output)
        return false;

    for (int i = 0; i < lines.size(); i++) {
        output << lines[i] << "\n";
    }

    return true;
}