#include "OpportunityEngine.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;


// Read CSV correctly, including quoted commas and newlines
static vector<vector<string>> readCSV(istream& file) {
    vector<vector<string>> rows;
    vector<string> row;
    string field;
    char ch;
    bool insideQuotes = false;

    while (file.get(ch)) {
        if (ch == '"') {
            if (insideQuotes && file.peek() == '"') {
                field += '"';
                file.get(ch);
            } else {
                insideQuotes = !insideQuotes;
            }
        }
        else if (ch == ',' && !insideQuotes) {
            row.push_back(field);
            field.clear();
        }
        else if ((ch == '\n' || ch == '\r') && !insideQuotes) {
            if (ch == '\r' && file.peek() == '\n') {
                file.get(ch);
            }

            row.push_back(field);
            rows.push_back(row);

            row.clear();
            field.clear();
        }
        else {
            field += ch;
        }
    }

    // Handle the last row if the file has no final newline
    if (!field.empty() || !row.empty()) {
        row.push_back(field);
        rows.push_back(row);
    }

    return rows;
}


// Filter opportunities
bool OpportunityEngine::filter(Student& student) {

    // 1. Open the CSV file
    ifstream file(csvFile);

    if (!file) {
        cerr << "Error: Cannot open " << csvFile << endl;
        return false;
    }

    // 2. Read all CSV records
    vector<vector<string>> rows = readCSV(file);
    file.close();

    if (rows.empty()) {
        cerr << "Error: CSV file is empty." << endl;
        return false;
    }

    // 3. Find column positions using the header
    unordered_map<string, int> columns;

    for (int i = 0; i < rows[0].size(); i++) {
        columns[rows[0][i]] = i;
    }

    if (columns.find("category") == columns.end() ||
        columns.find("min_gpa") == columns.end()) {
        cerr << "Error: Required CSV columns are missing." << endl;
        return false;
    }

    double cgpa = student.getCgpa();
    string preferredCategory =
        Utils::toLower(student.getPreferredCategory());

    json filteredOpportunities = json::array();

    // 4. Process each opportunity
    for (int i = 1; i < rows.size(); i++) {

        const vector<string>& row = rows[i];

        // Skip incomplete records
        if (row.size() != rows[0].size()) {
            continue;
        }

        try {
            double minimumGPA =
                stod(row[columns["min_gpa"]]);

            string category =
                Utils::toLower(row[columns["category"]]);

            // Check CGPA
            if (minimumGPA > cgpa) {
                continue;
            }

            // Check preferred category
            if (preferredCategory != "any" &&
                category != preferredCategory) {
                continue;
            }

            // 5. Convert the matching CSV row to JSON
            json opportunity;

            for (const auto& column : columns) {
                const string& key = column.first;
                const string& value = row[column.second];

                if (key == "min_gpa") {
                    opportunity[key] = stod(value);
                }
                else if (key == "required_skills") {
                    // Convert skills from JSON text into a JSON object
                    json skills = json::parse(
                        value, nullptr, false
                    );

                    if (skills.is_discarded()) {
                        opportunity[key] = value;
                    } else {
                        opportunity[key] = skills;
                    }
                }
                else {
                    opportunity[key] = value;
                }
            }

            filteredOpportunities.push_back(opportunity);
        }
        catch (const exception&) {
            // Skip records with invalid numeric values
            continue;
        }
    }

    // 6. Store student details and matching opportunities
    json result;

    result["student"] = {
        {"userId", student.getUserId()},
        {"name", student.getName()},
        {"email", student.getEmail()},
        {"cgpa", cgpa},
        {"preferredCategory", student.getPreferredCategory()}
    };

    result["opportunities"] = filteredOpportunities;

    // 7. Save the result to the JSON file
    ofstream output(outputFile);

    if (!output) {
        cerr << "Error: Cannot create " << outputFile << endl;
        return false;
    }

    output << result.dump(4) << '\n';

    if (!output) {
        cerr << "Error: Failed to write JSON file." << endl;
        return false;
    }

    cout << "Filtering completed successfully!" << endl;
    cout << "Matching opportunities: "
         << filteredOpportunities.size() << endl;
    cout << "Saved to: " << outputFile << endl;

    return true;
}
