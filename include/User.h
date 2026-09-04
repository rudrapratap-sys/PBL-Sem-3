#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
private:
    string name;
    string email;
    string password;

public:
    User();
    User(string name, string email, string password);

    string getName() const;
    string getEmail() const;
    string getPassword() const;

    void setName(string name);
    void setEmail(string email);
    void setPassword(string password);
};

#endif