#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int GetProrityOfItem(char &Item)
{
    int Priority = Item;

    if (Item == toupper(Item))
        return Priority - 64 + 26;

    return Priority - 96;
}

char GetSimilarItemsInRutsack(string &Rutsack)
{
    size_t CompartmentLength = Rutsack.length() / 2;
    string FirstRutsack = Rutsack.substr(0, CompartmentLength);
    string SecondRutsack = Rutsack.substr(CompartmentLength, CompartmentLength);

    for (char FirstItem : FirstRutsack)
    {
        for (char SecondItem : SecondRutsack)
        {
            if (FirstItem == SecondItem)
            {
                return FirstItem;
            }
        }
    }

    return '\0';
}

char GetSimilarItemsInGroup(vector<string> &RutsackList)
{
    string FirstRutsack = RutsackList[0];
    string SecondRutsack = RutsackList[1];
    string ThirdRutsack = RutsackList[2];

    for (char FirstItem : FirstRutsack)
    {
        for (char SecondItem : SecondRutsack)
        {
            for (char ThirdItem : ThirdRutsack)
            {
                if (FirstItem == SecondItem && FirstItem == ThirdItem && SecondItem == ThirdItem)
                {
                    return FirstItem;
                }
            }
        }
    }

    return '\0';
}

int main(int argc, char **argv)
{
    int TotalSum = 0;
    int TotalSumOfGroups = 0;

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
    vector<string> RutsackList;

    while (getline(InputTextFile, Line))
    {
        RutsackList.push_back(Line);
        char SimilarItem = GetSimilarItemsInRutsack(Line);

        TotalSum += GetProrityOfItem(SimilarItem);

        if (RutsackList.size() == 3)
        {
            SimilarItem = GetSimilarItemsInGroup(RutsackList);
            RutsackList.clear();

            TotalSumOfGroups += GetProrityOfItem(SimilarItem);
        }
    }

    InputTextFile.close();

    cout << "The total sum of the priorities of the item types are " << TotalSum << endl;
    cout << "The total sum of the priorities in the groups are " << TotalSumOfGroups << endl;

    return 0;
}