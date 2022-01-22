#include "util.h"
#include "constants.h"
#include "board.h"

bool Util::IsBlack(int idx)
{
	return idx < IDX_BLACK;
}

string Util::PositionToChessNote(Vector2f position)
{
	string s = "";
	s += char(position.x / SIZE_PIECE + 97);
	s += char(7-position.y / SIZE_PIECE + 49);
	
	return s;
}

Vector2f Util::NoteToCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	
	return Vector2f(x * SIZE_PIECE, y * SIZE_PIECE);
}

void Util::Move(Sprite *pieces, string note)
{
	Vector2f oldPosition = Util::NoteToCoord(note[0], note[1]);
	Vector2f newPosition = Util::NoteToCoord(note[2], note[3]);
	
	for(int i = 0; i < TOTAL_PIECES; i++)
		if (pieces[i].getPosition() == newPosition)
			pieces[i].setPosition(-100, -100);
	
	for (int i = 0; i < TOTAL_PIECES; i++)
		if (pieces[i].getPosition() == oldPosition)
			pieces[i].setPosition(newPosition);

}

string Util::GetNamePieceEnum(int numberPiece)
{
	string name;
	switch(numberPiece)
	{
		case PAWN:
			name = "pawn";
			break;
		case KNIGHT:
			name = "knight";
			break;
		case BISHOP:
			name = "bishop";
			break;
		case ROOK:
			name = "rook";
			break;
		case QUEEN:
			name = "queen";
			break;
		case KING:
			name = "king";
			break; 
		default:
			break;
	}
	
	return name;
}

string Util::GetNamePieceByIdx(int idxPiece)
{
	string name;		
	int line = idxPiece / 8;
	int col = idxPiece % 8;
	int numberPiece;

	bool isBlack = IsBlack(idxPiece);
	if (isBlack)	
	{
		numberPiece = abs(board[line][col]);
		name = Util::GetNamePieceEnum(numberPiece);

		name += "_black";
	}
	else
	{ 
		line += 4;
		numberPiece = abs(board[line][col]);
		name = Util::GetNamePieceEnum(numberPiece);

		name += "_white";
	}

	return name;
}

Vector2f Util::CenterPosition(Sprite piece)
{
	Vector2f p = piece.getPosition() + Vector2f(SIZE_PIECE/2, SIZE_PIECE/2);
	Vector2f center = Vector2f( SIZE_PIECE * int(p.x/SIZE_PIECE),
								SIZE_PIECE * int(p.y/SIZE_PIECE));
	
	return center;
}
