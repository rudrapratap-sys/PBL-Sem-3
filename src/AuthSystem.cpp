
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class AuthSystem {
private:
    vector<User> users;
    string filePath = "users.txt";

public:

    AuthSystem() {
        loadUsers();
    }

    string makePasswordHash( string& password) {

        return password + "SALT_ADDED";
    }

    bool isValidEmail( string& email) {

        size_t at = email.find('@');
        size_t dot = email.rfind('.');

        if (at == string::npos || dot == string::npos) {
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

    bool emailExists( string& email) {
        for (User& user : users) {
            if (Helper::compare(user.getEmail(), email)) {
                return true;
            }
        }

        return false;
    }

    string generateUserId() {
        
        int nextNumber = users.size() + 1;
        return "U" + to_string(nextNumber);
    }

    bool loadUsers() {
        users.clear();

        ifstream file(filePath);

        if (!file) {
            return true;
        }

        string line;

        while (getline(file, line)) {
            vector<string> parts = Helper::split(line, '|');

            if (parts.size() == 4) {
                users.push_back(
                    User(parts[0], parts[1], parts[2], parts[3])
                );
            }
        }

        return true;
    }

    bool saveUsers() {
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

    bool registerUser( string& name,
                       string& email,
                       string& password,
                      User& createdUser,
                      string& message) {

        string cleanedName = Helper::trim(name);
        string cleanedEmail = Helper::trim(email);

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

        createdUser = User(
            generateUserId(),
            cleanedName,
            cleanedEmail,
            makePasswordHash(password)
        );

        users.push_back(createdUser);

        if (!saveUsers()) {
            message = "Could not save user data.";
            return false;
        }

        message = "Registration successful.";
        return true;
    }

    bool loginUser( string& email,
                    string& password,
                   User& loggedInUser,
                   string& message) {

        string cleanedEmail = Helper::trim(email);
        string enteredPasswordValue = makePasswordHash(password);

        for (User& user : users) {
            if (Helper::compare(user.getEmail(), cleanedEmail)) {

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
};
