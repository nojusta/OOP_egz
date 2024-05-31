#include "functions.h"

int main()
{
    std::ifstream in("input.txt");
    if (!in) {
        std::cout << "Nerastas failas\n";
        return 1;
    }

    std::map<std::string, std::vector<int>> zodziai;
    std::unordered_map<std::string, int> wordCount;
    std::vector<std::string> urls;

    Read_File(in, zodziai);
    Counter(zodziai, wordCount);

    in.clear();
    in.seekg(0);

    FindURLs(in, urls);

    writeOutput(wordCount, zodziai, urls);

    return 0;
}
