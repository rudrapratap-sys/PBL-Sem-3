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


    bool compare(const string& first, const string& second) {
        if(toLower(trim(first)) == toLower(trim(second))){
            return true;
        }
        else{
            return false;
        }
    }
}
