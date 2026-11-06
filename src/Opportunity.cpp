
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Opportunity {
private:
    string title;
    string category;
    string domain;
    double minCgpa;
    vector<string> requiredSkills;
    string location;

public:

    Opportunity() : minCgpa(0.0) {
    }

    Opportunity(const string& title,
                const string& category,
                const string& domain,
                double minCgpa,
                const vector<string>& requiredSkills,
                const string& location)
        : title(title),
          category(category),
          domain(domain),
          minCgpa(minCgpa),
          requiredSkills(requiredSkills),
          location(location) {
    }

    string getTitle() {
        return title;
    }

    string getCategory() {
        return category;
    }

    string getDomain() {
        return domain;
    }

    double getMinCgpa() {
        return minCgpa;
    }

    vector<string> getRequiredSkills() {
        return requiredSkills;
    }

    string getLocation() {
        return location;
    }
};
