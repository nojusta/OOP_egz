#include "functions.h"

// Funkcija, kuri nuskaito TLD faila
std::unordered_set<std::string> LoadTLDs(const std::string& filename) {
    std::unordered_set<std::string> tlds;
    std::ifstream tldFile(filename);
    if (!tldFile.is_open()) {
        std::cerr << "Error: Could not open TLD file." << std::endl;
        return tlds;
    }

    std::string tld;
    while (std::getline(tldFile, tld)) {
        if (!tld.empty()) {
            tlds.insert("." + tld);  // prideda taska prie TLD
        }
    }

    return tlds;
}

// Skaito faila ir sudeda zodzius i map
void Read_File(std::ifstream& in, std::map<std::string, std::vector<int>>& zodziai) {
    std::string line;
    int line_number = 1;
    std::regex word_regex(R"((\b[-ąčęėįšųūžĄČĘĖĮŠŲŪŽa-zA-Z]+\b))");

    while (std::getline(in, line)) {
        std::sregex_iterator words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
        std::sregex_iterator words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::string word = (*i).str();
            std::transform(word.begin(), word.end(), word.begin(), ::tolower); // konvertuoja i mazasias raides
            zodziai[word].push_back(line_number);
        }
        line_number++;
    }
}

// Suskaiciuoja kiek kartu pasikartoja kiekvienas zodis
void Counter(const std::map<std::string, std::vector<int>>& zodziai, std::unordered_map<std::string, int>& wordCount) {
    for (const auto& pair : zodziai) {
        wordCount[pair.first] = pair.second.size();
    }
}

// Suranda URL adresus tekste
void FindURLs(std::ifstream& in, std::vector<std::string>& urls, const std::unordered_set<std::string>& tlds) {
    std::string line;
    std::regex url_regex(R"((https?:\/\/[^\s]+|www\.[^\s]+|[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))");

    while (std::getline(in, line)) {
        std::sregex_iterator urls_begin = std::sregex_iterator(line.begin(), line.end(), url_regex);
        std::sregex_iterator urls_end = std::sregex_iterator();

        for (std::sregex_iterator i = urls_begin; i != urls_end; ++i) {
            std::string potential_url = (*i).str();
            std::transform(potential_url.begin(), potential_url.end(), potential_url.begin(), ::tolower); // konvertuoja i mazasias raides

            // Extract the domain part to validate against TLDs
            std::regex domain_regex(R"(([a-zA-Z0-9.-]+)\.([a-zA-Z]{2,}))");
            std::smatch domain_match;
            if (std::regex_search(potential_url, domain_match, domain_regex)) {
                std::string domain = domain_match.str(0);
                size_t pos = domain.find_last_of('.');
                while (pos != std::string::npos) {
                    std::string tld = domain.substr(pos);
                    if (tlds.find(tld) != tlds.end()) {
                        urls.push_back(potential_url);
                        break;
                    }
                    pos = domain.find_last_of('.', pos - 1);
                }
            }
        }
    }
}

int visual_width(const std::string& str) {
    return str.size();
}

// Iraso rezultatus i failus
void writeOutput(const std::unordered_map<std::string, int>& wordCount, 
                 const std::map<std::string, std::vector<int>>& wordLines, 
                 const std::vector<std::string>& urls) {
    try {
        std::ofstream outputFile("output.txt");
        if (outputFile) {
            if (!wordLines.empty()) {
                int wordColumnWidth = 30;
                int countColumnWidth = 10;
                outputFile << std::left << std::setw(wordColumnWidth) << "Žodis" << std::setw(countColumnWidth) << " Kiekis" << "  Eilučių Nr.\n";
                outputFile << std::string(wordColumnWidth + countColumnWidth + 12, '-') << "\n";
                
                for (const auto& entry : wordLines) {
                    if (entry.second.size() > 1) {
                        auto countIt = wordCount.find(entry.first);
                        if (countIt != wordCount.end()) {
                            outputFile << std::left << entry.first;
                            int visualPadding = wordColumnWidth - visual_width(entry.first);
                            for (int i = 0; i < visualPadding; ++i) {
                                outputFile << " ";
                            }
                            outputFile << std::setw(countColumnWidth) << countIt->second;
                            for (int line : entry.second) {
                                outputFile << " " << line;
                            }
                            outputFile << "\n";
                        }
                    }
                }
            }

            outputFile << "\n";
            outputFile.close();
        }

        // Iraso URL adresus
        std::ofstream urlFile("urls.txt");
        if (urlFile) {
            urlFile << "URL skaičius: " << urls.size() << ".\n";
            urlFile << std::string(20, '-') << "\n";
            for (const auto& url : urls) {
                urlFile << url << "\n";
            }
            urlFile << "\n";
            urlFile.close();
        }
    } catch (...) {
        std::cerr << "Nenumatyta klaida rašant į failą." << std::endl;
    }
}

