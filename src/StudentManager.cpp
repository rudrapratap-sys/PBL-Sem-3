#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class StudentManager {
private:
    string filePath;

public:

    StudentManager(const string& filePath = "students.txt") {
        this->filePath = filePath;
    }

    Student loadProfile(User& user) {
        Student student(user);

        ifstream file(filePath);
        string line;

        while (getline(file, line)) {
            vector<string> parts = Helper::split(line, '|');

            if (parts.size() < 8)
                continue;

            if (parts[0] == user.getUserId()) {
                student.setBranch(parts[1]);
                student.setYear(stoi(parts[2]));
                student.setCgpa(stod(parts[3]));
                student.setTargetRole(parts[4]);
                student.setPreferredCategory(parts[5]);

                student.setSkills(parts[6]);

                student.setInterests(
                    Helper::splitAndTrim(parts[7], ',')
                );

                return student;
            }
        }

        return student;
    }

    bool saveProfile(Student& student) {
        vector<string> lines;
        string line;
        bool found = false;

        ifstream file(filePath);

        while (getline(file, line)) {
            vector<string> parts = Helper::split(line, '|');

            if (!parts.empty() && parts[0] == student.getUserId()) {
                found = true;
                continue;
            }

            lines.push_back(line);
        }

        file.close();

        stringstream data;

        data << student.getUserId() << "|"
             << student.getBranch() << "|"
             << student.getYear() << "|"
             << fixed << setprecision(2) << student.getCgpa() << "|"
             << student.getTargetRole() << "|"
             << student.getPreferredCategory() << "|";

        auto skills = student.getSkills();

        for (auto it = skills.begin(); it != skills.end(); ++it) {
            data << it->first << ":" << it->second;

            auto next = it;
            ++next;

            if (next != skills.end())
                data << ", ";
        }

        data << "|";

        data << Helper::join(student.getInterests(), ',');

        lines.push_back(data.str());

        ofstream output(filePath);

        if (!output)
            return false;

        for (int i = 0; i < lines.size(); i++) {
            output << lines[i] << "\n";
        }

        return true;
    }
};
