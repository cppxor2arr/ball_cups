#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include "functions.h"
void clear()
{
    system("clear");
}
unsigned int loadHighScore()
{
    std::string Temp;
    unsigned int Highscore;
    std::ifstream File ("Highscore.txt");
    if ((File.is_open()))
    {
        File >> Temp;
        File.close();
        std::istringstream Convert(Temp);
        Convert >> Highscore;
    }
    else
    {
        File.close();
        std::ofstream File;
        File.open("Highscore.txt");
        File << 0;
        File.close();
        std::ifstream File2 ("Highscore.txt");
        File2 >> Temp;
        File2.close();
        std::istringstream Convert(Temp);
        Convert >> Highscore;
    }
    return Highscore;
}
void menu(unsigned short int &GameOptions, const unsigned int &Highscore)
{
    clear();
    std::cout << "Ball & Cups v1.0\n\n";
    std::cout << "Highscore: " << Highscore << '\n' << '\n';
    std::cout << "Options:\n**********\n";
    std::cout << "1. Play\n2. About this game\n3. Quit\n\n> ";
    std::cin >> GameOptions;
    if ((GameOptions != 1) && (GameOptions != 2) && (GameOptions != 3))
    {
        clear();
        std::cin.clear();
        std::cin.ignore(1000000, '\n');
        menu(GameOptions, Highscore);
    }
    if (GameOptions == 2)
    {
        clear();
        std::cout << "  This game is where cups move around with a ball in one of them\n"
                     "and after you see the cups move you guess which cup it is in with\n"
                     "the numbers 1, 2, & 3.\n\n"
                     "  When you fail to guess right then it's Game Over. But if you keep\n"
                     "guessing right then the cups will start to move faster.\n\n\n"
                     "               ENJOY! (Press any key to continue...)" << std::endl;
        std::cin.ignore(); std::cin.get();
        menu(GameOptions, Highscore);
    }
    if (GameOptions == 3)
    {
        clear();
        std::cout << "Exiting...\n\nExiting...\n\nExiting...\n" << std::endl;;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));;
    }
}
void startGame(unsigned int &Highscore)
{
    clear();
    for (int x{3}; x > -1; x--)
    {
        std::cout << "Starting game in... " << x << '\n' << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        clear();
    }
    std::string Cups[5]
    {
        "[][][][]    [][][][]    [][][][]\n",
        "[]    []    []    []    []    []\n",
        "[]    []    []    []    []    []\n",
        "[]    []    []    []    []    []\n",
        "********    ********    ********\n\n"
    };
    std::string Ball[4]
    {
        " ####\n",
        "#    #\n",
        "#    #\n",
        " ####\n"
    };
    int WhichCup{0}, LeftCup{1}, MiddleCup{2}, RightCup{3};
    beginBallAndCups(Cups, Ball, WhichCup);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    clear();
    int GuessCup{0};
    unsigned short int Difficulty{1};
    srand(time(NULL));
    int RandomCup{rand() % 6};
    unsigned short int TempHighscore{0};
    unsigned short int CupsMovementSpeed{60};
    goto start;
    do
    {
        for (int x{0}; x < Difficulty; x++)
        {
            RandomCup = rand() % 6;
            if (WhichCup == LeftCup)
            {
                switch (RandomCup)
                {
                case 0:
                    leftCupToMiddleCup(CupsMovementSpeed);
                    WhichCup = MiddleCup;
                    break;
                case 1:
                    leftCupToRightCup(CupsMovementSpeed);
                    WhichCup = RightCup;
                    break;
                case 2:
                    middleCupToLeftCup(CupsMovementSpeed);
                    WhichCup = MiddleCup;
                    break;
                case 3:
                    middleCupToRightCup(CupsMovementSpeed);
                    break;
                case 4:
                    rightCupToMiddleCup(CupsMovementSpeed);
                    break;
                case 5:
                    rightCupToLeftCup(CupsMovementSpeed);
                    WhichCup = RightCup;
                    break;
                }
                clear();
                continue;
            }
            if (WhichCup == MiddleCup)
            {
                switch (RandomCup)
                {
                case 0:
                    leftCupToMiddleCup(CupsMovementSpeed);
                    WhichCup = LeftCup;
                    break;
                case 1:
                    leftCupToRightCup(CupsMovementSpeed);
                    break;
                case 2:
                    middleCupToLeftCup(CupsMovementSpeed);
                    WhichCup = LeftCup;
                    break;
                case 3:
                    middleCupToRightCup(CupsMovementSpeed);
                    WhichCup = RightCup;
                    break;
                case 4:
                    rightCupToMiddleCup(CupsMovementSpeed);
                    WhichCup = RightCup;
                    break;
                case 5:
                    rightCupToLeftCup(CupsMovementSpeed);
                    break;
                }
                clear();
                continue;
            }
            if (WhichCup == RightCup)
            {
                switch (RandomCup)
                {
                case 0:
                    leftCupToMiddleCup(CupsMovementSpeed);
                    break;
                case 1:
                    leftCupToRightCup(CupsMovementSpeed);
                    WhichCup = LeftCup;
                    break;
                case 2:
                    middleCupToLeftCup(CupsMovementSpeed);
                    break;
                case 3:
                    middleCupToRightCup(CupsMovementSpeed);
                    WhichCup = MiddleCup;
                    break;
                case 4:
                    rightCupToMiddleCup(CupsMovementSpeed);
                    WhichCup = MiddleCup;
                    break;
                case 5:
                    rightCupToLeftCup(CupsMovementSpeed);
                    WhichCup = LeftCup;
                    break;
                }
                clear();
                continue;
            }
        }
start:
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Which cup is the ball in (1, 2, or 3): ";
        std::cin >> GuessCup;
        while ((GuessCup != 1) && (GuessCup != 2) && (GuessCup != 3))
        {
            clear();
            std::cout << "Enter 1, 2, or 3: ";
            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            std::cin >> GuessCup;
        }
        if (GuessCup == WhichCup)
        {
            Difficulty++;
            TempHighscore += 5;
            if (TempHighscore > Highscore)
            {
                Highscore = TempHighscore;
                std::ofstream File ("Highscore.txt");
                File << Highscore;
                File.close();
            }
            if (CupsMovementSpeed > 0)
            {
                CupsMovementSpeed -= 5;
            }
        }
        clear();
    }
    while (GuessCup == WhichCup);
    clear();
    std::cout << "Your score was " << TempHighscore << "!\n" << std::endl << "Your highscore is " << Highscore << "!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    clear();
}
void beginBallAndCups(const std::string (&Cups)[5], const std::string (&Ball)[4], int &WhichCup)
{
    srand(time(NULL));
    int ChooseCup{rand() % 3 + 1}, NoWhiteSpace{0};
    WhichCup = ChooseCup;
    switch (ChooseCup)
    {
    case 1:
        NoWhiteSpace = 2;
        break;
    case 2:
        NoWhiteSpace = 14;
        break;
    case 3:
        NoWhiteSpace = 26;
        break;
    }
    for (unsigned short int x{0}; x < NoWhiteSpace; x++)
    {
        for (unsigned short int i{0}; i < 5; i++)
        {
            std::cout << Cups[i];
        }
        for (int i{0}; i < 4; i++)
        {
            for (unsigned short int n{0}; n < x; n++)
            {
                std::cout << " ";
            }
            std::cout << Ball[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        if (x < (NoWhiteSpace - 1))
        {
            clear();
        }
    }
}
/********************************************************************************/
/********************************************************************************/
void leftCupToMiddleCup(const unsigned short int &CupsMovementSpeed)
{
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "           [][][][]     [][][][]\n"
                 "           []    []     []    []\n"
                 "           []    []     []    []\n"
                 "           []    []     []    []\n"
                 "           ********     ********\n"
                 "                                \n"
                 " [][][][]                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " ********                       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "          [][][][]      [][][][]\n"
                 "          []    []      []    []\n"
                 "          []    []      []    []\n"
                 "          []    []      []    []\n"
                 "          ********      ********\n"
                 "                                \n"
                 "  [][][][]                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  ********                      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "         [][][][]       [][][][]\n"
                 "         []    []       []    []\n"
                 "         []    []       []    []\n"
                 "         []    []       []    []\n"
                 "         ********       ********\n"
                 "                                \n"
                 "   [][][][]                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   ********                     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "        [][][][]        [][][][]\n"
                 "        []    []        []    []\n"
                 "        []    []        []    []\n"
                 "        []    []        []    []\n"
                 "        ********        ********\n"
                 "                                \n"
                 "    [][][][]                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    ********                    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "       [][][][]         [][][][]\n"
                 "       []    []         []    []\n"
                 "       []    []         []    []\n"
                 "       []    []         []    []\n"
                 "       ********         ********\n"
                 "                                \n"
                 "     [][][][]                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     ********                   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "      [][][][]          [][][][]\n"
                 "      []    []          []    []\n"
                 "      []    []          []    []\n"
                 "      []    []          []    []\n"
                 "      ********          ********\n"
                 "                                \n"
                 "      [][][][]                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      ********                  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "     [][][][]           [][][][]\n"
                 "     []    []           []    []\n"
                 "     []    []           []    []\n"
                 "     []    []           []    []\n"
                 "     ********           ********\n"
                 "                                \n"
                 "       [][][][]                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       ********                 \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "    [][][][]            [][][][]\n"
                 "    []    []            []    []\n"
                 "    []    []            []    []\n"
                 "    []    []            []    []\n"
                 "    ********            ********\n"
                 "                                \n"
                 "        [][][][]                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        ********                \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "   [][][][]             [][][][]\n"
                 "   []    []             []    []\n"
                 "   []    []             []    []\n"
                 "   []    []             []    []\n"
                 "   ********             ********\n"
                 "                                \n"
                 "         [][][][]               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         ********               \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "  [][][][]              [][][][]\n"
                 "  []    []              []    []\n"
                 "  []    []              []    []\n"
                 "  []    []              []    []\n"
                 "  ********              ********\n"
                 "                                \n"
                 "          [][][][]              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          ********              \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << " [][][][]               [][][][]\n"
                 " []    []               []    []\n"
                 " []    []               []    []\n"
                 " []    []               []    []\n"
                 " ********               ********\n"
                 "                                \n"
                 "           [][][][]             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           ********             \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********    [][][][]    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
}
/********************************************************************************/
void leftCupToRightCup(const unsigned short int &CupsMovementSpeed)
{
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "[][][][]    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "[][][][]    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "[][][][]    []    []    [][][][]\n"
                 "[]    []    ********    []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "[][][][]    ********    [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 " [][][][]                       \n"
                 " []    []               [][][][]\n"
                 " []    []               []    []\n"
                 " []    []               []    []\n"
                 " ********               []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "  [][][][]                      \n"
                 "  []    []                      \n"
                 "  []    []              [][][][]\n"
                 "  []    []              []    []\n"
                 "  ********              []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "   [][][][]                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   []    []             [][][][]\n"
                 "   ********             []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "    [][][][]                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    ********            [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "     [][][][]                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     ********                   \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "      [][][][]                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      ********                  \n"
                 "                                \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "       [][][][]                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       ********                 \n"
                 "                                \n"
                 "                       [][][][] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       ******** \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "        [][][][]                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        ********                \n"
                 "                                \n"
                 "                      [][][][]  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      ********  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "         [][][][]               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         ********               \n"
                 "                                \n"
                 "                     [][][][]   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     ********   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "          [][][][]              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          ********              \n"
                 "                                \n"
                 "                    [][][][]    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    ********    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "           [][][][]             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           ********             \n"
                 "                                \n"
                 "                   [][][][]     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   ********     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                  [][][][]      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  ********      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "             [][][][]           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             ********           \n"
                 "                                \n"
                 "                 [][][][]       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 ********       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "              [][][][]          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              ********          \n"
                 "                                \n"
                 "                [][][][]        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                ********        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "               [][][][]         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               ********         \n"
                 "                                \n"
                 "               [][][][]         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               ********         \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                [][][][]        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                ********        \n"
                 "                                \n"
                 "              [][][][]          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              ********          \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                 [][][][]       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 ********       \n"
                 "                                \n"
                 "             [][][][]           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             ********           \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                  [][][][]      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  ********      \n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                   [][][][]     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   ********     \n"
                 "                                \n"
                 "           [][][][]             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           ********             \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                    [][][][]    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    ********    \n"
                 "                                \n"
                 "          [][][][]              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          ********              \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                     [][][][]   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     ********   \n"
                 "                                \n"
                 "         [][][][]               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         ********               \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                      [][][][]  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      ********  \n"
                 "                                \n"
                 "        [][][][]                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        ********                \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                       [][][][] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       ******** \n"
                 "                                \n"
                 "       [][][][]                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       ********                 \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "      [][][][]                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      ********                  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "     [][][][]                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     ********                   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********    [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "    [][][][]                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    ********                    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []    [][][][]\n"
                 "            ********    []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "   [][][][]                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   ********                     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []    [][][][]\n"
                 "            []    []    []    []\n"
                 "            ********    []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "  [][][][]                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  ********                      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 " [][][][]                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " ********                       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
}
/********************************************************************************/
void middleCupToLeftCup(const unsigned short int &CupsMovementSpeed)
{
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********    [][][][]    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << " [][][][]               [][][][]\n"
                 " []    []               []    []\n"
                 " []    []               []    []\n"
                 " []    []               []    []\n"
                 " ********               ********\n"
                 "                                \n"
                 "           [][][][]             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           ********             \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "  [][][][]              [][][][]\n"
                 "  []    []              []    []\n"
                 "  []    []              []    []\n"
                 "  []    []              []    []\n"
                 "  ********              ********\n"
                 "                                \n"
                 "          [][][][]              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          ********              \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "   [][][][]             [][][][]\n"
                 "   []    []             []    []\n"
                 "   []    []             []    []\n"
                 "   []    []             []    []\n"
                 "   ********             ********\n"
                 "                                \n"
                 "         [][][][]               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         ********               \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "    [][][][]            [][][][]\n"
                 "    []    []            []    []\n"
                 "    []    []            []    []\n"
                 "    []    []            []    []\n"
                 "    ********            ********\n"
                 "                                \n"
                 "        [][][][]                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        ********                \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "     [][][][]           [][][][]\n"
                 "     []    []           []    []\n"
                 "     []    []           []    []\n"
                 "     []    []           []    []\n"
                 "     ********           ********\n"
                 "                                \n"
                 "       [][][][]                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       ********                 \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "      [][][][]          [][][][]\n"
                 "      []    []          []    []\n"
                 "      []    []          []    []\n"
                 "      []    []          []    []\n"
                 "      ********          ********\n"
                 "                                \n"
                 "      [][][][]                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      ********                  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "       [][][][]         [][][][]\n"
                 "       []    []         []    []\n"
                 "       []    []         []    []\n"
                 "       []    []         []    []\n"
                 "       ********         ********\n"
                 "                                \n"
                 "     [][][][]                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     ********                   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "        [][][][]        [][][][]\n"
                 "        []    []        []    []\n"
                 "        []    []        []    []\n"
                 "        []    []        []    []\n"
                 "        ********        ********\n"
                 "                                \n"
                 "    [][][][]                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    ********                    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "         [][][][]       [][][][]\n"
                 "         []    []       []    []\n"
                 "         []    []       []    []\n"
                 "         []    []       []    []\n"
                 "         ********       ********\n"
                 "                                \n"
                 "   [][][][]                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   ********                     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "          [][][][]      [][][][]\n"
                 "          []    []      []    []\n"
                 "          []    []      []    []\n"
                 "          []    []      []    []\n"
                 "          ********      ********\n"
                 "                                \n"
                 "  [][][][]                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  ********                      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "           [][][][]     [][][][]\n"
                 "           []    []     []    []\n"
                 "           []    []     []    []\n"
                 "           []    []     []    []\n"
                 "           ********     ********\n"
                 "                                \n"
                 " [][][][]                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " ********                       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
}
/********************************************************************************/
void middleCupToRightCup(const unsigned short int &CupsMovementSpeed)
{
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********    [][][][]    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]               [][][][] \n"
                 "[]    []               []    [] \n"
                 "[]    []               []    [] \n"
                 "[]    []               []    [] \n"
                 "********               ******** \n"
                 "                                \n"
                 "             [][][][]           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             ********           \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]              [][][][]  \n"
                 "[]    []              []    []  \n"
                 "[]    []              []    []  \n"
                 "[]    []              []    []  \n"
                 "********              ********  \n"
                 "                                \n"
                 "              [][][][]          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              ********          \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]             [][][][]   \n"
                 "[]    []             []    []   \n"
                 "[]    []             []    []   \n"
                 "[]    []             []    []   \n"
                 "********             ********   \n"
                 "                                \n"
                 "               [][][][]         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               ********         \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]            [][][][]    \n"
                 "[]    []            []    []    \n"
                 "[]    []            []    []    \n"
                 "[]    []            []    []    \n"
                 "********            ********    \n"
                 "                                \n"
                 "                [][][][]        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                ********        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]           [][][][]     \n"
                 "[]    []           []    []     \n"
                 "[]    []           []    []     \n"
                 "[]    []           []    []     \n"
                 "********           ********     \n"
                 "                                \n"
                 "                 [][][][]       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 ********       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]          [][][][]      \n"
                 "[]    []          []    []      \n"
                 "[]    []          []    []      \n"
                 "[]    []          []    []      \n"
                 "********          ********      \n"
                 "                                \n"
                 "                  [][][][]      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  ********      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]         [][][][]       \n"
                 "[]    []         []    []       \n"
                 "[]    []         []    []       \n"
                 "[]    []         []    []       \n"
                 "********         ********       \n"
                 "                                \n"
                 "                   [][][][]     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   ********     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]        [][][][]        \n"
                 "[]    []        []    []        \n"
                 "[]    []        []    []        \n"
                 "[]    []        []    []        \n"
                 "********        ********        \n"
                 "                                \n"
                 "                    [][][][]    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    ********    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]       [][][][]         \n"
                 "[]    []       []    []         \n"
                 "[]    []       []    []         \n"
                 "[]    []       []    []         \n"
                 "********       ********         \n"
                 "                                \n"
                 "                     [][][][]   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     ********   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]      [][][][]          \n"
                 "[]    []      []    []          \n"
                 "[]    []      []    []          \n"
                 "[]    []      []    []          \n"
                 "********      ********          \n"
                 "                                \n"
                 "                      [][][][]  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      ********  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]     [][][][]           \n"
                 "[]    []     []    []           \n"
                 "[]    []     []    []           \n"
                 "[]    []     []    []           \n"
                 "********     ********           \n"
                 "                                \n"
                 "                       [][][][] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       ******** \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "********    ********            \n"
                 "                                \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "********    ********            \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "********    ********    [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []    [][][][]\n"
                 "********    ********    []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
}
/********************************************************************************/
void rightCupToMiddleCup(const unsigned short int &CupsMovementSpeed)
{
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []    [][][][]\n"
                 "********    ********    []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "********    ********    [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "********    ********            \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "[]    []    []    []            \n"
                 "********    ********            \n"
                 "                                \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]     [][][][]           \n"
                 "[]    []     []    []           \n"
                 "[]    []     []    []           \n"
                 "[]    []     []    []           \n"
                 "********     ********           \n"
                 "                                \n"
                 "                       [][][][] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       ******** \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]      [][][][]          \n"
                 "[]    []      []    []          \n"
                 "[]    []      []    []          \n"
                 "[]    []      []    []          \n"
                 "********      ********          \n"
                 "                                \n"
                 "                      [][][][]  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      ********  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]       [][][][]         \n"
                 "[]    []       []    []         \n"
                 "[]    []       []    []         \n"
                 "[]    []       []    []         \n"
                 "********       ********         \n"
                 "                                \n"
                 "                     [][][][]   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     ********   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]        [][][][]        \n"
                 "[]    []        []    []        \n"
                 "[]    []        []    []        \n"
                 "[]    []        []    []        \n"
                 "********        ********        \n"
                 "                                \n"
                 "                    [][][][]    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    ********    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]         [][][][]       \n"
                 "[]    []         []    []       \n"
                 "[]    []         []    []       \n"
                 "[]    []         []    []       \n"
                 "********         ********       \n"
                 "                                \n"
                 "                   [][][][]     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   ********     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]          [][][][]      \n"
                 "[]    []          []    []      \n"
                 "[]    []          []    []      \n"
                 "[]    []          []    []      \n"
                 "********          ********      \n"
                 "                                \n"
                 "                  [][][][]      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  ********      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]           [][][][]     \n"
                 "[]    []           []    []     \n"
                 "[]    []           []    []     \n"
                 "[]    []           []    []     \n"
                 "********           ********     \n"
                 "                                \n"
                 "                 [][][][]       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 ********       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]            [][][][]    \n"
                 "[]    []            []    []    \n"
                 "[]    []            []    []    \n"
                 "[]    []            []    []    \n"
                 "********            ********    \n"
                 "                                \n"
                 "                [][][][]        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                ********        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]             [][][][]   \n"
                 "[]    []             []    []   \n"
                 "[]    []             []    []   \n"
                 "[]    []             []    []   \n"
                 "********             ********   \n"
                 "                                \n"
                 "               [][][][]         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               ********         \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]              [][][][]  \n"
                 "[]    []              []    []  \n"
                 "[]    []              []    []  \n"
                 "[]    []              []    []  \n"
                 "********              ********  \n"
                 "                                \n"
                 "              [][][][]          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              ********          \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]               [][][][] \n"
                 "[]    []               []    [] \n"
                 "[]    []               []    [] \n"
                 "[]    []               []    [] \n"
                 "********               ******** \n"
                 "                                \n"
                 "             [][][][]           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             ********           \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********    [][][][]    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]                [][][][]\n"
                 "[]    []    [][][][]    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    []    []    ********\n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
}
/********************************************************************************/
void rightCupToLeftCup(const unsigned short int &CupsMovementSpeed)
{
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "[][][][]    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "[][][][]    []    []    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "[][][][]    []    []    [][][][]\n"
                 "[]    []    ********    []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "[][][][]    ********    [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "[][][][]                [][][][]\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "[]    []                []    []\n"
                 "********                ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 " [][][][]                       \n"
                 " []    []               [][][][]\n"
                 " []    []               []    []\n"
                 " []    []               []    []\n"
                 " ********               []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "  [][][][]                      \n"
                 "  []    []                      \n"
                 "  []    []              [][][][]\n"
                 "  []    []              []    []\n"
                 "  ********              []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "   [][][][]                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   []    []             [][][][]\n"
                 "   ********             []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "    [][][][]                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    ********            [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "     [][][][]                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     ********                   \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "      [][][][]                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      ********                  \n"
                 "                                \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "       [][][][]                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       ********                 \n"
                 "                                \n"
                 "                       [][][][] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       ******** \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "        [][][][]                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        ********                \n"
                 "                                \n"
                 "                      [][][][]  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      ********  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "         [][][][]               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         ********               \n"
                 "                                \n"
                 "                     [][][][]   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     ********   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "          [][][][]              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          ********              \n"
                 "                                \n"
                 "                    [][][][]    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    ********    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "           [][][][]             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           ********             \n"
                 "                                \n"
                 "                   [][][][]     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   ********     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                  [][][][]      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  ********      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "             [][][][]           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             ********           \n"
                 "                                \n"
                 "                 [][][][]       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 ********       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "              [][][][]          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              ********          \n"
                 "                                \n"
                 "                [][][][]        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                ********        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "               [][][][]         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               ********         \n"
                 "                                \n"
                 "               [][][][]         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               []    []         \n"
                 "               ********         \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                [][][][]        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                []    []        \n"
                 "                ********        \n"
                 "                                \n"
                 "              [][][][]          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              []    []          \n"
                 "              ********          \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                 [][][][]       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 []    []       \n"
                 "                 ********       \n"
                 "                                \n"
                 "             [][][][]           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             []    []           \n"
                 "             ********           \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                  [][][][]      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  []    []      \n"
                 "                  ********      \n"
                 "                                \n"
                 "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                   [][][][]     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   []    []     \n"
                 "                   ********     \n"
                 "                                \n"
                 "           [][][][]             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           []    []             \n"
                 "           ********             \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                    [][][][]    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    []    []    \n"
                 "                    ********    \n"
                 "                                \n"
                 "          [][][][]              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          []    []              \n"
                 "          ********              \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                     [][][][]   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     []    []   \n"
                 "                     ********   \n"
                 "                                \n"
                 "         [][][][]               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         []    []               \n"
                 "         ********               \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                      [][][][]  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      []    []  \n"
                 "                      ********  \n"
                 "                                \n"
                 "        [][][][]                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        []    []                \n"
                 "        ********                \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                       [][][][] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       []    [] \n"
                 "                       ******** \n"
                 "                                \n"
                 "       [][][][]                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       []    []                 \n"
                 "       ********                 \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                                \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "      [][][][]                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      []    []                  \n"
                 "      ********                  \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********            \n"
                 "                        [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "     [][][][]                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     []    []                   \n"
                 "     ********                   \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            ********    [][][][]\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "    [][][][]                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    []    []                    \n"
                 "    ********                    \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []            \n"
                 "            []    []    [][][][]\n"
                 "            ********    []    []\n"
                 "                        []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "   [][][][]                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   []    []                     \n"
                 "   ********                     \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []            \n"
                 "            []    []    [][][][]\n"
                 "            []    []    []    []\n"
                 "            ********    []    []\n"
                 "                        []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "  [][][][]                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  []    []                      \n"
                 "  ********                      \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]            \n"
                 "            []    []    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    []    []\n"
                 "                        ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 " [][][][]                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " []    []                       \n"
                 " ********                       \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "                                \n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            ********    ********\n"
                 "[][][][]                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "            []    []    []    []\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "[]    []                        \n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "            [][][][]    [][][][]\n"
                 "[][][][]    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    ********    ********\n"
                 "********                        \n";
    std::this_thread::sleep_for(std::chrono::milliseconds(CupsMovementSpeed));
    clear();
    std::cout << "[][][][]    [][][][]    [][][][]\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "[]    []    []    []    []    []\n"
                 "********    ********    ********\n";
}
