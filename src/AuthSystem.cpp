#include "../include/AuthSystem.h"

#include <iostream>
#include <fstream>

#include "../json.hpp"

using json = nlohmann::json;

using namespace std;


AuthSystem::AuthSystem(string fileName)
{
    this->fileName = fileName;

    loadUsers();
}


bool AuthSystem::emailExists(const string& email) const
{
    for (const User& user : users)
    {
        if (user.getEmail() == email)
        {
            return true;
        }
    }

    return false;
}


void AuthSystem::loadUsers()
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Users file not found. Creating a new one..." << endl;

        ofstream newFile(fileName);

        if (newFile.is_open())
        {
            newFile << "[]";
            newFile.close();
        }

        return;
    }


    try
    {
        json data;

        file >> data;

        file.close();


        users.clear();


        for (const auto& item : data)
        {
            string name = item["name"];
            string email = item["email"];
            string password = item["password"];

            User user(name, email, password);

            users.push_back(user);
        }
    }
    catch (const exception& e)
    {
        cout << "Error reading users.json!" << endl;
        cout << e.what() << endl;
    }
}



void AuthSystem::saveUsers() const
{
    json data = json::array();


    for (const User& user : users)
    {
        json userData;

        userData["name"] = user.getName();
        userData["email"] = user.getEmail();
        userData["password"] = user.getPassword();

        data.push_back(userData);
    }


    ofstream file(fileName);


    if (!file.is_open())
    {
        cout << "Error opening users.json for writing!" << endl;
        return;
    }


    file << data.dump(4);

    file.close();
}

bool AuthSystem::registerUser()
{
    string name;
    string email;
    string password;


    cout << "\n========== REGISTER ==========\n";


    cout << "Enter your name: ";
    getline(cin >> ws, name);


    cout << "Enter your email: ";
    getline(cin, email);

    if (emailExists(email))
    {
        cout << "\nAn account with this email already exists!\n";
        return false;
    }


    cout << "Enter your password: ";
    getline(cin, password);



    if (name.empty() || email.empty() || password.empty())
    {
        cout << "\nAll fields are required!\n";
        return false;
    }



    User newUser(name, email, password);

    users.push_back(newUser);


    saveUsers();


    cout << "\nRegistration successful!\n";

    return true;
}


bool AuthSystem::loginUser()
{
    string email;
    string password;


    cout << "\n========== LOGIN ==========\n";


    cout << "Enter your email: ";
    getline(cin >> ws, email);


    cout << "Enter your password: ";
    getline(cin, password);


    for (const User& user : users)
    {
        if (user.getEmail() == email)
        {
            if (user.getPassword() == password)
            {
                cout << "\nLogin successful!\n";

                cout << "Welcome, "
                     << user.getName()
                     << "!\n";

                return true;
            }
            else
            {
                cout << "\nIncorrect password!\n";

                return false;
            }
        }
    }


    cout << "\nNo account found with this email!\n";

    return false;
}


void AuthSystem::displayUsers() const
{
    cout << "\n========== USERS ==========\n";


    if (users.empty())
    {
        cout << "No users registered.\n";
        return;
    }


    for (const User& user : users)
    {
        cout << "Name     : "
             << user.getName()
             << endl;

        cout << "Email    : "
             << user.getEmail()
             << endl;

        cout << "Password : "
             << user.getPassword()
             << endl;

        cout << "--------------------------\n";
    }
}
