/*
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Roadmap.h"
using namespace std;

// Job constructor
Job::Job(string jobName, vector<string> jobSkills)
{
    name = jobName;
    skills = jobSkills;
    int n = skills.size();
    adj.resize(n);
    // Creating graph
    for (int i = 0; i < n - 1; i++)
    {
        adj[i].push_back(i + 1);
    }
}
// Return job name
string Job::getName()
{
    return name;
}
// Traverse the job graph using BFS
void Job::traverse()
{
    int n = skills.size();
    if (n == 0)
    {
        cout << "No skills available.\n";
        return;
    }
    vector<bool> visited(n, false);
    queue<int> q;

    // BFS from the first skill
    q.push(0);
    visited[0] = true;
    cout << "\nJob Role: " << name << "\n\n";
    bool first = true;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        if (!first)
        {
            cout << " -> ";
        }
        cout << "[" << skills[current] << "]";
        first = false;
        for (int next : adj[current])
        {
            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    cout << endl;
}
// Roadmap constructor
Roadmap::Roadmap()
{
    jobs.push_back(Job("Software Developer",
        {"C++", "OOP", "Data Structures", "Algorithms"}));

    jobs.push_back(Job("Web Developer",
        {"HTML", "CSS", "JavaScript", "React"}));

    jobs.push_back(Job("Data Analyst",
        {"Python", "SQL", "Excel", "Statistics"}));

    jobs.push_back(Job("AI/ML Engineer",
        {"Python", "Mathematics", "Machine Learning", "Deep Learning"}));

    jobs.push_back(Job("Cybersecurity Analyst",
        {"Networking", "Linux", "Python", "Security Basics"}));

    jobs.push_back(Job("Cloud Engineer",
        {"Linux", "Networking", "Cloud Computing", "Docker"}));

    jobs.push_back(Job("DevOps Engineer",
        {"Linux", "Git", "Docker", "CI/CD"}));

    jobs.push_back(Job("Mobile App Developer",
        {"Programming", "OOP", "Android", "APIs"}));
}

// Return total number of jobs
int Roadmap::getJobCount()
{
    return jobs.size();
}
// Return job name at a given index
string Roadmap::getJobName(int index)
{
    if (index >= 0 && index < jobs.size())
    {
        return jobs[index].getName();
    }
    return "Invalid Job";
}
// Display required skills for a selected job
void Roadmap::displayJobGraph(int index)
{
    if (index >= 0 && index < jobs.size())
    {
        jobs[index].traverse();
    }
    else
    {
        cout << "Invalid job selection.\n";
    }
}
    */