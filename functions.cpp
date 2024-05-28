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
                int wordColumnWidth = 30;
                int countColumnWidth = 10;
                outputFile << std::left << std::setw(wordColumnWidth) << "Žodis" << std::setw(countColumnWidth) << " Kiekis" << "  Eilučių Nr.\n";
                outputFile << std::string(wordColumnWidth + countColumnWidth + 12, '-') << "\n";
                for (const auto& entry : wordLines) {
                    if (entry.second.size() > 1){
                        auto countIt = wordCount.find(entry.first);
                        if (countIt != wordCount.end()) {
                            int padding = wordColumnWidth - entry.first.size() + (entry.first.size() - visual_width(entry.first));
                            outputFile << std::left << entry.first << std::string(padding, ' ') << std::setw(countColumnWidth) << countIt->second;
                            for (int line : entry.second) {
                                outputFile << " " << line;
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

int visual_width(const std::string& s) {
    std::regex lithuanian_chars("\xc4\x85|\xc4\x8d|\xc4\x99|\xc4\x97|\xc5\xa1|\xc5\xb3|\xc5\xab|\xc5\xbe|\xc4\xaf|\xc4\x84|\xc4\x8c|\xc4\x98|\xc4\x96|\xc5\xa0|\xc5\xb2|\xc5\xaa|\xc5\xbd|\xc4\xae");
    std::ptrdiff_t num_lithuanian_chars = std::distance(
        std::sregex_iterator(s.begin(), s.end(), lithuanian_chars),
        std::sregex_iterator()
    );
    return s.size() - num_lithuanian_chars;
}