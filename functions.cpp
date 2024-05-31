#include "functions.h"

void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai)
{
    std::string line;
    int line_number = 1;
    std::regex word_regex(R"((\b[-ąčęėįšųūžĄČĘĖĮŠŲŪŽa-zA-Z]+\b))");

    while (std::getline(in, line)) {
        std::sregex_iterator words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
        std::sregex_iterator words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::string word = (*i).str();
            std::transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert to lowercase
            zodziai[word].push_back(line_number);
        }
        line_number++;
    }
}

void Counter(const std::map<std::string, std::vector<int>>& zodziai)
{
    std::ofstream out("counter.txt");
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
            std::set<int> unique_lines(pair.second.begin(), pair.second.end());
            for (int line : unique_lines) {
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
