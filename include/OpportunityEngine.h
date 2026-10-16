#pragma once

#include "Student.h"

#include <string>

class OpportunityEngine {
private:
    std::string csvFile;
    std::string outputFile;

public:
    explicit OpportunityEngine(
        const std::string& csvFile = "opportunities_200.csv",
        const std::string& outputFile = "filtered.json");

    bool filter(Student& student);
};
