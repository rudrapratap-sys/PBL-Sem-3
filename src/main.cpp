#include <iostream>
#include "../include/AuthSystem.h"

using namespace std;

int main()
{
    AuthSystem authSystem;

    int choice;

    while (true)
    {
        cout << "\n";
        cout << "=====================================\n";
        cout << "     CAREER INTELLIGENCE SYSTEM\n";
        cout << "=====================================\n";

        cout << "\n1. Register";
        cout << "\n2. Login";
        cout << "\n3. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                authSystem.registerUser();
                break;
            }

            case 2:
            {
                authSystem.loginUser();
                break;
            }

            case 3:
            {
                cout << "\nThank you for using Career Intelligence System!\n";
                return 0;
            }

            default:
            {
                cout << "\nInvalid choice! Please try again.\n";
            }
        }
    }

    return 0;
}