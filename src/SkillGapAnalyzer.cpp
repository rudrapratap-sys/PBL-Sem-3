#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct SkillEvaluation {
    string skillName;
    int studentLevel;
    int requiredLevel;
    double achievement;
    string status;
};

struct OpportunityResult {
    string id;
    string name;

    vector<SkillEvaluation> skills;

    double readinessScore;
    double gpaScore;
    double opportunityScore;

    bool gpaEligible;
};

class SkillGapAnalyzer {
private:
    int getStudentLevel(
        const unordered_map<string, int>& studentSkills,
        const string& requiredSkill
    ) const {
        for (const auto& skill : studentSkills) {
            if (Utils::compare(skill.first, requiredSkill)) {
                return skill.second;
            }
        }

        return 0;
    }
    double calculateAchievement(
        int studentLevel,
        int requiredLevel
    ) const {
        if (requiredLevel <= 0) {
            return 0.0;
        }

        double ratio =
            static_cast<double>(studentLevel) /
            requiredLevel;

        if (ratio > 1.0) {
            ratio = 1.0;
        }

        return ratio * 100.0;
    }

    double calculateGpaScore(
        double studentCgpa,
        double minimumGpa
    ) const {
      
        if (minimumGpa <= 0.0) {
            return 100.0;
        }

        double ratio = studentCgpa / minimumGpa;

        if (ratio > 1.0) {
            ratio = 1.0;
        }

        if (ratio < 0.0) {
            ratio = 0.0;
        }

        return ratio * 100.0;
    }

public:
   
    OpportunityResult analyzeOpportunity(
        Student& student,
        const json& opportunity
    ) const {
        OpportunityResult result;

        result.id =
            opportunity.value("opportunity_id", "");

        result.name =
            opportunity.value("name", "Unknown");

        double minimumGpa =
            opportunity.value("min_gpa", 0.0);

        result.readinessScore = 0.0;
        result.gpaScore = 0.0;
        result.opportunityScore = 0.0;

        unordered_map<string, int> studentSkills =
            student.getSkills();

        const json& requiredSkills =
            opportunity["required_skills"];

        double totalAchievement = 0.0;
        int requiredSkillCount = 0;

        for (
            auto item = requiredSkills.begin();
            item != requiredSkills.end();
            ++item
        ) {
            string skillName = item.key();
            int requiredLevel = item.value().get<int>();

           
            if (requiredLevel <= 0) {
                continue;
            }

            int studentLevel =
                getStudentLevel(
                    studentSkills,
                    skillName
                );

            double achievement =
                calculateAchievement(
                    studentLevel,
                    requiredLevel
                );

            SkillEvaluation evaluation;

            evaluation.skillName = skillName;
            evaluation.studentLevel = studentLevel;
            evaluation.requiredLevel = requiredLevel;
            evaluation.achievement = achievement;

            if (studentLevel == 0) {
                evaluation.status = "Missing";
            }
            else if (studentLevel < requiredLevel) {
                evaluation.status = "Needs Improvement";
            }
            else {
                evaluation.status = "Matched";
            }

            result.skills.push_back(evaluation);

            totalAchievement += achievement;
            requiredSkillCount++;
        }

       
        if (requiredSkillCount > 0) {
            result.readinessScore =
                totalAchievement /
                requiredSkillCount;
        }

        result.gpaEligible =
            minimumGpa <= 0.0 ||
            student.getCgpa() >= minimumGpa;

        result.gpaScore =
            calculateGpaScore(
                student.getCgpa(),
                minimumGpa
            );

        
        result.opportunityScore =
            (0.70 * result.readinessScore) +
            (0.30 * result.gpaScore);

        return result;
    }

   
    vector<OpportunityResult> analyze(
        Student& student,
        const string& filePath = "filtered.json"
    ) const {
        vector<OpportunityResult> results;

        ifstream file(filePath);

        if (!file) {
            return results;
        }

        json data;

        try {
            file >> data;
        }
        catch (...) {
            return results;
        }

        if (
            !data.contains("opportunities") ||
            !data["opportunities"].is_array()
        ) {
            return results;
        }

        for (const json& opportunity :
             data["opportunities"]) {

            if (
                !opportunity.contains("required_skills") ||
                !opportunity["required_skills"].is_object()
            ) {
                continue;
            }

            OpportunityResult result =
                analyzeOpportunity(
                    student,
                    opportunity
                );

            
            if (!result.skills.empty()) {
                results.push_back(result);
            }
        }

        sort(
            results.begin(),
            results.end(),
            [](const OpportunityResult& first,
               const OpportunityResult& second) {
                return first.opportunityScore >
                       second.opportunityScore;
            }
        );
        return results;
    }
};