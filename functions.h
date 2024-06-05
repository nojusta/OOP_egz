#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include <algorithm>
#include <iostream>
#include <iomanip>

// Function declarations
void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai);
void Counter(const std::map<std::string, std::vector<int>>& zodziai, std::unordered_map<std::string, int>& wordCount);
void FindURLs(std::ifstream& in, std::vector<std::string>& urls, const std::unordered_set<std::string>& tlds);
int visual_width(const std::string& str);
void writeOutput(const std::unordered_map<std::string, int>& wordCount, 
                 const std::map<std::string, std::vector<int>>& wordLines, 
                 const std::vector<std::string>& urls);
std::unordered_set<std::string> LoadTLDs(const std::string& filename);

#endif
