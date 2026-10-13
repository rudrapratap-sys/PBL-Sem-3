#include "Utils.h"

#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

namespace Utils {
    string trim(const string& text) {
        size_t start = 0;
        while (start < text.size() && isspace(static_cast<unsigned char>(text[start]))) {
            start++;
        }

        size_t end = text.size();
        while (end > start && isspace(static_cast<unsigned char>(text[end - 1]))) {
            end--;
        }

        return text.substr(start, end - start);
    }

    string toLower(string text) {
        transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
            return static_cast<char>(tolower(ch));
        });
        return text;
    }

    vector<string> split(const string& text, char delimiter) {
        vector<string> parts;
        stringstream ss(text);
        string item;

        while (getline(ss, item, delimiter)) {
            parts.push_back(item);
        }

        return parts;
    }

    vector<string> splitAndTrim(const string& text, char delimiter) {
        vector<string> parts;
        for (const string& item : split(text, delimiter)) {
            string cleaned = trim(item);
            if (!cleaned.empty()) {
                parts.push_back(cleaned);
            }
        }
        return parts;
    }

    string join(const vector<string>& items, char delimiter) {
        string result;
        for (size_t i = 0; i < items.size(); i++) {
            result += items[i];
            if (i + 1 < items.size()) {
                result += delimiter;
            }
        }
        return result;
    }

    bool equalsIgnoreCase(const string& first, const string& second) {
        return toLower(trim(first)) == toLower(trim(second));
    }
}
