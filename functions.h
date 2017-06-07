#include <string>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void clear();
unsigned int loadHighScore();
void menu(unsigned short int &GameOptions, const unsigned int &Highscore);
void startGame(unsigned int &Highscore);
void beginBallAndCups(const std::string (&Cups)[5], const std::string (&Ball)[4], int &WhichCup);
void leftCupToMiddleCup(const unsigned short int &CupsMovementSpeed);
void leftCupToRightCup(const unsigned short int &CupsMovementSpeed);
void middleCupToLeftCup(const unsigned short int &CupsMovementSpeed);
void middleCupToRightCup(const unsigned short int &CupsMovementSpeed);
void rightCupToMiddleCup(const unsigned short int &CupsMovementSpeed);
void rightCupToLeftCup(const unsigned short int &CupsMovementSpeed);
#endif
