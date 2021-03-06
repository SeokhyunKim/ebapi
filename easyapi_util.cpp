#include "easyapi_util.hpp"
#include <iostream>

using namespace std;

vector<string> extractVariables(const string& templateStr) {
    size_t pos = templateStr.find("${");
    if (pos == string::npos) {
        return vector<string>();
    }
    vector<string> variables;
    while (pos != string::npos) {
        size_t endPos = templateStr.find("}", pos + 2);
        if (endPos != string::npos && (endPos - pos - 2 > 0)) {
            string var = trim(templateStr.substr(pos + 2, endPos - pos - 2));
            if (!var.empty()) {
                variables.push_back(var);
            }
        }
        pos = templateStr.find("${", pos + 2);
    }
    return variables;
}

vector<string> tokenizeCSVLine(string line, const string& delimiters) {
    char* lineary = (char*)line.c_str();
    char* token;
    char* rest = lineary;
    vector<string> tokens;
    while ((token = strtok_r(rest, delimiters.c_str(), &rest))) {
        tokens.push_back(string(token));
    }
    return tokens;
}

vector<string> removeFunctions(const vector<string>& vec) {
    vector<string> removed;
    for (auto& str : vec) {
        if (str.length() <= 0 || str[0] == '=') {
            continue;
        }
        removed.push_back(str);
    }
    return removed;
}

bool isSame(const vector<string>& vec1, const vector<string>& vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (auto& str1 : vec1) {
        bool find = false;
        for (auto& str2 : vec2) {
            if (0 == str1.compare(str2)) {
                find = true;
                break;
            }
        }
        if (!find) {
            return false;
        }
    }
    return true;
}

int getNumVariablesExceptFunctions(const vector<std::string>& vec) {
    vector<string> vecExceptFunctions = removeFunctions(vec);
    return vecExceptFunctions.size();
}

string trim(string const& str)
{
    if(str.empty())
        return str;

    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}



