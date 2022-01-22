#ifndef RULES_H
#define RULES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Rules { 
	public:
		Rules();
		static vector<Vector2f> GetLegalMoves(string namePiece, Vector2f actualPosition);
		static bool CheckTakeMove(Sprite *piece, Vector2f newPosition, int idxPieceMove);
		static bool IsLegalMove(Sprite *pieces, Vector2f newPosition, int idxPiece);
		static bool CheckValidMove(Sprite *pieces, Vector2f newPosition, Vector2f oldPosition, int idxPiece);
	
};

#endif
