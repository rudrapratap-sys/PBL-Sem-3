#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <vector>
#include <string>

#include "User.h"

using namespace std;

class AuthSystem
{
private:

    vector<User> users;

    string fileName;

    bool emailExists(const string& email) const;

public:

    AuthSystem(string fileName = "data/users.json");

    void loadUsers();

    void saveUsers() const;

    bool registerUser();

    bool loginUser();

    void displayUsers() const;
};

#endif