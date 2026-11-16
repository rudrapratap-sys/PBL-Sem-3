#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class OpportunityEngine {
private:
    string csvFile = "opportunities_200.csv";
    string outputFile = "filtered.json";

public:
    bool filter(Student& student) {
        ifstream file(csvFile);

        if (!file) {
            cerr << "Error: Cannot open " << csvFile << endl;
            return false;
        }

        vector<vector<string>> rows = readCSV(file);
        file.close();

        if (rows.empty()) {
            cerr << "Error: CSV file is empty." << endl;
            return false;
        }

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
            Helper::toLower(student.getPreferredCategory());

        json filteredOpportunities = json::array();

        for (int i = 1; i < rows.size(); i++) {

            const vector<string>& row = rows[i];

            if (row.size() != rows[0].size()) {
                continue;
            }

            try {
                double minimumGPA =
                    stod(row[columns["min_gpa"]]);

                string category =
                    Helper::toLower(row[columns["category"]]);

                if (minimumGPA > cgpa) {
                    continue;
                }

                if (preferredCategory != "any" &&
                    category != preferredCategory) {
                    continue;
                }

                json opportunity;

                for (const auto& column : columns) {
                    const string& key = column.first;
                    const string& value = row[column.second];

                    if (key == "min_gpa") {
                        opportunity[key] = stod(value);
                    }
                    else if (key == "required_skills") {
                        json skills = json::parse(
                            value, nullptr, false
                        );

                        if (skills.is_discarded()) {
                            opportunity[key] = value;
                        }
                        else {
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
                continue;
            }
        }

        json result;

        result["student"] = {
            {"userId", student.getUserId()},
            {"name", student.getName()},
            {"email", student.getEmail()},
            {"cgpa", cgpa},
            {"preferredCategory", student.getPreferredCategory()}
        };

        result["opportunities"] = filteredOpportunities;

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

private:
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
                }
                else {
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

        if (!field.empty() || !row.empty()) {
            row.push_back(field);
            rows.push_back(row);
        }

        return rows;
    }
};
