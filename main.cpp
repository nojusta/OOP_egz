#include "functions.h"

int main() {
    std::ifstream in("input.txt");
    if (!in) {
        std::cout << "Nerastas failas\n";
        return 1;
    }

    // Uzkrauna TLDs is failo i set
    std::unordered_set<std::string> tlds = LoadTLDs("tlds.txt");

    // Jei nera TLDs, baigia programa
    if (tlds.empty()) {
        std::cerr << "Error: Jokiu TLD nerasta." << std::endl;
        return 1;
    }

    std::map<std::string, std::vector<int>> zodziai;
    std::unordered_map<std::string, int> wordCount;
    std::vector<std::string> urls;

    Read_File(in, zodziai);
    Counter(zodziai, wordCount);

    in.clear();
    in.seekg(0);

    FindURLs(in, urls, tlds);

    ExtractWordsWithBus(zodziai);

    writeOutput(wordCount, zodziai, urls);

    return 0;
}