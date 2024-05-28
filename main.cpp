#include "functions.h"

int main() {
    try {
        std::ifstream inputFile("input.txt");
        if (!inputFile) {
            std::cerr << "Klaida atidarant failą." << std::endl;
            return 1;
        }

        std::unordered_map<std::string, int> wordCount;
        std::map<std::string, std::vector<int>> wordLines;
        std::vector<std::string> urls;
        std::string line;
        int lineNumber = 0;
        
        while (std::getline(inputFile, line)) {
            lineNumber++;
            processLine(line, lineNumber, wordCount, wordLines, urls);
        }

        inputFile.close();

        writeOutput(wordCount, wordLines, urls);
    } catch (const std::exception& e) {
        std::cerr << "Įvyko klaida: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Įvyko nežinoma klaida." << std::endl;
        return 1;
    }

    return 0;
}