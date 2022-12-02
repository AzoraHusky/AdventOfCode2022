#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int GetWinScore (string OppenentA, string OppenentB)
{
    if (OppenentA == "A" && OppenentB == "X" || 
        OppenentA == "B" && OppenentB == "Y" || 
        OppenentA == "C" && OppenentB == "Z") return 3;

    if (OppenentA == "A" && OppenentB == "Y" ||
        OppenentA == "B" && OppenentB == "Z" || 
        OppenentA == "C" && OppenentB == "X") return 6;
    else return 0;
}

int GetShapeScore (string Oppenent)
{
    if (Oppenent == "A" || Oppenent == "X") return 1;
    else if (Oppenent == "B" || Oppenent == "Y") return 2;
    else if (Oppenent == "C" || Oppenent == "Z") return 3;

    return 0;
}

string GetNewShape (string OppenentA, string OppenentB)
{
    if (OppenentB == "X")
    {
        if (OppenentA == "A") return "Z";
        else if (OppenentA == "C") return "Y";
        else return "X";
    }
    else if (OppenentB == "Y")
    {
        if (OppenentA == "A") return "X";
        else if (OppenentA == "C") return "Z";
        else return "Y";
    }
    else if (OppenentB == "Z")
    {
        if (OppenentA == "A") return "Y";
        else if (OppenentA == "C") return "X";
        else return "Z";
    }

    return "";
}

int main (int argc, char** argv)
{
    int TotalScore = 0;
    int TotalScoreAlt = 0;

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

    ifstream InputTextFile (argv[1]);
    if (!InputTextFile)
    {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    string Line;

    while (getline (InputTextFile, Line))
    {
        size_t pos = Line.find_last_of(" ");
        string OpponentA = Line.substr(0, pos);
        string OpponentB = Line.substr(pos + 1, 1);

        int WinScore = GetWinScore(OpponentA, OpponentB);
        int ShapeScore = GetShapeScore (OpponentB);

        TotalScore += WinScore + ShapeScore;

        string NewShape = GetNewShape(OpponentA, OpponentB);
        WinScore = GetWinScore(OpponentA, NewShape);
        ShapeScore = GetShapeScore(NewShape);

        TotalScoreAlt += WinScore + ShapeScore;
    }

    InputTextFile.close();

    cout << "You have won a total score of " << TotalScore << endl;
    cout << "For your new strategy you won a total score of " << TotalScoreAlt << endl;
}