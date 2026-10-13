#pragma once

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
    Opportunity();
    Opportunity(const string& title,
                const string& category,
                const string& domain,
                double minCgpa,
                const vector<string>& requiredSkills,
                const string& location);

    string getTitle();
    string getCategory();
    string getDomain();
    double getMinCgpa();
    vector<string> getRequiredSkills();
    string getLocation();
};
