#include "functions.h"

int main()
{
    std::ifstream in("input.txt");
    if (!in) {
        std::cout << "Nerastas failas\n";
        return 1;
    }

    std::set<std::string> urls;
    std::map<std::string, std::vector<int>> zodziai;

    Read_File(in, zodziai);
    Counter(zodziai);
    in.clear();
    in.seekg(0);

    WriteCrossReference(zodziai);
    FindURLs(in, urls);

    return 0;
}