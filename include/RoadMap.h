#ifndef ROADMAP_H
#define ROADMAP_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Job
{
private:
    string name;
    vector<string> skills;
    vector<vector<int>> adj;
public:
    Job(string jobName, vector<string> jobSkills);
    string getName();
    void traverse();
};

class Roadmap
{
private:
    vector<Job> jobs;
public:
    Roadmap();
    int getJobCount();
    string getJobName(int index);
    void displayJobGraph(int index);
};

#endif