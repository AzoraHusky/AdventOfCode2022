#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int Columns = 9;
vector<vector<char>> Crates(Columns);

bool IsUpgradedMachine = true; //Change this variable for the upgraded machine or not

vector<int> IntegerExtractor(string &Line)
{
    stringstream StringStream;
    vector<int> FoundIntegers;

    StringStream << Line;

    string Temp;
    int FoundInteger;
    while (!StringStream.eof())
    {
        StringStream >> Temp;

        if (stringstream(Temp) >> FoundInteger)
            FoundIntegers.push_back(FoundInteger);

        Temp = "";
    }

    return FoundIntegers;
}

void MoveCrates(string &Line)
{
    try
    {
        int MoveTotal = IntegerExtractor(Line)[0];
        int FromSource = IntegerExtractor(Line)[1] - 1;
        int ToDestination = IntegerExtractor(Line)[2] - 1;

        for (int MoveCounter = 0; MoveCounter < MoveTotal; MoveCounter++)
        {
            int LastCrate = Crates[FromSource].size() - 1;
            Crates[ToDestination].push_back(Crates[FromSource][LastCrate]);
            Crates[FromSource].pop_back();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void MoveCratesUpgrade(string &Line)
{
    try
    {
        int MoveTotal = IntegerExtractor(Line)[0];
        int FromSource = IntegerExtractor(Line)[1] - 1;
        int ToDestination = IntegerExtractor(Line)[2] - 1;

        for (int MoveCounter = 0; MoveCounter < MoveTotal; MoveCounter++)
        {
            int LastCrate = Crates[FromSource].size() - (MoveTotal - MoveCounter);
            Crates[ToDestination].push_back(Crates[FromSource][LastCrate]);
        }
        for (int i = 0; i < MoveTotal; i++)
            Crates[FromSource].pop_back();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char **argv)
{

    if (argc > 3)
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
    int ColoumnCounter = 0;
    int RowCounter = 0;

    bool IsDoneWithVector = false;

    while (getline(InputTextFile, Line))
    {
        if (Line == "" && !IsDoneWithVector)
        {
            IsDoneWithVector = true;
            for (int i = 0; i < Crates.size(); i++)
                reverse(Crates[i].begin(), Crates[i].end());
        }
        if (!IsDoneWithVector)
        {
            for (int i = 1; i < Line.length(); i += 4)
            {
                if (Line[i] != ' ')
                    Crates[ColoumnCounter].push_back(Line[i]);
                ColoumnCounter++;
            }
            ColoumnCounter = 0;
        }
        else
        {
            if (IsUpgradedMachine)
            {
                if (Line != "")
                {
                    MoveCratesUpgrade(Line);
                }
            }
            else
            {
                if (Line != "")
                {
                    MoveCrates(Line);
                }
            }
        }
    }

    InputTextFile.close();

    for (int i = 0; i < Crates.size(); i++)
    {
        for (int j = 0; j < Crates[i].size(); j++)
        {
            cout << Crates[i][j] << " ";
        }
        cout << endl;
    }

    cout << "The combination of the top crates are ";
    for (int i = 0; i < Crates.size(); i++)
    {
        cout << Crates[i][Crates[i].size() - 1];
    }
    cout << endl;

    return 0;
}