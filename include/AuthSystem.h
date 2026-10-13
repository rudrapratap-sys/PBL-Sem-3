#pragma once

#include "User.h"

#include <string>
#include <vector>

using namespace std;

class AuthSystem {
private:
    string filePath = "data/users.txt";
    vector<User> users;

    // const after the function means this function is read-only for this object.
    // It can check filePath/users, but it cannot change them accidentally.
    string makePasswordHash(const string& password);
    bool isValidEmail(const string& email);
    bool emailExists(const string& email);
    string generateUserId();

public:
    AuthSystem();

    bool loadUsers();
    bool saveUsers();
    bool registerUser(const string& name,
                      const string& email,
                      const string& password,
                      User& createdUser,
                      string& message);
    bool loginUser(const string& email,
                   const string& password,
                   User& loggedInUser,
                   string& message);
};
