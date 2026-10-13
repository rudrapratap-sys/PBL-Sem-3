#include "Opportunity.h"

using namespace std;

Opportunity::Opportunity() : minCgpa(0.0) {
}

Opportunity::Opportunity(const string& title,
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

string Opportunity::getTitle() {
    return title;
}

string Opportunity::getCategory() {
    return category;
}

string Opportunity::getDomain() {
    return domain;
}

double Opportunity::getMinCgpa() {
    return minCgpa;
}

vector<string> Opportunity::getRequiredSkills() {
    return requiredSkills;
}

string Opportunity::getLocation() {
    return location;
}
