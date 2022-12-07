#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool IsCharactersDuplicated(string &Marker)
{
    for (int i = 0; i < Marker.size() - 1; i++)
    {
        for (int j = i + 1; j < Marker.size(); j++)
        {
            if (Marker[i] == Marker[j]) return true;
        }
    }

    return false;
}

int GetFirstMarker(string &Line)
{
    int MarkerLength = 14;
    int Counter;

    for (Counter = 0; Counter < Line.size() - MarkerLength; Counter++)
    {
        string Marker = Line.substr(Counter, MarkerLength);
        if (!IsCharactersDuplicated(Marker)) break;
    }

    return Counter + MarkerLength;
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

    getline(InputTextFile, Line);

    InputTextFile.close();

    int FirstMarkerPosition = GetFirstMarker(Line);

    cout << "The first marker in the string is " << FirstMarkerPosition << endl;

    return 0;
}