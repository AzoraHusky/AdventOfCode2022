#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char** argv)
{
    string ElfList;
    vector<int> CaloryList;
    ifstream InputTextFile;
    int HighestCalory = 0;

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
    int CaloryTotal;

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

    for (int i : CaloryList)
    {
        if (HighestCalory < i) HighestCalory = i;
    }

    cout << "The highest Calory held by an Elf is " << HighestCalory << endl;
    
    return 0;
}