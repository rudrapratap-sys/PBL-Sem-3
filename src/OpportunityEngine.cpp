// #include "OpportunityEngine.h"

// #include "Utils.h"

// #include <algorithm>
// #include <fstream>
// #include <sstream>
// #include <unordered_set>

// using namespace std;

// OpportunityEngine::OpportunityEngine(const string& filePath) : filePath(filePath) {
//     loadOpportunities();
// }

// bool OpportunityEngine::loadOpportunities() {
//     opportunities.clear();

//     ifstream file(filePath);
//     if (!file) {
//         return false;
//     }

//     string line;
//     while (getline(file, line)) {
//         vector<string> parts = Utils::split(line, '|');
//         if (parts.size() >= 6) {
//             double minCgpa = 0.0;
//             try {
//                 minCgpa = stod(parts[3]);
//             } catch (...) {
//                 minCgpa = 0.0;
//             }

//             opportunities.push_back(Opportunity(
//                 Utils::trim(parts[0]),
//                 Utils::trim(parts[1]),
//                 Utils::trim(parts[2]),
//                 minCgpa,
//                 Utils::splitAndTrim(parts[4], ','),
//                 Utils::trim(parts[5])
//             ));
//         }
//     }

//     return true;
// }

// vector<OpportunityResult> OpportunityEngine::findOpportunities(Student& student) {
//     vector<OpportunityResult> results;
//     unordered_set<string> studentSkillSet;

//     for (const string& skill : student.getSkills()) {
//         studentSkillSet.insert(Utils::toLower(Utils::trim(skill)));
//     }

//     for (Opportunity& opportunity : opportunities) {
//         OpportunityResult result;
//         result.opportunity = opportunity;
//         result.eligible = student.getCgpa() >= opportunity.getMinCgpa();
//         result.score = 0.0;

//         for (const string& skill : opportunity.getRequiredSkills()) {
//             if (studentSkillSet.count(Utils::toLower(skill))) {
//                 result.matchedSkills.push_back(skill);
//             } else {
//                 result.missingSkills.push_back(skill);
//             }
//         }

//         if (!result.eligible) {
//             stringstream reason;
//             reason << "Not eligible because minimum CGPA is "
//                    << opportunity.getMinCgpa() << ".";
//             result.reason = reason.str();
//             results.push_back(result);
//             continue;
//         }

//         if (!opportunity.getRequiredSkills().empty()) {
//             result.score += 60.0 * result.matchedSkills.size() / opportunity.getRequiredSkills().size();
//         }

//         if (Utils::equalsIgnoreCase(opportunity.getDomain(), student.getTargetRole())) {
//             result.score += 25.0;
//         }

//         if (!Utils::equalsIgnoreCase(student.getPreferredCategory(), "Any") &&
//             Utils::equalsIgnoreCase(opportunity.getCategory(), student.getPreferredCategory())) {
//             result.score += 15.0;
//         }

//         if (result.score > 100.0) {
//             result.score = 100.0;
//         }

//         stringstream reason;
//         reason << "Eligible. Skill match: "
//                << result.matchedSkills.size() << "/"
//                << opportunity.getRequiredSkills().size() << ".";

//         if (Utils::equalsIgnoreCase(opportunity.getDomain(), student.getTargetRole())) {
//             reason << " Domain matches target role.";
//         }

//         if (Utils::equalsIgnoreCase(opportunity.getCategory(), student.getPreferredCategory())) {
//             reason << " Category matches preference.";
//         }

//         result.reason = reason.str();
//         results.push_back(result);
//     }

//     sort(results.begin(), results.end(), [](OpportunityResult first, OpportunityResult second) {
//         if (first.eligible != second.eligible) {
//             return first.eligible > second.eligible;
//         }

//         if (first.score != second.score) {
//             return first.score > second.score;
//         }

//         return first.opportunity.getTitle() < second.opportunity.getTitle();
//     });

//     return results;
// }
