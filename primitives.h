#ifndef PRIMITIVES_H
#define PRIMITIVES_H

enum Dir
{
    up,
    down,
    left,
    right
};



struct GameStatistics
{
    int score;
    int time;

};

enum CalledFrom
{
    MainMenu,
    GameOverMenu
};


#endif // PRIMITIVES_H

