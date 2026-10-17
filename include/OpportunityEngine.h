#pragma once

using namespace std ;

#include <string>
#include "Student.h"

class OpportunityEngine {
private:
    string csvFile = "opportunities_200.csv";
    string outputFile = "filtered.json";

public:
    // Filter opportunities and save them to JSON
    bool filter(Student& student);
};
