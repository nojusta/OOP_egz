#include "functions.h"

std::string processWord(const std::string& word) {
    std::string cleaned;
    try {
        std::regex notFixedRegex("[^\\wąčęėįšųūžĄČĘĖĮŠŲŪŽ]+");
        cleaned = std::regex_replace(word, notFixedRegex, "");
        std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
    } catch (std::regex_error& e) {
        std::cerr << "Regex klaida: " << e.what() << std::endl;
        std::cerr << "Klaida apdorojant žodį: " << word << std::endl;
    }
    if (std::all_of(cleaned.begin(), cleaned.end(), ::isdigit)) {
        return "";
    }

    //std::cout << "Nuskaitytas zodis: " << cleaned << std::endl; // debuginimas

    return cleaned;
}

void addToTheList(const std::string& word, std::map<std::string, std::vector<int>>& wordLines, int lineNumber) {
    if (word.empty()) 
        return;

    try {
        auto it = wordLines.find(word);

        if (it == wordLines.end()) {
            wordLines[word] = {lineNumber};
        } else {
            if (lineNumber != it->second.back()) {
                it->second.push_back(lineNumber);
            }
        }
    } catch (...) {
        std::cerr << "Nenumatyta klaida pridedant žodį į sąrašą." << std::endl;
    }
}

void processLine(const std::string& line, int lineNumber, std::unordered_map<std::string, int>& wordCount, std::map<std::string, std::vector<int>>& wordLines, std::vector<std::string>& urls) {
    std::istringstream iss(line);
    std::string word;
    std::regex urlRegex(R"((https?://[^\s]+|www\.[^\s]+|[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}))");
    std::sregex_iterator begin(line.begin(), line.end(), urlRegex);
    std::sregex_iterator end;

    while (iss >> word) {
        std::string cleanedWord = processWord(word);
        if (!cleanedWord.empty()) {
            wordCount[cleanedWord]++;
            addToTheList(cleanedWord, wordLines, lineNumber);
        }
    }

    // Extract URLs
    for (std::sregex_iterator i = begin; i != end; ++i) {
        urls.push_back(i->str());
    }
}

void writeOutput(const std::unordered_map<std::string, int>& wordCount, const std::map<std::string, std::vector<int>>& wordLines, const std::vector<std::string>& urls) {
    try {
        std::ofstream outputFile("output.txt");
        if (outputFile) {
            if (!wordLines.empty()) {
                outputFile << std::left << std::setw(30) << "Žodis" << std::setw(10) << " Kiekis" << " Eilučių Nr.\n";
                outputFile << std::string(50, '-') << "\n";
                for (const auto& entry : wordLines) {
                    if (entry.second.size() > 1){
                        auto countIt = wordCount.find(entry.first);
                        if (countIt != wordCount.end()) {
                            outputFile << std::left << std::setw(30) << entry.first << std::setw(10) << countIt->second;
                            for (int line : entry.second) {
                                outputFile << std::setw(4) << line;
                            }
                            outputFile << "\n";
                        }
                    }
                }
            }

            outputFile << "\nURL skaičius: " << urls.size() << ".\n";
            outputFile << std::string(20, '-') << "\n";
            for (const auto& url : urls)
                outputFile << url << "\n";

            outputFile << "\n";
            outputFile.close();
        }
    } catch (...) {
        std::cerr << "Nenumatyta klaida rašant į failą." << std::endl;
    }
}
