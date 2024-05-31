#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai);

void Counter(std::map<std::string, std::vector<int>>& zodziai);

void WriteCrossReference(const std::map<std::string, std::vector<int>>& zodziai);

void FindURLs(std::ifstream& in, std::set<std::string>& urls);

#endif // FUNCTIONS_H