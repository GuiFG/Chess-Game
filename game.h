#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "board.h"
#include "util.h"
#include "rules.h"
#include "constants.h"

using namespace std;
using namespace sf;

class Game 
{    
    public:
        Game();
        void Initialize();
        void HandleInput(RenderWindow &window);
        void Update();
        void Draw(RenderWindow &window);

        VideoMode GetVideoMode();
    
    private:
        VideoMode videoMode;
        string pathPieces;
	    string pathBoard;	
	    Texture tPieces, tBoard;
	    Sprite spritePieces;
	    Sprite spriteBoard;
	    Sprite pieces[TOTAL_PIECES];

        bool isMove, updatePosition;
        float dx, dy;
        int idxPiece, idxDragDrop, idxTaked;
        Vector2f oldPosition, newPosition;
        Vector2i positionMouse;
        string chessNote, notesPosition;
        
        void CheckMoveBack(Event event, Sprite *pieces, string &notePosition);
        int CheckDragAndDrop(Event event, Sprite *sprites, Vector2i position);
};

#endif