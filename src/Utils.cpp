#include "Utils.h"


using namespace std;

namespace Utils {
    string trim(const string& text) {
        int start = 0;
        int end = text.length() - 1;

        // Skip spaces from the beginning
        while (start < text.length() && text[start] == ' ') {
            start++;
        }

        // Skip spaces from the end
        while (end >= start && text[end] == ' ') {
            end--;
        }   

        return text.substr(start, end - start + 1);
    }

    string toLower(string text) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = text[i] + 32;
        }
    }

    return text;
}

    vector<string> split(const string& text, char delimiter) {
        vector<string> parts;
        string item = "";

        for (int i = 0; i < text.length(); i++) {
            if (text[i] == delimiter) {
                parts.push_back(item);
                item = "";
            } else {
                item += text[i];
            }
        }

        parts.push_back(item);

        return parts;
    }

    string join(const vector<string>& items, char delimiter) {
        string result = "";

        for (int i = 0; i < items.size(); i++) {
            result += items[i];

            if (i < items.size() - 1) {
                result += delimiter;
            }
        }

        return result;
    }

    vector<string> splitAndTrim(const string& text, char delimiter) {
        vector<string> parts = split(text, delimiter);
        vector<string> result;

        for (int i = 0; i < parts.size(); i++) {
            string item = trim(parts[i]);

            if (item != "") {
                result.push_back(item);
            }
        }

        return result;
    }

    bool equalsIgnoreCase(const string& first, const string& second) {
        return toLower(trim(first)) == toLower(trim(second));
    }
}
