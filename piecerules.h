#ifndef PIECE_RULES_H
#define PIECE_RULES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class PieceRules { 
	public:
		vector<Vector2f> GetLegalMoves(string namePiece, Vector2f actualPosition);
};

#endif
