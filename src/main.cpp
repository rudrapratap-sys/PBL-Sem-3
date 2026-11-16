#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <string>

#include "Utils.cpp"
#include "User.cpp"
#include "Student.cpp"
#include "Opportunity.cpp"
#include "AuthSystem.cpp"
#include "StudentManager.cpp"
#include "OpportunityEngine.cpp"
#include "SkillGapAnalyzer.cpp"
#include "RoadMap.cpp"

using namespace std;

int readInt(const string& message, int minimum, int maximum) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number.\n";
        }
        else {
            cin.ignore(1000, '\n');

            if (value >= minimum && value <= maximum) {
                return value;
            }

            cout << "Enter a number from "
                 << minimum << " to " << maximum << ".\n";
        }
    }
}

double readDouble(const string& message, double minimum, double maximum) {
    double value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number.\n";
        }
        else {
            cin.ignore(1000, '\n');

            if (value >= minimum && value <= maximum) {
                return value;
            }

            cout << "Enter a value from "
                 << minimum << " to " << maximum << ".\n";
        }
    }
}

string readText(const string& message) {
    cout << message;

    string input;
    getline(cin, input);

    return Helper::trim(input);
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    string temp;
    getline(cin, temp);
}

bool login_user(AuthSystem& authSystem, User& loggedInUser) {
    cout << "\n--- Login ---\n";

    string email = readText("Enter email: ");
    string password = readText("Enter password: ");

    string message;

    if (authSystem.loginUser(email, password, loggedInUser, message)) {
        cout << message << "\n";
        return true;
    }

    cout << "Login failed: " << message << "\n";
    waitForEnter();

    return false;
}

void register_user(AuthSystem& authSystem,
                   StudentManager& studentManager) {
    cout << "\n--- Register New Account ---\n";

    string name = readText("Enter full name: ");
    string email = readText("Enter email: ");
    string password = readText("Enter password: ");

    User createdUser;
    string message;

    if (authSystem.registerUser(name, email, password,
                                createdUser, message)) {
        Student student(createdUser);
        studentManager.saveProfile(student);

        cout << message << " Your user ID is "
             << createdUser.getUserId() << ".\n";
    }
    else {
        cout << "Registration failed: " << message << "\n";
    }

    waitForEnter();
}

string prefer() {

    cout << "Which category do you prefer?\n"
         << "1. Jobs\n"
         << "2. Internships\n"
         << "3. Hackathons\n"
         << "4. Workshops\n"
         << "5. Any\n";

    int c = readInt("Enter your choice: ", 1, 5);

    switch (c) {
        case 1: return "job";
        case 2: return "internship";
        case 3: return "hackathon";
        case 4: return "workshop";
        case 5: return "Any";
    }

    return "Any";
}

void editBasicDetails(Student& student,
                      StudentManager& studentManager) {
    cout << "\n--- Edit Basic Details ---\n";

    student.setBranch(readText("Branch (example: CSE): "));
    student.setYear(readInt("Year (1-4): ", 1, 4));
    student.setCgpa(readDouble("CGPA (0-10): ", 0.0, 10.0));
    student.setPreferredCategory(prefer());

    string interests = readText(
        "Interests separated by comma (example: AI,Web): "
    );

    student.setInterests(Helper::splitAndTrim(interests, ','));

    studentManager.saveProfile(student);

    cout << "Profile updated.\n";
    waitForEnter();
}

void addSkill(Student& student, StudentManager& studentManager) {
    cout << "\n--- Add Skills ---\n";

    string skill = readText(
        "Enter your skills with proficiency scores (e.g., Python:5, C:6, C++:9)\n\n"
        "Choose a score based on your knowledge and experience:\n"
        "1-3   Beginner      : You know the basics and can write simple programs.\n"
        "4-6   Intermediate  : You understand concepts and have built small projects.\n"
        "7-8   Advanced      : You can build complex projects and solve problems independently.\n"
        "9-10  Expert        : You have developed real-world projects and can apply your skills confidently.\n\n"
        "Be honest with your ratings to help us recommend suitable opportunities and identify your skill gaps.\n\n"
        "Format: SkillName1:Score, SkillName2:Score\n"
        "Your skills: "
    );

    if (skill.empty()) {
        cout << "Skill input is empty.\n";
    }
    else {
        student.setSkills(skill);
        studentManager.saveProfile(student);
        cout << "Skills updated.\n";
    }

    waitForEnter();
}

void removeSkill(Student& student, StudentManager& studentManager) {
    cout << "\n--- Remove Skill ---\n";

    unordered_map<string, int> skills = student.getSkills();

    if (skills.empty()) {
        cout << "No skills to remove.\n";
        waitForEnter();
        return;
    }

    cout << "Current skills:\n";

    for (const auto& s : skills) {
        cout << "  " << s.first << " : "
             << s.second << "/10\n";
    }

    string skill = readText("Skill to remove: ");

    if (student.removeSkill(skill)) {
        studentManager.saveProfile(student);
        cout << "Skill removed.\n";
    }
    else {
        cout << "Skill not found.\n";
    }

    waitForEnter();
}

void studentDashboard(Student& student,
                      StudentManager& studentManager) {
    OpportunityEngine engine;

    while (true) {
        cout << "\n==============================\n";
        cout << " Student Dashboard - "
             << student.getName() << "\n";
        cout << "==============================\n";

        cout << "1. View Profile\n";
        cout << "2. Edit Basic Details\n";
        cout << "3. Add Skills\n";
        cout << "4. Remove Skill\n";
        cout << "5. Discover Opportunities\n";
        cout << "6. View Roadmap\n";
        cout << "7. Logout\n";

        int choice = readInt("Enter choice: ", 1, 9);

        switch (choice) {
            case 1:
                student.displayProfile();
                waitForEnter();
                break;

            case 2:
                editBasicDetails(student, studentManager);
                waitForEnter();
                break;

            case 3:
                addSkill(student, studentManager);
                break;

            case 4:
                removeSkill(student, studentManager);
                break;

            case 5:
            {
                SkillGapAnalyzer analyzer;
                bool result = engine.filter(student);

                if (result) {
                    analyzer.displayOpportunities(student);
                }
                else{
                    cout<<"Some error occured while filtering data" ;
                }

                waitForEnter();
                break;
            }

            case 6: {
                Roadmap roadmap;
                roadmap.showMenu(student);
                waitForEnter();
                break;
            }

            case 7:
                studentManager.saveProfile(student);
                cout << "Logged out.\n";
                return;
        }
    }
}

int main() {
    AuthSystem authSystem;
    StudentManager studentManager;

    while (true) {
        cout << "\n============================================\n";
        cout << " Skill Gap Navigator + Opportunity Finder\n";
        cout << "============================================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        int choice = readInt("Enter choice (1-3): ", 1, 3);

        switch (choice) {
            case 1:
                register_user(authSystem, studentManager);
                break;

            case 2: {
                User loggedInUser;

                if (login_user(authSystem, loggedInUser)) {
                    Student student =
                        studentManager.loadProfile(loggedInUser);

                    studentDashboard(student, studentManager);
                }

                break;
            }

            case 3:
                cout << "Thank you for using the project.\n";
                return 0;
        }
    }
}
