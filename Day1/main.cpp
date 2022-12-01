#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main (int argc, char** argv)
{
    vector<int> CaloryList;
    ifstream InputTextFile;
    int HighestTopThree = 0;

    if (argc > 2)
    {
        cout << "There are too many arguments, please type just the argument for the input text file" << endl;
        return 0;
    }
    else if (argc == 1)
    {
        cout << "Please input a text file as an argument" << endl;
        return 0;
    }

    InputTextFile.open (argv[1]);
    if (!InputTextFile) {
        cout << "Unable to open file!" << endl;
        return 0;
    }

    string x;
    int CaloryTotal = 0;

    while (getline(InputTextFile, x))
    {
        if (x == "")
        {
            CaloryList.push_back (CaloryTotal);
            CaloryTotal = 0;
        }
        else
        {
            CaloryTotal += stoi(x);
        }
    }
    InputTextFile.close();

    sort (CaloryList.begin(), CaloryList.end(), greater<int>());

    HighestTopThree = CaloryList[0] + CaloryList[1] + CaloryList[2];

    cout << "The highest Calories held by an Elf is " << CaloryList[0] << endl;
    cout << "The total of the top three Elves is " << HighestTopThree << endl;
    
    return 0;
}