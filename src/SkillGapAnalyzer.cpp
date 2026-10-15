// #include "SkillGapAnalyzer.h"

// #include "Utils.h"

// #include <fstream>
// #include <queue>
// #include <unordered_map>
// #include <unordered_set>

// using namespace std;

// SkillGapAnalyzer::SkillGapAnalyzer(const string& filePath)
//     : filePath(filePath) {
//     addPrerequisite("DSA", "C++");
//     addPrerequisite("DSA", "OOP");
//     addPrerequisite("React", "JavaScript");
//     addPrerequisite("Power BI", "Excel");
//     addPrerequisite("Machine Learning", "Python");
//     addPrerequisite("Machine Learning", "Maths");
//     addPrerequisite("Machine Learning", "Statistics");
//     addPrerequisite("Data Visualization", "Statistics");
//     addPrerequisite("Security Basics", "Networking");
//     loadRoles();
// }

// void SkillGapAnalyzer::addPrerequisite(const string& skill, const string& prerequisite) {
//     prerequisites[Utils::toLower(skill)].push_back(prerequisite);
// }

// bool SkillGapAnalyzer::loadRoles() {
//     roles.clear();

//     ifstream file(filePath);
//     if (!file) {
//         return false;
//     }

//     string line;
//     while (getline(file, line)) {
//         vector<string> parts = Utils::split(line, '|');
//         if (parts.size() >= 2) {
//             string roleName = Utils::trim(parts[0]);
//             vector<string> skills = Utils::splitAndTrim(parts[1], ',');
//             if (!roleName.empty() && !skills.empty()) {
//                 roles.push_back({roleName, skills});
//             }
//         }
//     }

//     return true;
// }

// vector<string> SkillGapAnalyzer::getRoleNames() {
//     vector<string> names;
//     for (const auto& role : roles) {
//         names.push_back(role.first);
//     }
//     return names;
// }

// vector<string> SkillGapAnalyzer::getSkillsForRole(const string& roleName) {
//     for (const auto& role : roles) {
//         if (Utils::equalsIgnoreCase(role.first, roleName)) {
//             return role.second;
//         }
//     }
//     return {};
// }

// SkillGapResult SkillGapAnalyzer::analyze(Student& student, const string& roleName) {
//     SkillGapResult result;
//     result.readinessScore = 0.0;
//     result.cycleFound = false;

//     vector<string> requiredSkills = getSkillsForRole(roleName);
//     unordered_set<string> studentSkillSet;

//     for (const string& skill : student.getSkills()) {
//         studentSkillSet.insert(Utils::toLower(Utils::trim(skill)));
//     }

//     for (const string& skill : requiredSkills) {
//         if (studentSkillSet.count(Utils::toLower(Utils::trim(skill)))) {
//             result.matchedSkills.push_back(skill);
//         } else {
//             result.missingSkills.push_back(skill);
//         }
//     }

//     if (!requiredSkills.empty()) {
//         result.readinessScore = (100.0 * result.matchedSkills.size()) / requiredSkills.size();
//     }

//     result.roadmap = makeRoadmap(result.missingSkills, result.cycleFound);
//     return result;
// }

// vector<string> SkillGapAnalyzer::makeRoadmap(const vector<string>& missingSkills,
//                                                        bool& cycleFound) {
//     vector<string> roadmap;
//     unordered_set<string> missingSet;
//     unordered_map<string, string> originalName;
//     unordered_map<string, int> indegree;
//     unordered_map<string, vector<string>> graph;

//     for (const string& skill : missingSkills) {
//         string key = Utils::toLower(skill);
//         missingSet.insert(key);
//         originalName[key] = skill;
//         indegree[key] = 0;
//     }

//     for (const string& skill : missingSkills) {
//         string skillKey = Utils::toLower(skill);
//         auto found = prerequisites.find(skillKey);

//         if (found == prerequisites.end()) {
//             continue;
//         }

//         for (const string& prereq : found->second) {
//             string prereqKey = Utils::toLower(prereq);
//             if (missingSet.count(prereqKey)) {
//                 graph[prereqKey].push_back(skillKey);
//                 indegree[skillKey]++;
//             }
//         }
//     }

//     queue<string> ready;
//     for (const string& skill : missingSkills) {
//         string key = Utils::toLower(skill);
//         if (indegree[key] == 0) {
//             ready.push(key);
//         }
//     }

//     while (!ready.empty()) {
//         string current = ready.front();
//         ready.pop();
//         roadmap.push_back(originalName[current]);

//         for (const string& next : graph[current]) {
//             indegree[next]--;
//             if (indegree[next] == 0) {
//                 ready.push(next);
//             }
//         }
//     }

//     cycleFound = roadmap.size() != missingSkills.size();
//     if (cycleFound) {
//         return missingSkills;
//     }

//     return roadmap;
// }
