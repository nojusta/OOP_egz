#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <iomanip>

// Function declarations
std::string processWord(const std::string& word);
void addToTheList(const std::string& word, std::map<std::string, std::vector<int>>& wordLines, int lineNumber);
void processLine(const std::string& line, int lineNumber, std::unordered_map<std::string, int>& wordCount, std::map<std::string, std::vector<int>>& wordLines, std::vector<std::string>& urls);
void writeOutput(const std::unordered_map<std::string, int>& wordCount, const std::map<std::string, std::vector<int>>& wordLines, const std::vector<std::string>& urls);
int visual_width(const std::string& s);

#endif // FUNCTIONS_H
