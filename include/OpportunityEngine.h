#pragma once

#include "Opportunity.h"
#include "Student.h"

#include <string>
#include <vector>

using namespace std;

struct OpportunityResult {
    Opportunity opportunity;
    bool eligible;
    double score;
    vector<string> matchedSkills;
    vector<string> missingSkills;
    string reason;
};

class OpportunityEngine {
private:
    string filePath;
    vector<Opportunity> opportunities;

public:
    explicit OpportunityEngine(const string& filePath = "data/opportunities.txt");

    bool loadOpportunities();
    vector<OpportunityResult> findOpportunities(Student& student);
};
