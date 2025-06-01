#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

string logo = R"( .----------------.  .----------------.  .----------------.  .----------------.                      
| .--------------. || .--------------. || .--------------. || .--------------. |                     
| | _____  _____ | || |     ____     | || |  _______     | || |  ________    | |                     
| ||_   _||_   _|| || |   .'    `.   | || | |_   __ \    | || | |_   ___ `.  | |                     
| |  | | /\ | |  | || |  /  .--.  \  | || |   | |__) |   | || |   | |   `. \ | |                     
| |  | |/  \| |  | || |  | |    | |  | || |   |  __ /    | || |   | |    | | | |                     
| |  |   /\   |  | || |  \  `--'  /  | || |  _| |  \ \_  | || |  _| |___.' / | |                     
| |  |__/  \__|  | || |   `.____.'   | || | |____| |___| | || | |________.'  | |                     
| |              | || |              | || |              | || |              | |                     
| '--------------' || '--------------' || '--------------' || '--------------' |                     
 '----------------'  '----------------'  '----------------'  '----------------'                      
 .----------------.  .----------------.  .----------------.  .----------------.                      
| .--------------. || .--------------. || .--------------. || .--------------. |                     
| |    ______    | || |      __      | || | ____    ____ | || |  _________   | |                     
| |  .' ___  |   | || |     /  \     | || ||_   \  /   _|| || | |_   ___  |  | |                     
| | / .'   \_|   | || |    / /\ \    | || |  |   \/   |  | || |   | |_  \_|  | |                     
| | | |    ____  | || |   / ____ \   | || |  | |\  /| |  | || |   |  _|  _   | |                     
| | \ `.___]  _| | || | _/ /    \ \_ | || | _| |_\/_| |_ | || |  _| |___/ |  | |                     
| |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |                     
| |              | || |              | || |              | || |              | |                     
| '--------------' || '--------------' || '--------------' || '--------------' |                     
 '----------------'  '----------------'  '----------------'  '----------------'                      
 .----------------.  .----------------.  .----------------.  .-----------------. .----------------.  
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
| |  _________   | || |  ____  ____  | || |     _____    | || | ____  _____  | || |    ______    | | 
| | |  _   _  |  | || | |_   ||   _| | || |    |_   _|   | || ||_   \|_   _| | || |  .' ___  |   | |
| | |_/ | | \_|  | || |   | |__| |   | || |      | |     | || |  |   \ | |   | || | / .'   \_|   | |
| |     | |      | || |   |  __  |   | || |      | |     | || |  | |\ \| |   | || | | |    ____  | |
| |    _| |_     | || |  _| |  | |_  | || |     _| |_    | || | _| |_\   |_  | || | \ `.___]  _| | |
| |   |_____|    | || | |____||____| | || |    |_____|   | || ||_____|\____| | || |  `._____.'   | |
| |              | || |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
'----------------'  '----------------'  '----------------'  '----------------'  '----------------' )";

map<char, int> allCharacters = {
    {'a', 1},
    {'b', 3},
    {'c', 3},
    {'d', 2},
    {'e', 1},
    {'f', 4},
    {'g', 2},
    {'h', 4},
    {'i', 1},
    {'j', 8},
    {'k', 5},
    {'l', 1},
    {'m', 3},
    {'n', 1},
    {'o', 1},
    {'p', 3},
    {'q', 10},
    {'r', 1},
    {'s', 1},
    {'t', 1},
    {'u', 1},
    {'v', 4},
    {'w', 4},
    {'x', 8},
    {'y', 4},
    {'z', 10}};

char yourLetters[4][4];

const char LETTERS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                        't', 'u', 'v', 'w', 'x', 'y', 'z'};

void createYourLetters()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            yourLetters[i][j] = LETTERS[rand() % 26];
        }
    }
}

void printYourLetters(int localPoints)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << yourLetters[i][j] << " (" << allCharacters[yourLetters[i][j]] << ") | ";
        }
        if (i == 0)
        {
            cout << "    Points: " << localPoints;
        }
        cout << endl;
        cout << "-------------------------------- |" << endl;
    }
}

bool wordInDictionary(string word)
{
    ifstream inputFile("words");
    if (!inputFile.is_open())
    {
        cerr << "Error opening dictionary file." << endl;
        return false;
    }

    string line;
    while (std::getline(inputFile, line))
    { // TODO: make this more efficient
        if (line == word)
        {
            inputFile.close();
            return true;
        }
    }
    inputFile.close();
    return false;
}

int points = 0;

int main()
{
    cout << logo << endl;
    srand(time(0));
    createYourLetters();

    while (true)
    {
        printYourLetters(points);

        bool legalWord = false;
        while (!legalWord)
        {
            cout << "Type your word: ";
            string word;
            cin >> word;
            for (char &c : word)
            { // Convert to lowercase for consistency and just in case stuff is case sensitive
                // Using static_cast<unsigned char> to avoid undefined behavior for negative values i guess according to ai at least
                c = tolower(static_cast<unsigned char>(c));
            }
            if (word.length() > 16 || word.length() < 2)
            {
                cout << "Invalid word." << endl << endl;
                continue;
            }
            else
            {
                char newLetters[4][4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        newLetters[i][j] = yourLetters[i][j];
                    }
                }

                int newPoints = 0;
                bool allFound = true;
                for (int i = 0; i < word.length(); i++)
                {
                    bool foundCharacter = false;
                    for (int j = 0; j < 4 && !foundCharacter; j++)
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            if (word[i] == newLetters[j][k])
                            {
                                newLetters[j][k] = ' '; // Mark as used
                                foundCharacter = true;
                                newPoints += allCharacters[word[i]];
                                break; // break out of k-loop
                            }
                        }
                    }
                    if (!foundCharacter)
                    {
                        allFound = false;
                        break;
                    }
                }
                if (!allFound)
                {
                    cout << "Invalid word." << endl << endl;
                    legalWord = false;
                    break;
                }

                if (wordInDictionary(word))
                {
                    legalWord = true;
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (newLetters[i][j] == ' ')
                            {
                                newLetters[i][j] = LETTERS[rand() % 26]; // Reset used letters
                            }
                            yourLetters[i][j] = newLetters[i][j];
                        }
                    }

                    if (word.length() >= 5)
                    {
                        newPoints += 2;
                    }
                    if (word.length() >= 6)
                    {
                        newPoints += 3;
                    }
                    if (word.length() >= 7)
                    {
                        newPoints += 5;
                    }
                    if (word.length() >= 8)
                    {
                        newPoints += 5;
                    }
                    if (word.length() >= 9)
                    {
                        newPoints += 5;
                    }
                    if (word.length() >= 10)
                    {
                        newPoints += 10;
                    }
                    if (word.length() >= 11)
                    {
                        newPoints += 10;
                    }
                    if (word.length() >= 12)
                    {
                        newPoints += 10;
                    }
                    if (word.length() >= 13)
                    {
                        newPoints += 10;
                    }
                    if (word.length() >= 14)
                    {
                        newPoints += 10;
                    }
                    if (word.length() >= 15)
                    {
                        newPoints += 10;
                    }
                    if (word.length() >= 16)
                    {
                        newPoints += 10;
                    }

                    points += newPoints;

                    cout << "You scored " << points << " points!" << endl << endl;
                    break;
                }
                else
                {
                    cout << "Invalid word." << endl << endl;
                    legalWord = false;
                    break;
                }
            }
        }
    }

    return 0;
}