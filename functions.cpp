#include "functions.h"

void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai)
{
    std::string zodis;
    std::string line;
    int line_number = 1;

    while (std::getline(in, line)) {
        size_t pos = 0;
        while ((pos = line.find_first_of("- – ")) != std::string::npos) {
            std::string zodis = line.substr(0, pos);
            zodis.erase(std::remove_if(zodis.begin(), zodis.end(), [](char c) { return std::ispunct(c) || std::isdigit(c); }), zodis.end());
            if (!zodis.empty()) {
                zodziai[zodis].push_back(line_number);
            }
            line = line.substr(pos + 1);
        }
        if (!line.empty()) {
            line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return std::ispunct(c) || std::isdigit(c); }), line.end());
            zodziai[line].push_back(line_number);
        }
        line_number++;
    }
}


void Counter(std::map<std::string, std::vector<int>>& zodziai)
{
    std::ofstream out ("counter.txt");
    for (const auto& pair : zodziai) {
        out << pair.first << ": " << pair.second.size() << "\n";
    }
}

void WriteCrossReference(const std::map<std::string, std::vector<int>>& zodziai)
{
    std::ofstream out("cross_reference.txt");
    for (const auto& pair : zodziai) {
        if (pair.second.size() > 1) {
            out << pair.first << ": ";
            for (int line : pair.second) {
                out << line << " ";
            }
            out << "\n";
        }
    }
}

void FindURLs(std::ifstream& in, std::set<std::string>& urls)
{
    std::string word;
    std::string line;
    std::vector<std::string> domains = {".com", ".net", ".org", ".lt", ".edu", ".gov"};

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            for (const std::string& tld : domains) {
                if (word.find(tld) != std::string::npos) {
                    urls.insert(word);
                    break;
                }
            }
        }
    }

    std::ofstream out("urls.txt");
    for(const std::string& url : urls) {
        out << url << "\n";
    }
}