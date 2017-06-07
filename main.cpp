#include "functions.h"
#include <cstdlib>
int main()
{
    system("title BallAndCups");
    restart:
    unsigned short int *GameOptions{new unsigned short int};
    unsigned int Highscore = loadHighScore();
    menu(*GameOptions, Highscore);
    if (*GameOptions == 3)
    {
        return 0;
    }
    delete GameOptions;
    startGame(Highscore);
    goto restart;
    return 0;
}
