#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <regex>
#include <iomanip>
#include <cctype>
#include <iomanip>
#include <unordered_map>

void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai);

void Counter(const std::map<std::string, std::vector<int>>& zodziai, std::unordered_map<std::string, int>& wordCount);

void FindURLs(std::ifstream& in, std::vector<std::string>& urls);

int visual_width(const std::string& str);
void writeOutput(const std::unordered_map<std::string, int>& wordCount, 
                 const std::map<std::string, std::vector<int>>& wordLines, 
                 const std::vector<std::string>& urls);
#endif // FUNCTIONS_H
