#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Util
{
    public:
        Util();
        static string PositionToChessNote(Vector2f position);
        static Vector2f NoteToCoord(char a, char b);
        static void Move(Sprite *pieces, string note);
        static bool IsBlack(int idx);
        static string GetNamePieceEnum(int numberPiece);
        static string GetNamePieceByIdx(int idxPiece);
        static Vector2f CenterPosition(Sprite piece);
    

};

#endif