#include "AuthSystem.h"

#include "Utils.h"

#include <fstream>
#include <sstream>

using namespace std;

AuthSystem::AuthSystem() {
    loadUsers();
}

string AuthSystem::makePasswordHash(const string& password) {
    // Academic demo only: for now we are only adding a fixed salt.
    // Future improvement: use a proper password hasher like bcrypt or Argon2.
    return password + "_some_salt_by_piyush";
}

bool AuthSystem::isValidEmail(const string& email) {
    // size_t is used for string positions instead of int.
    // It stores values from 0 to positive only, so it cannot be negative.
    // also .find() return size_t not int
    size_t at = email.find('@');
    size_t dot = email.rfind('.');

    // If find() or rfind() does not find the character, it returns string::npos.
    if (at == string::npos) {
        return false;
    }

    if (dot == string::npos) {
        return false;
    }

    if (at == 0) {
        return false;
    }

    if (dot <= at + 1) {
        return false;
    }

    if (dot == email.size() - 1) {
        return false;
    }

    return true;
}

bool AuthSystem::emailExists(const string& email) {
    for (User& user : users) {
        if (Utils::equalsIgnoreCase(user.getEmail(), email)) {
            return true;
        }
    }
    return false;
}

string AuthSystem::generateUserId() {
    // Simple ID generation for this project.
    // If 3 users are already saved, the next user ID will be U4.
    int nextNumber = users.size() + 1;
    return "U" + to_string(nextNumber);
}

bool AuthSystem::loadUsers() {
    users.clear();

    ifstream file(filePath);
    if (!file) {
        return true;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts = Utils::split(line, '|');
        if (parts.size() == 4) {
            users.push_back(User(parts[0], parts[1], parts[2], parts[3]));
        }
    }

    return true;
}

bool AuthSystem::saveUsers() {
    ofstream file(filePath);
    if (!file) {
        return false;
    }

    for (User& user : users) {
        file << user.getUserId() << "|"
             << user.getName() << "|"
             << user.getEmail() << "|"
             << user.getPasswordHash() << "\n";
    }

    return true;
}

bool AuthSystem::registerUser(const string& name,
                              const string& email,
                              const string& password,
                              User& createdUser,
                              string& message) {
    string cleanedName = Utils::trim(name);
    string cleanedEmail = Utils::trim(email);

    if (cleanedName.empty()) {
        message = "Name cannot be empty.";
        return false;
    }

    if (!isValidEmail(cleanedEmail)) {
        message = "Please enter a valid email address.";
        return false;
    }

    if (emailExists(cleanedEmail)) {
        message = "An account with this email already exists.";
        return false;
    }

    if (password.size() < 4) {
        message = "Password should contain at least 4 characters for this demo.";
        return false;
    }

    createdUser = User(generateUserId(), cleanedName, cleanedEmail, makePasswordHash(password));
    users.push_back(createdUser);

    if (!saveUsers()) {
        message = "Could not save user data.";
        return false;
    }

    message = "Registration successful.";
    return true;
}

bool AuthSystem::loginUser(const string& email,
                           const string& password,
                           User& loggedInUser,
                           string& message) {
    string cleanedEmail = Utils::trim(email);
    string enteredPasswordValue = makePasswordHash(password);

    for (User& user : users) {
        if (Utils::equalsIgnoreCase(user.getEmail(), cleanedEmail)) {
            if (user.getPasswordHash() == enteredPasswordValue) {
                loggedInUser = user;
                message = "Login successful.";
                return true;
            }
            message = "Wrong password.";
            return false;
        }
    }

    message = "No account found with this email.";
    return false;
}
