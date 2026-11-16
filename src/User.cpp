#include <string>

using namespace std;

class User {
private:
    string userId;
    string name;
    string email;
    string passwordHash;

public:
    User() {
    }

    User( const string& userId,
      const string& name,
      const string& email,
      const string& passwordHash) {

        this->userId = userId;
        this->name = name;
        this->email = email;
        this->passwordHash = passwordHash;
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

    void setName( string& name) {
        this->name = name;
    }

    void setEmail( string& email) {
        this->email = email;
    }

    void setPasswordHash( string& passwordHash) {
        this->passwordHash = passwordHash;
    }
};