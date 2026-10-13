#pragma once

#include "Student.h"

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct SkillGapResult {
    vector<string> matchedSkills;
    vector<string> missingSkills;
    vector<string> roadmap;
    double readinessScore;
    bool cycleFound;
};

class SkillGapAnalyzer {
private:
    string filePath;
    vector<pair<string, vector<string>>> roles;
    unordered_map<string, vector<string>> prerequisites;

    void addPrerequisite(const string& skill, const string& prerequisite);
    vector<string> makeRoadmap(const vector<string>& missingSkills,
                                         bool& cycleFound);

public:
    explicit SkillGapAnalyzer(const string& filePath = "data/roles.txt");

    bool loadRoles();
    vector<string> getRoleNames();
    vector<string> getSkillsForRole(const string& roleName);
    SkillGapResult analyze(Student& student, const string& roleName);
};
