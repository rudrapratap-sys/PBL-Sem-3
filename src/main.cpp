// #include "AuthSystem.h"
// #include "OpportunityEngine.h"
// #include "SkillGapAnalyzer.h"
// #include "StudentManager.h"
// #include "Utils.h"

// #include <iomanip>
// #include <iostream>
// #include <limits>
// #include <sstream>
// #include <string>
// #include <vector>

// using namespace std;

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

    return Utils::trim(input);
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    string temp;
    getline(cin, temp);
}

void printList(const vector<string>& items) {
    if (items.empty()) {
        cout << "None";
        return;
    }

    for (size_t i = 0; i < items.size(); i++) {
        cout << items[i];
        if (i + 1 < items.size()) {
            cout << ", ";
        }
    }
}

// void registerFlow(AuthSystem& authSystem, StudentManager& studentManager) {
//     cout << "\n--- Register New Account ---\n";
//     string name = readText("Enter full name: ");
//     string email = readText("Enter email: ");
//     string password = readText("Enter password: ");

//     User createdUser;
//     string message;

//     if (authSystem.registerUser(name, email, password, createdUser, message)) {
//         Student student(createdUser);
//         studentManager.saveProfile(student);
//         cout << message << " Your user ID is " << createdUser.getUserId() << ".\n";
//     } else {
//         cout << "Registration failed: " << message << "\n";
//     }

//     waitForEnter();
// }

// bool loginFlow(AuthSystem& authSystem, User& loggedInUser) {
//     cout << "\n--- Login ---\n";
//     string email = readText("Enter email: ");
//     string password = readText("Enter password: ");
//     string message;

//     if (authSystem.loginUser(email, password, loggedInUser, message)) {
//         cout << message << "\n";
//         return true;
//     }

//     cout << "Login failed: " << message << "\n";
//     waitForEnter();
//     return false;
// }

// void editBasicDetails(Student& student, StudentManager& studentManager) {
//     cout << "\n--- Edit Basic Details ---\n";
//     student.setBranch(readText("Branch (example: CSE): "));
//     student.setYear(readInt("Year (1-4): ", 1, 4));
//     student.setCgpa(readDouble("CGPA (0-10): ", 0.0, 10.0));

//     string interests = readText("Interests separated by comma (example: AI,Web): ");
//     student.setInterests(Utils::splitAndTrim(interests, ','));

//     studentManager.saveProfile(student);
//     cout << "Profile updated.\n";
//     waitForEnter();
// }

// void addSkill(Student& student, StudentManager& studentManager) {
//     cout << "\n--- Add Skill ---\n";
//     string skill = readText("Skill name: ");

//     if (student.addSkill(skill)) {
//         studentManager.saveProfile(student);
//         cout << "Skill added.\n";
//     } else {
//         cout << "Skill is empty or already present.\n";
//     }

//     waitForEnter();
// }

// void removeSkill(Student& student, StudentManager& studentManager) {
//     cout << "\n--- Remove Skill ---\n";
//     cout << "Current skills: ";
//     printList(student.getSkills());
//     cout << "\n";

//     string skill = readText("Skill to remove: ");
//     if (student.removeSkill(skill)) {
//         studentManager.saveProfile(student);
//         cout << "Skill removed.\n";
//     } else {
//         cout << "Skill not found.\n";
//     }

//     waitForEnter();
// }

// void selectTargetRole(Student& student,
//                       SkillGapAnalyzer& analyzer,
//                       StudentManager& studentManager) {
//     vector<string> roles = analyzer.getRoleNames();

//     if (roles.empty()) {
//         cout << "No roles found in data/roles.txt.\n";
//         waitForEnter();
//         return;
//     }

//     cout << "\n--- Select Target Role ---\n";
//     for (size_t i = 0; i < roles.size(); i++) {
//         cout << i + 1 << ". " << roles[i] << "\n";
//     }

//     int choice = readInt("Choose role: ", 1, static_cast<int>(roles.size()));
//     student.setTargetRole(roles[choice - 1]);
//     studentManager.saveProfile(student);
//     cout << "Target role set to " << roles[choice - 1] << ".\n";
//     waitForEnter();
// }

// void analyzeSkillGap(Student& student, SkillGapAnalyzer& analyzer) {
//     if (student.getTargetRole().empty()) {
//         cout << "Please select a target role first.\n";
//         waitForEnter();
//         return;
//     }

//     SkillGapResult result = analyzer.analyze(student, student.getTargetRole());

//     cout << "\n--- Skill Gap Report ---\n";
//     cout << "Target Role     : " << student.getTargetRole() << "\n";
//     cout << "Readiness Score : " << fixed << setprecision(2)
//               << result.readinessScore << "%\n";

//     cout << "\nMatched Skills  : ";
//     printList(result.matchedSkills);

//     cout << "\nMissing Skills  : ";
//     printList(result.missingSkills);

//     cout << "\n\nLearning Roadmap:\n";
//     if (result.roadmap.empty()) {
//         cout << "All required skills are already matched.\n";
//     } else {
//         if (result.cycleFound) {
//             cout << "Cycle found in prerequisite data, showing simple missing skill list.\n";
//         }

//         for (size_t i = 0; i < result.roadmap.size(); i++) {
//             cout << i + 1 << ". " << result.roadmap[i] << "\n";
//         }
//     }

//     waitForEnter();
// }

// void discoverOpportunities(Student& student, OpportunityEngine& engine) {
//     vector<OpportunityResult> results = engine.findOpportunities(student);

//     if (results.empty()) {
//         cout << "No opportunity data found in data/opportunities.txt.\n";
//         waitForEnter();
//         return;
//     }

//     int topN = readInt("How many results do you want to see? ", 1, static_cast<int>(results.size()));

//     cout << "\n--- Opportunity Results ---\n";
//     for (int i = 0; i < topN; i++) {
//         OpportunityResult& result = results[i];
//         Opportunity& opportunity = result.opportunity;

//         cout << "\n" << i + 1 << ". " << opportunity.getTitle() << "\n";
//         cout << "Domain      : " << opportunity.getDomain() << "\n";
//         cout << "Location    : " << opportunity.getLocation() << "\n";
//         cout << "Min CGPA    : " << opportunity.getMinCgpa() << "\n";
//         cout << "Eligibility : " << (result.eligible ? "Eligible" : "Not Eligible") << "\n";
//         cout << "Score       : " << fixed << setprecision(2) << result.score << "/100\n";
//         cout << "Matched     : ";
//         printList(result.matchedSkills);
//         cout << "\nMissing     : ";
//         printList(result.missingSkills);
//         cout << "\nReason      : " << result.reason << "\n";
//     }

//     waitForEnter();
// }

// void studentDashboard(Student& student,
//                       StudentManager& studentManager,
//                       SkillGapAnalyzer& analyzer,
//                       OpportunityEngine& engine) {
//     while (true) {
//         cout << "\n==============================\n";
//         cout << " Student Dashboard - " << student.getName() << "\n";
//         cout << "==============================\n";
//         cout << "1. View Profile\n";
//         cout << "2. Edit Basic Details\n";
//         cout << "3. Add Skill\n";
//         cout << "4. Remove Skill\n";
//         cout << "5. Select Target Role\n";
//         cout << "6. Analyze Skill Gap\n";
//         cout << "7. Discover Opportunities\n";
//         cout << "8. Logout\n";

//         int choice = readInt("Enter choice: ", 1, 9);

//         switch (choice) {
//             case 1:
//                 student.displayProfile();
//                 waitForEnter();
//                 break;
//             case 2:
//                 editBasicDetails(student, studentManager);
//                 break;
//             case 3:
//                 addSkill(student, studentManager);
//                 break;
//             case 4:
//                 removeSkill(student, studentManager);
//                 break;
//             case 5:
//                 selectTargetRole(student, analyzer, studentManager);
//                 break;
//             case 6:
//                 analyzeSkillGap(student, analyzer);
//                 break;
//             case 7:
//                 discoverOpportunities(student, engine);
//                 break;
//             case 8:
//                 studentManager.saveProfile(student);
//                 cout << "Logged out.\n";
//                 return;
//         }
//     }
// }

// int main() {
//     AuthSystem authSystem;
//     StudentManager studentManager;
//     SkillGapAnalyzer analyzer;
//     OpportunityEngine engine;

//     while (true) {
//         cout << "\n============================================\n";
//         cout << " Skill Gap Navigator + Opportunity Finder\n";
//         cout << "============================================\n";
//         cout << "1. Register\n";
//         cout << "2. Login\n";
//         cout << "3. Exit\n";

//         int choice = readInt("Enter choice: ", 1, 3);

//         if (choice == 1) {
//             registerFlow(authSystem, studentManager);
//         } else if (choice == 2) {
//             User loggedInUser;
//             if (loginFlow(authSystem, loggedInUser)) {
//                 Student student = studentManager.loadProfile(loggedInUser);
//                 studentDashboard(student, studentManager, analyzer, engine);
//             }
//         } else {
//             cout << "Thank you for using the project.\n";
//             break;
//         }
//     }

//     return 0;
// }

// hello
#include<iostream>

#include "AuthSystem.h"
#include "OpportunityEngine.h"
#include "SkillGapAnalyzer.h"
#include "StudentManager.h"
#include "Utils.h"

using namespace std;

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    string temp;
    getline(cin, temp);
}

bool login_user(AuthSystem& authSystem, User& loggedInUser) {
    cout << "\n--- Login ---\n";
    string email ;
    cout<<"Enter email: ";
    getline(cin, email);
    email = Utils::trim(email);

    string password ;
    cout<<"Enter password: ";
    getline(cin, password);
    password = Utils::trim(password);
    string message;

    if (authSystem.loginUser(email, password, loggedInUser, message)) {
        cout << message << "\n";
        return true;
    }

    cout << "Login failed: " << message << "\n";
    waitForEnter();
    return false;
}

void register_user(AuthSystem& authSystem, StudentManager& studentManager) {
    cout << "\n--- Register New Account ---\n";
    string name ;
    cout<<"Enter full name: ";
    getline(cin,name);
    name = Utils::trim(name);

    string email ;
    cout<<"Enter email: ";
    getline(cin, email);
    email = Utils::trim(email);

    string password ;
    cout<<"Enter password: ";
    getline(cin, password);
    password = Utils::trim(password);

    User createdUser;
    string message;

    if (authSystem.registerUser(name, email, password, createdUser, message)) {
        Student student(createdUser);
        studentManager.saveProfile(student);
        cout << message << " Your user ID is " << createdUser.getUserId() << ".\n";
    } else {
        cout << "Registration failed: " << message << "\n";
    }

    waitForEnter();
}

void editBasicDetails(Student& student, StudentManager& studentManager) {
    cout << "\n--- Edit Basic Details ---\n";

    student.setBranch(readText("Branch (example: CSE): "));
    student.setYear(readInt("Year (1-4): ", 1, 4));
    student.setCgpa(readDouble("CGPA (0-10): ", 0.0, 10.0));

    string interests = readText("Interests separated by comma (example: AI,Web): ");
    student.setInterests(Utils::splitAndTrim(interests, ','));

    studentManager.saveProfile(student);
    cout << "Profile updated.\n";
    waitForEnter();
}

void addSkill(Student& student, StudentManager& studentManager) {
    cout << "\n--- Add Skill ---\n";
    string skill = readText("Skill name: ");

    if (student.addSkill(skill)) {
        studentManager.saveProfile(student);
        cout << "Skill added.\n";
    } else {
        cout << "Skill is empty or already present.\n";
    }

    waitForEnter();
}

void editBasicDetails(){}
void addSkill(){}
void removeSkill(){}
void selectTargetRole(){}
void analyzeSkillGap(){}
void discoverOpportunities(){}


void studentDashboard(Student& student,
                      StudentManager& studentManager,
                      SkillGapAnalyzer& analyzer,
                      OpportunityEngine& engine) {
    while (true) {
        cout << "\n==============================\n";
        cout << " Student Dashboard - " << student.getName() << "\n";
        cout << "==============================\n";
        cout << "1. View Profile\n";
        cout << "2. Edit Basic Details\n";
        cout << "3. Add Skill\n";
        cout << "4. Remove Skill\n";
        cout << "5. Select Target Role\n";
        cout << "6. Analyze Skill Gap\n";
        cout << "7. Discover Opportunities\n";
        cout << "8. Logout\n";

        int choice ;
        cout<<"Enter choice : ";
        cin>>choice;

        switch (choice) {
            case 1:
                student.displayProfile();
                waitForEnter();
                break;
            case 2:
                editBasicDetails(student, studentManager);
                break;
            case 3:
                addSkill(student, studentManager);
                break;
            case 4:
                removeSkill(student, studentManager);
                break;
            case 5:
                selectTargetRole(student, analyzer, studentManager);
                break;
            case 6:
                analyzeSkillGap(student, analyzer);
                break;
            case 7:
                discoverOpportunities(student, engine);
                break;
            case 8:
                studentManager.saveProfile(student);
                cout << "Logged out.\n";
                return;
        }
    }
}

int main(){

    AuthSystem authSystem;
    StudentManager studentManager;
    SkillGapAnalyzer analyzer;
    OpportunityEngine engine;

    while (true) {
        
        cout << "\n============================================\n";
        cout << " Skill Gap Navigator + Opportunity Finder\n";
        cout << "============================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        int choice ;
        cout<<"Enter choice: 1, 2, 3 : ";
        cin>>choice;

        
        switch (choice) {
            case 1:
                register_user(authSystem, studentManager);
                break;

            case 2: {
                User loggedInUser;

                if (login_user(authSystem, loggedInUser)) {
                    Student student =
                    studentManager.loadProfile(loggedInUser);
                    studentDashboard(student, studentManager, analyzer, engine);
                }
                break;
            }

            case 3:
                cout << "Thank you for using the project.\n";
                return 0;

            default:
                cout << "Enter a valid choice: ";
                break;
        }


    }
}