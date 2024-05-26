#include "functions.h"

std::string processWord(const std::string& word) {
    std::string cleaned;
    try {
        std::regex notFixedRegex("[^\\w]+");
        cleaned = std::regex_replace(word, notFixedRegex, "");
        std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
    } catch (std::regex_error& e) {
        std::cerr << "Regex error'as: " << e.what() << std::endl;
        std::cerr << "Įvyko klaida apdorojant žodį: " << word << std::endl;
    }
    return cleaned;
}

void addToTheList(const std::string& word, std::map<std::string, std::vector<int>>& wordLines, int lineNumber) {
    if (word.empty()) 
        return;

    try {
        auto it = wordLines.find(word);

        if (it == wordLines.end()) {
            wordLines[word] = {lineNumber};
        }
        else {
            if (lineNumber != it->second.back()) {
                it->second.push_back(lineNumber);
            }
        }
    } catch (...) {
        std::cerr << "Nežinoma klaida įdedant žodį į sąrašą." << std::endl;
    }
}

void processLine(const std::string& line, int lineNumber, std::unordered_map<std::string, int>& wordCount, std::map<std::string, std::vector<int>>& wordLines, std::vector<std::string>& urls) {
    try {
        std::regex urlRegex("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
        std::istringstream stream(line);
        std::string word;
        while (stream >> word) {
            if (std::regex_match(word, urlRegex)) {
                urls.push_back(word);
            }
            else if (!std::all_of(word.begin(), word.end(), ::isdigit)) {
                std::string cleanedWord = processWord(word);
                if (!cleanedWord.empty()) {
                    wordCount[cleanedWord]++;
                    addToTheList(cleanedWord, wordLines, lineNumber);
                }
            }
        }
    } catch (std::regex_error& e) {
        std::cerr << "Regex klaida: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Nežinoma klaida apdorojant eilutę." << std::endl;
    }
}

void writeOutput(const std::map<std::string, std::vector<int>>& wordLines, const std::vector<std::string>& urls) {
    try {
        std::ofstream outputFile("output.txt");
        if (outputFile) {
            if (!wordLines.empty()) {
                outputFile << std::left << std::setw(30) << "Žodis" << std::setw(10) << " Kiekis" << " Eilučių Nr.\n";
                outputFile << std::string(50, '-') << "\n";
                for (const auto& entry : wordLines) {
                    if (entry.second.size() > 1){
                        outputFile << std::left << std::setw(30) << entry.first << std::setw(10) << entry.second.size();

                        for (int line : entry.second) {
                            outputFile << std::setw(4) << line;
                        }

                        outputFile << "\n";
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
        std::cerr << "Nežinoma klaida įvyko rašant į failą." << std::endl;
    }
}