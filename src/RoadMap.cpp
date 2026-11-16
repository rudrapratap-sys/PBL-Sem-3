#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Job
{
private:
    string name;
    vector<string> skills;
    vector<vector<int>> adj;

    int getStudentLevel(Student& student,string& skillName)
    {
        for (auto& item : student.getSkills())
        {
            if (Helper::compare(item.first, skillName))
            {
                return item.second;
            }
        }
        return 0;
    }

public:
    Job(string jobName,vector<string> jobSkills)
    {
        name = jobName;
        skills = jobSkills;

        int n = skills.size();
        adj.resize(n);
        for (int i = 0; i < n - 1; i++)
        {
            adj[i].push_back(i + 1);
        }
    }

    string getName()
    {
        return name;
    }

    void printList(vector<int>& list,vector<int>& levels)
    {
        for (int i = 0; i < (int)list.size(); i++)
        {
            if (i > 0)
            {
                cout << " -> ";
            }
            cout << "[" << skills[list[i]] << " (" << levels[list[i]] << "/10)]";
        }
        cout << "\n";
    }

    void showRoadmap(Student& student)
    {
        const int STRONG_LEVEL = 8;
        int n = skills.size();
        cout << "\n===== Roadmap: " << name << " =====\n";

        if (n == 0)
        {
            cout << "No skills available for this job.\n";
            return;
        }

        vector<int> levels(n, 0);
        vector<int> learnFirst;
        vector<int> reviseLater;
        int mastered = 0;
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            levels[current] = getStudentLevel(student, skills[current]);
            if (levels[current] == 10)
            {
                mastered++;
            }
            else if (levels[current] >= STRONG_LEVEL)
            {
                reviseLater.push_back(current);
            }
            else
            {
                learnFirst.push_back(current);
            }
            for (int next : adj[current])
            {
                if (!visited[next])
                {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        if (learnFirst.empty() && reviseLater.empty())
        {
            cout << "All skills mastered! You are ready for this job.\n";
            return;
        }
        if (!learnFirst.empty())
        {
            cout << "\nLearn first (in this order):\n";
            printList(learnFirst, levels);
        }
        else
        {
            cout << "\nNothing new to learn. Just revise your strong skills.\n";
        }
        if (!reviseLater.empty())
        {
            cout << "\nRevise later (you are already strong):\n";
            printList(reviseLater, levels);
        }
        if (mastered > 0)
        {
            cout << "\nSkills already mastered (10/10) and skipped: " << mastered << "(";

            bool firstName = true;
            for(int i=0; i<n; i++)
            {
                if (levels[i]==10)
                {
                    if(!firstName)
                    {
                        cout << ",";
                    }
                    cout << skills[i];
                    firstName = false;
                }
            }
            cout << ")\n";
        }
    }
};


class Roadmap
{
private:
    vector<Job> jobs;

public:
    Roadmap()
    {
        jobs.push_back(Job("Software Developer",
            {"C++", "OOP", "Data Structures", "Algorithms",
             "Git", "SQL", "System Design"}));

        jobs.push_back(Job("Web Developer",
            {"HTML", "CSS", "JavaScript", "Git",
             "React", "Node.js", "SQL"}));

        jobs.push_back(Job("Data Analyst",
            {"Excel", "SQL", "Python", "Statistics",
             "Pandas", "Data Visualization", "Power BI"}));

        jobs.push_back(Job("Data Scientist",
            {"Python", "Statistics", "SQL", "Pandas",
             "Data Visualization", "Machine Learning", "Deep Learning"}));

        jobs.push_back(Job("AI/ML Engineer",
            {"Python", "Mathematics", "Statistics", "Machine Learning",
             "Deep Learning", "NLP", "Generative AI"}));

        jobs.push_back(Job("Cyber Security Analyst",
            {"Networking", "Operating Systems", "Linux",
             "Python", "Security Basics", "Ethical Hacking"}));

        jobs.push_back(Job("Mobile App Developer",
            {"Programming Basics", "OOP", "Java",
             "Android Development", "APIs", "Git"}));

        jobs.push_back(Job("Cloud Engineer",
            {"Linux", "Networking", "Python", "Cloud Computing",
             "Docker", "Kubernetes", "CI/CD"}));

        jobs.push_back(Job("DevOps Engineer",
            {"Linux", "Git", "Scripting", "CI/CD",
             "Docker", "Kubernetes", "Cloud Computing"}));

        jobs.push_back(Job("UI/UX Designer",
            {"Design Principles", "Color Theory", "Typography",
             "Wireframing", "Prototyping", "Figma", "Usability Testing"}));

        jobs.push_back(Job("Database Administrator",
            {"SQL", "Database Design", "Normalization",
             "Query Optimization", "Backup and Recovery", "Database Security"}));

        jobs.push_back(Job("Software Tester",
            {"Programming Basics", "Testing Basics", "Test Cases",
             "Bug Tracking", "SQL", "Automation Testing", "Selenium"}));
    }

    void showMenu(Student& student)
    {
        int choice;
        int total = jobs.size();
        cout << "\n===== CAREER ROADMAP =====\n";
        cout << "--- Available Job Roles ---\n";
        for (int i = 0; i < total ; i++)
        {
            cout << i + 1 << ". " << jobs[i].getName() << "\n";
        }
        cout << "0. Back to Dashboard\n";
        cout << "\nChoose a job role to see what to learn next, based on your skills:";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 0:
            break;
        case 1:
            jobs[0].showRoadmap(student);
            break;
        case 2:
            jobs[1].showRoadmap(student);
            break;
        case 3:
            jobs[2].showRoadmap(student);
            break;
        case 4:
            jobs[3].showRoadmap(student);
            break;
        case 5:
            jobs[4].showRoadmap(student);
            break;
        case 6:
            jobs[5].showRoadmap(student);
            break;
        case 7:
            jobs[6].showRoadmap(student);
            break;
        case 8:
            jobs[7].showRoadmap(student);
            break;
        case 9:
            jobs[8].showRoadmap(student);
            break;
        case 10:
            jobs[9].showRoadmap(student);
            break;
        case 11:
            jobs[10].showRoadmap(student);
            break;
        case 12:
            jobs[11].showRoadmap(student);
            break;
        default:
            cout << "Invalid choice! Enter a number from 1 to " << total << ".\n";
        }
    }
};