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

void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai);
void Counter(const std::map<std::string, std::vector<int>>& zodziai);
void WriteCrossReference(const std::map<std::string, std::vector<int>>& zodziai);
void FindURLs(std::ifstream& in, std::set<std::string>& urls);

#endif // FUNCTIONS_H
