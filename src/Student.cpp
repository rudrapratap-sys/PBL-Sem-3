
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>

#include "Utils.cpp"
#include "User.cpp"

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

    // Default constructor
    Student() : year(1), cgpa(0.0), preferredCategory("Any") {
    }

    // Constructor using existing User information
    Student(const User& user)
        : User(user), year(1), cgpa(0.0), preferredCategory("Any") {
    }

    bool predictOpportunities() {
        // The opportunity filter writes the profile and skills to filtered.json.
        int result = system("python prediction.py");

        if (result != 0) {
            cout << "Prediction failed.\n";
            return false;
        }

        cout << "Recommendations displayed above.\n";
        return true;
    }

    // Getters
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

    // Setters
    void setBranch(const string& branch) {
        this->branch = Utils::trim(branch);
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
        this->targetRole = Utils::trim(targetRole);
    }

    void setPreferredCategory(const string& preferredCategory) {
        string cleaned = Utils::trim(preferredCategory);

        if (cleaned.empty()) {
            this->preferredCategory = "Any";
        } else {
            this->preferredCategory = cleaned;
        }
    }

    // Input format: Python:5, C:3, C++:9
    void setSkills(const string& input) {
        skills.clear();

        // Split the complete input at commas
        vector<string> skillList = Utils::split(input, ',');

        for (string item : skillList) {
            // Split each skill entry at the colon
            vector<string> parts = Utils::split(item, ':');

            // Every entry must contain a name and score
            if (parts.size() != 2) {
                continue;
            }

            string name = Utils::trim(parts[0]);
            string scoreText = Utils::trim(parts[1]);

            if (name.empty() || scoreText.empty()) {
                continue;
            }

            // Convert the score from string to integer
            int score;

            try {
                score = stoi(scoreText);
            } catch (...) {
                continue;
            }

            // Accept proficiency scores from 0 to 10
            if (score >= 0 && score <= 10) {
                addSkill(name, score);
            }
        }
    }

    void setInterests(const vector<string>& interests) {
        this->interests.clear();

        for (const string& interest : interests) {
            string cleaned = Utils::trim(interest);

            if (!cleaned.empty()) {
                this->interests.push_back(cleaned);
            }
        }
    }

    // Add a single skill
    bool addSkill(const string& skill, int proficiency) {
        string name = Utils::trim(skill);

        if (name.empty() || proficiency < 0 || proficiency > 10) {
            return false;
        }

        // Avoid duplicate names, ignoring capitalization
        for (const auto& existing : skills) {
            if (Utils::compare(existing.first, name)) {
                return false;
            }
        }

        skills[name] = proficiency;
        return true;
    }

    // Remove a skill
    bool removeSkill(const string& skill) {
        for (auto it = skills.begin(); it != skills.end(); ++it) {
            if (Utils::compare(it->first, skill)) {
                skills.erase(it);
                return true;
            }
        }

        return false;
    }

    // Display student profile
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
            cout << Utils::join(interests, ',');
        }

        cout << "\n";
    }
};
