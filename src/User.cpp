#include "User.h"

using namespace std;

User::User() {
}

// Member initializer list: directly stores parameter values into class variables.
// Example: userId(userId) means the class variable userId gets the parameter userId.
User::User(const string& userId,
           const string& name,
           const string& email,
           const string& passwordHash)
    : userId(userId), name(name), email(email), passwordHash(passwordHash) {
}

string User::getUserId() {
    return userId;
}

string User::getName() {
    return name;
}

string User::getEmail() {
    return email;
}

string User::getPasswordHash() {
    return passwordHash;
}

void User::setName(const string& name) {
    this->name = name;
}

void User::setEmail(const string& email) {
    this->email = email;
}

void User::setPasswordHash(const string& passwordHash) {
    this->passwordHash = passwordHash;
}
