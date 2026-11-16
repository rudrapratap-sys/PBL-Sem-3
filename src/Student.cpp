
#include <iostream>
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
    unordered_map<string, int> skills;
    vector<string> interests;

public:

    Student() {
        this->year = 1;
        this->cgpa = 0.0;
        this->preferredCategory = "Any";
    }

    Student(const User& user) : User(user) {
        this->year = 1;
        this->cgpa = 0.0;
        this->preferredCategory = "Any";
    }


    string getBranch() {
        return branch;
    }

    int getYear() {
        return year;
    }

    double getCgpa() {
        return cgpa;
    }

    string getTargetRole() {
        return targetRole;
    }

    string getPreferredCategory() {
        return preferredCategory;
    }

    unordered_map<string, int> getSkills() {
        return skills;
    }

    vector<string> getInterests() {
        return interests;
    }

    void setBranch(const string& branch) {
        this->branch = Helper::trim(branch);
    }

    bool setYear(int year) {
        if (year < 1 || year > 4) {
            return false;
        }

        this->year = year;
        return true;
    }

    bool setCgpa(double cgpa) {
        if (cgpa < 0.0 || cgpa > 10.0) {
            return false;
        }

        this->cgpa = cgpa;
        return true;
    }

    void setTargetRole(const string& targetRole) {
        this->targetRole = Helper::trim(targetRole);
    }

    void setPreferredCategory(const string& preferredCategory) {
        string cleaned = Helper::trim(preferredCategory);

        if (cleaned.empty()) {
            this->preferredCategory = "Any";
        } else {
            this->preferredCategory = cleaned;
        }
    }

    void setSkills(const string& input) {
        skills.clear();

        vector<string> skillList = Helper::split(input, ',');

        for (string item : skillList) {
            vector<string> parts = Helper::split(item, ':');

            if (parts.size() != 2) {
                continue;
            }

            string name = Helper::trim(parts[0]);
            string scoreText = Helper::trim(parts[1]);

            if (name.empty() || scoreText.empty()) {
                continue;
            }

            int score;

            try {
                score = stoi(scoreText);
            } catch (...) {
                continue;
            }

            if (score >= 0 && score <= 10) {
                addSkill(name, score);
            }
        }
    }

    void setInterests(const vector<string>& interests) {
        this->interests.clear();

        for (const string& interest : interests) {
            string cleaned = Helper::trim(interest);

            if (!cleaned.empty()) {
                this->interests.push_back(cleaned);
            }
        }
    }

    bool addSkill(const string& skill, int proficiency) {
        string name = Helper::trim(skill);

        if (name.empty() || proficiency < 0 || proficiency > 10) {
            return false;
        }

        for (const auto& existing : skills) {
            if (Helper::compare(existing.first, name)) {
                return false;
            }
        }

        skills[name] = proficiency;
        return true;
    }

    bool removeSkill(const string& skill) {
        for (auto it = skills.begin(); it != skills.end(); ++it) {
            if (Helper::compare(it->first, skill)) {
                skills.erase(it);
                return true;
            }
        }

        return false;
    }

    void displayProfile() {
        cout << "\n--- Student Profile ---\n";

        cout << "User ID              : " << getUserId() << "\n";
        cout << "Name                 : " << getName() << "\n";
        cout << "Email                : " << getEmail() << "\n";

        cout << "Branch               : "
             << (branch.empty() ? "Not added" : branch) << "\n";

        cout << "Year                 : " << year << "\n";

        cout << "CGPA                 : " << fixed
             << setprecision(2) << cgpa << " / 10\n";

        cout << "Target Role          : "
             << (targetRole.empty() ? "Not selected" : targetRole) << "\n";

        cout << "Preferred Category   : " << preferredCategory << "\n";

        cout << "Skills:\n";

        if (skills.empty()) {
            cout << "No skills added\n";
        } else {
            for (const auto& skill : skills) {
                cout << skill.first << " : "
                     << skill.second << "/10\n";
            }
        }

        cout << "Interests            : ";

        if (interests.empty()) {
            cout << "No interests added\n";
        } else {
            cout << Helper::join(interests, ',');
        }

        cout << "\n";
    }
};
