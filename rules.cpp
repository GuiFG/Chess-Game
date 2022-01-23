#include "rules.h"
#include "util.h"
#include "constants.h"


bool Rules::CheckTakeMove(Sprite *pieces, Vector2f newPosition, int idxPieceMove)
{
	for (int i = 0; i < TOTAL_PIECES; i++)
	{	
		if (pieces[i].getPosition() == newPosition && i != idxPieceMove)
		{
			bool isBlackPieceMove = Util::IsBlack(idxPieceMove);
			bool isBlackPieceTaked = Util::IsBlack(i);
			
			/*
			cout << "Idx piece move " << idxPieceMove << endl;
			cout << "Idx taked " << i << endl;
			cout << "Piece position: " << piece[i].getPosition().x << " " << piece[i].getPosition().y << endl;
			cout << "New Position: " << newPosition.x << " " << newPosition.y << endl; */

			if (isBlackPieceMove ^ isBlackPieceTaked)
			{
				// cout << "different colors" << endl;
				pieces[i].setPosition(-100, -100);
				return true;
			}
			else 
				return false;
		}
	}

	return true;
}

vector<Vector2f> Rules::GetLegalMoves(string namePiece, Vector2f actualPosition)
{
	// cout << "Name Piece: " << namePiece << endl;
	// cout << "Actual position: " << actualPosition.x << " " << actualPosition.y << endl;

	vector<Vector2f> moves;

	return moves;
}

bool Rules::IsLegalMove(Sprite *pieces, Vector2f newPosition, int idxPiece)
{
	string namePiece = Util::GetNamePieceByIdx(idxPiece);	

	vector<Vector2f> legalMoves = GetLegalMoves(namePiece, pieces[idxPiece].getPosition());
	
	return legalMoves.size() >= 0;
}

bool Rules::CheckValidMove(
			Sprite *pieces, 
			Vector2f newPosition,
			Vector2f oldPosition,
			int idxPiece
)
{
	bool valid = newPosition != oldPosition;
	
	if (!valid)
		return false;
	
	valid = IsLegalMove(pieces, newPosition, idxPiece);

	if (!valid)
		return false; 

	valid = Rules::CheckTakeMove(pieces, newPosition, idxPiece);	

	return valid;
}



