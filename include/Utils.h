#pragma once

#include <string>
#include <vector>

using namespace std;

namespace Utils {
    string trim(const string& text);
    string toLower(string text);
    vector<string> split(const string& text, char delimiter);
    vector<string> splitAndTrim(const string& text, char delimiter);
    string join(const vector<string>& items, char delimiter);
    bool equalsIgnoreCase(const string& first, const string& second);
}
