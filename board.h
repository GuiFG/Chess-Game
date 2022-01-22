#ifndef BOARD_H
#define BOARD_H 

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int board[8][8] =
    { -1, -2, -3, -4, -5, -3, -2, -1,
    -6, -6, -6, -6, -6, -6, -6, -6,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    6,  6,  6,  6,  6,  6,  6,  6,
    1,  2,  3,  4,  5,  3,  2,  1
    };

class Board
{
    public:
        static void LoadPosition(Sprite *pieces, string position);
        static int** GetBoard();
};

#endif