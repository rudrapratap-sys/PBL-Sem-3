#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct SkillAnalysis
{
    string skillName;
    int currentLevel;
    int requiredLevel;
    string status;
};

struct OpportunityResult
{
    string opportunityName;
    string location;
    string category;

    double readinessScore;
    double opportunityScore;

    vector<SkillAnalysis> skillAnalysis;
    vector<string> skillsToImprove;
};

class SkillGapAnalyzer
{
private:

    int getStudentLevel(
        unordered_map<string, int>& studentSkills,
        const string& skillName)
    {
        for (auto& skill : studentSkills)
        {
            if (Utils::compare(skill.first, skillName))
            {
                return skill.second;
            }
        }

        return 0;
    }

    string getStatus(
        int current,
        int required)
    {
        if (current >= required)
        {
            return "MATCHED";
        }

        if (current >= required * 0.7)
        {
            return "NEEDS IMPROVEMENT";
        }

        return "NOT MATCHED";
    }

    double calculateReadinessScore(
        unordered_map<string, int>& studentSkills,
        json requiredSkills)
    {
        int matchedPoints = 0;
        int totalRequiredPoints = 0;

        for (auto it = requiredSkills.begin();
             it != requiredSkills.end();
             ++it)
        {
            string skillName = it.key();
            int requiredLevel = it.value();

            int currentLevel =
                getStudentLevel(
                    studentSkills,
                    skillName
                );

            if (currentLevel < requiredLevel)
            {
                matchedPoints += currentLevel;
            }
            else
            {
                matchedPoints += requiredLevel;
            }

            totalRequiredPoints += requiredLevel;
        }

        if (totalRequiredPoints == 0)
        {
            return 0.0;
        }

        return (matchedPoints * 100.0)
               / totalRequiredPoints;
    }

    double calculateOpportunityScore(
        double readiness,
        double cgpa)
    {
        double cgpaScore =
            (cgpa / 10.0) * 100.0;

        return
            (0.7 * readiness) +
            (0.3 * cgpaScore);
    }

    OpportunityResult analyzeOpportunity(
        Student& student,
        json opportunity)
    {
        OpportunityResult result;

        result.opportunityName =
            opportunity.value("name", "Unknown");

        result.location =
            opportunity.value("location", "Unknown");

        result.category =
            opportunity.value("category", "Unknown");

        unordered_map<string, int> studentSkills =
            student.getSkills();

        json requiredSkills =
            opportunity["required_skills"];

        result.readinessScore =
            calculateReadinessScore(
                studentSkills,
                requiredSkills
            );

        result.opportunityScore =
            calculateOpportunityScore(
                result.readinessScore,
                student.getCgpa()
            );

        for (auto it = requiredSkills.begin();
             it != requiredSkills.end();
             ++it)
        {
            SkillAnalysis skill;

            skill.skillName = it.key();

            skill.requiredLevel = it.value();

            skill.currentLevel =
                getStudentLevel(
                    studentSkills,
                    skill.skillName
                );

            skill.status =
                getStatus(
                    skill.currentLevel,
                    skill.requiredLevel
                );

            result.skillAnalysis.push_back(skill);

            if (skill.status != "MATCHED")
            {
                result.skillsToImprove.push_back(
                    skill.skillName
                );
            }
        }

        return result;
    }

    void sortResults(
        vector<OpportunityResult>& results)
    {
        for (int i = 0;
             i < results.size() - 1;
             i++)
        {
            for (int j = i + 1;
                 j < results.size();
                 j++)
            {
                if (results[j].opportunityScore >
                    results[i].opportunityScore)
                {
                    OpportunityResult temp =
                        results[i];

                    results[i] = results[j];
                    results[j] = temp;
                }
            }
        }
    }

public:

    vector<OpportunityResult> analyze(
        Student& student)
    {
        vector<OpportunityResult> results;

        ifstream file("filtered.json");

        if (!file)
        {
            return results;
        }

        json data;

        try
        {
            file >> data;
        }
        catch (...)
        {
            return results;
        }

        json opportunities =
            data["opportunities"];

        for (int i = 0;
             i < opportunities.size();
             i++)
        {
            results.push_back(
                analyzeOpportunity(
                    student,
                    opportunities[i]
                )
            );
        }

        sortResults(results);

        return results;
    }

    void displayOpportunities(
        Student& student)
    {
        vector<OpportunityResult> results =
            analyze(student);

        if (results.empty())
        {
            cout << "No opportunities could be analyzed.\n";
            return;
        }

        cout << "\n****************************************************************************************************\n";
        cout << "                                          TOP 5 OPPORTUNITIES MATCHES                                          \n";
        cout << "****************************************************************************************************\n";

        int count = 5;

        if (results.size() < 5)
        {
            count = results.size();
        }

        for (int i = 0; i < count; i++)
        {
            OpportunityResult& result =
                results[i];
            cout << "\n~~~~~~~~RANK " << (i + 1) << "~~~~~~~~\n";

            // cout << "\nOpportunity ID : " << result.
            cout << "\nOpportunity : "
                 << result.opportunityName
                 << "\n";

            cout << "\nLocation : "
                 << result.location
                 << "\n";

            cout << "\nCategory : "
                 << result.category
                 << "\n";

            cout << fixed
                 << setprecision(2);
             cout << "\nOpportunity Match Score : "
                  << result.opportunityScore
                  << " %\n";

            cout<<"Our analysis suggests that there are "<<result.opportunityScore<<"% chances of you being selected for this opportunity.\n";
            cout << "\nReadiness Score          :"
                 << result.readinessScore<<"%\n";

            cout<<"You are "<<result.readinessScore<<"% prepared for this opportunity.\n";
           
            cout << "\n---------------------------------------------------------\n";
            cout << "SKILL ANALYSIS\n";
            cout << left
                 << setw(20) << "Skill"
                 << setw(12) << "Current"
                 << setw(12) << "Required"
                 << setw(20) << "Status"
                 << "\n";

            for (int j = 0;
                 j < result.skillAnalysis.size();
                 j++)
            {
                SkillAnalysis& skill =
                    result.skillAnalysis[j];

                cout << left
                     << setw(20) << skill.skillName
                     << setw(12) << skill.currentLevel
                     << setw(12) << skill.requiredLevel
                     << setw(20) << skill.status
                     << "\n";
            }

            cout << "\n---------------------------------------------------------\n";
            cout << "SKILLS TO IMPROVE\n";

            if (result.skillsToImprove.empty())
            {
                cout << "All required skills are matched.\n";
            }
            else
            {
                for (int j = 0;
                     j < result.skillsToImprove.size();
                     j++)
                {
                    cout << "- "
                         << result.skillsToImprove[j]
                         << "\n";
                }
            }

            cout<<"==================================================================================================\n";
        }
    }
};