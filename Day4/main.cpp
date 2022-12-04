#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> GetPairs(string &Pair)
{
    size_t pos = Pair.find_last_of(",");
    string FirstPair = Pair.substr(0, pos);
    string SecondPair = Pair.substr(pos + 1, Pair.length() - pos);

    vector<string> Pairs;
    Pairs.push_back(FirstPair);
    Pairs.push_back(SecondPair);

    return Pairs;
}

vector<int> GetPairList(string &Pair)
{
    size_t pos = Pair.find_last_of("-");
    int FirstNumber = stoi(Pair.substr(0, pos));
    int SecondNumber = stoi(Pair.substr(pos + 1, Pair.length() - pos));

    vector<int> PairList;
    for (int i = FirstNumber; i <= SecondNumber; i++)
        PairList.push_back(i);

    return PairList;
}

int GetPairsContainEachOther(string &Line)
{
    vector<string> Pairs = GetPairs(Line);

    vector<int> FirstPairList = GetPairList(Pairs[0]);
    vector<int> SecondPairList = GetPairList(Pairs[1]);

    int TotalIntersectingSections = 0;
    for (int FirstSection : FirstPairList)
    {
        for (int SecondSection : SecondPairList)
        {
            if (FirstSection == SecondSection)
                TotalIntersectingSections++;
        }
    }

    if (TotalIntersectingSections == FirstPairList.size() || TotalIntersectingSections == SecondPairList.size())
        return 1;

    return 0;
}

int GetSectionsOverlappingEachOther(string &Line)
{
    vector<string> Pairs = GetPairs(Line);

    vector<int> FirstPairList = GetPairList(Pairs[0]);
    vector<int> SecondPairList = GetPairList(Pairs[1]);

    int TotalIntersectingSections = 0;
    for (int FirstSection : FirstPairList)
    {
        for (int SecondSection : SecondPairList)
        {
            if (FirstSection == SecondSection)
                TotalIntersectingSections++;
        }
    }

    if (TotalIntersectingSections > 0) return 1;

    return 0;
}

int main(int argc, char **argv)
{
    int TotalOverlappingPairs = 0;
    int TotalOverlappingSections = 0;

    if (argc > 2)
    {
        cout << "There are too many arguments, only provide the text file" << endl;
        return 0;
    }
    else if (argc == 1)
    {
        cout << "Please provide an argument for the text file" << endl;
        return 0;
    }

    ifstream InputTextFile(argv[1]);
    if (!InputTextFile)
    {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    string Line;

    while (getline(InputTextFile, Line))
    {
        try
        {
            TotalOverlappingPairs += GetPairsContainEachOther(Line);
            TotalOverlappingSections += GetSectionsOverlappingEachOther(Line);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    InputTextFile.close();

    cout << "The total amount of overlapping pairs are " << TotalOverlappingPairs << endl;
    cout << "The total amount of pairs with overlap are " << TotalOverlappingSections << endl;

    return 0;
}