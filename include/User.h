#pragma once

#include <string>

using namespace std;

class User {
private:
    string userId;
    string name;
    string email;
    string passwordHash;

public:
    User();
    User(const string& userId,
         const string& name,
         const string& email,
         const string& passwordHash);

    string getUserId();
    string getName();
    string getEmail();
    string getPasswordHash();

    void setName(const string& name);
    void setEmail(const string& email);
    void setPasswordHash(const string& passwordHash);
};
