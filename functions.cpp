#include "functions.h"

// Skaito faila ir sudeda zodzius i map
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
            std::transform(word.begin(), word.end(), word.begin(), ::tolower); // konvertuoja i mazasias raides
            zodziai[word].push_back(line_number);
        }
        line_number++;
    }
}

// Suskaiciuoja kiek kartu pasikartoja kiekvienas zodis
void Counter(const std::map<std::string, std::vector<int>>& zodziai, std::unordered_map<std::string, int>& wordCount)
{
    for (const auto& pair : zodziai) {
        wordCount[pair.first] = pair.second.size();
    }
}

// Suranda URL adresus tekste
void FindURLs(std::ifstream& in, std::vector<std::string>& urls)
{
    std::string word;
    std::string line;
    std::vector<std::string> domains = {".com", ".net", ".org", ".lt", ".edu", ".gov"};

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            for (const std::string& tld : domains) {
                if (word.find(tld) != std::string::npos) {
                    urls.push_back(word);
                    break;
                }
            }
        }
    }
}

int visual_width(const std::string& str) {
    int width = 0;
    for (char ch : str) {
        if (static_cast<unsigned char>(ch) >= 128) {
            if (ch >= -60 && ch <= -9) {
                width += 1;
            } else {
                width += 2; 
            }
        } else {
            width += 1;
        }
    }
    return width;
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