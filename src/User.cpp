#include "../include/User.h"

User::User()
{
    name = "";
    email = "";
    password = "";
}

User::User(string name, string email, string password)
{
    this->name = name;
    this->email = email;
    this->password = password;
}

string User::getName() const
{
    return name;
}

string User::getEmail() const
{
    return email;
}

string User::getPassword() const
{
    return password;
}

void User::setName(string name)
{
    this->name = name;
}

void User::setEmail(string email)
{
    this->email = email;
}

void User::setPassword(string password)
{
    this->password = password;
}
