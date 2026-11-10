#include <string>

using namespace std;

class User {
private:
    string userId;
    string name;
    string email;
    string passwordHash;

    // Member initializer list: directly stores parameter values into class variables.
    // Example: userId(userId) means the class variable userId gets the parameter userId.
public:
    User() {
    }

    User(const string& userId,
         const string& name,
         const string& email,
         const string& passwordHash)
        : userId(userId),
          name(name),
          email(email),
          passwordHash(passwordHash) {
    }

    string getUserId() {
        return userId;
    }

    string getName() {
        return name;
    }

    string getEmail() {
        return email;
    }

    string getPasswordHash() {
        return passwordHash;
    }

    void setName(const string& name) {
        this->name = name;
    }

    void setEmail(const string& email) {
        this->email = email;
    }

    void setPasswordHash(const string& passwordHash) {
        this->passwordHash = passwordHash;
    }
};