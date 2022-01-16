#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include "piecerules.h"

using namespace std;
using namespace sf;

enum PieceEnum {
	ROOK = 1,
	KNIGHT = 2,
	BISHOP = 3,
	QUEEN = 4,
	KING = 5,
	PAWN = 6
};


int board[8][8] =
	{ -1, -2, -3, -4, -5, -3, -2, -1,
	  -6, -6, -6, -6, -6, -6, -6, -6,
	   0,  0,  0,  0,  0,  0,  0,  0,
	   0,  0,  0,  0,  0,  0,  0,  0,
	   0,  0,  0,  0,  0,  0,  0,  0,
	   0,  0,  0,  0,  0,  0,  0,  0,
	   6,  6,  6,  6,  6,  6,  6,  6,
	   1,  2,  3,  4,  5,  3,  2,  1
	};

const int WIDTH = 454;
const int HEIGHT = 454;
const int SIZE_PIECE = 56;
const int TOTAL_PIECES = 32;
const int IDX_BLACK = 16;

string PositionToChessNote(Vector2f position)
{
	string s = "";
	s += char(position.x / SIZE_PIECE + 97);
	s += char(7-position.y / SIZE_PIECE + 49);
	
	return s;
}

Vector2f NoteToCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	
	return Vector2f(x * SIZE_PIECE, y * SIZE_PIECE);
}

void Move(Sprite *pieces, string note)
{
	Vector2f oldPosition = NoteToCoord(note[0], note[1]);
	Vector2f newPosition = NoteToCoord(note[2], note[3]);
	
	for(int i = 0; i < TOTAL_PIECES; i++)
		if (pieces[i].getPosition() == newPosition)
			pieces[i].setPosition(-100, -100);
	
	for (int i = 0; i < TOTAL_PIECES; i++)
		if (pieces[i].getPosition() == oldPosition)
			pieces[i].setPosition(newPosition);

}

void LoadPosition(Sprite *pieces, string position = "")
{
	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
						
			pieces[k].setTextureRect( 
				IntRect(SIZE_PIECE*x, SIZE_PIECE*y, 
					 	SIZE_PIECE, SIZE_PIECE) 
			);
			pieces[k].setPosition(SIZE_PIECE * j, SIZE_PIECE * i);
			k++;
		}
	
	for (int i = 0; i < position.length(); i+= 5)
	{
		Move(pieces, position.substr(i, 4));
	}
}

bool IsBlack(int idx)
{
	return idx < IDX_BLACK;
}

void PrintColorPiece(int idx)
{
	bool isBlack = IsBlack(idx);

	if (isBlack)
		cout << "Black Piece" << endl;
	else
		cout << "White Piece" << endl;
}

string GetNamePieceEnum(int numberPiece)
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


string GetNamePiece(int idxPiece)
{
	string name;		
	int line = idxPiece / 8;
	int col = idxPiece % 8;
	int numberPiece;

	bool isBlack = IsBlack(idxPiece);
	if (isBlack)	
	{
		numberPiece = abs(board[line][col]);
		name = GetNamePieceEnum(numberPiece);

		name += "_black";
	}
	else
	{ 
		line += 4;
		numberPiece = abs(board[line][col]);
		name = GetNamePieceEnum(numberPiece);

		name += "_white";
	}

	return name;
}

bool LegalMove(Sprite *pieces, Vector2f newPosition, int idxPiece)
{
	PieceRules rules;
	string namePiece = GetNamePiece(idxPiece);	

	vector<Vector2f> legalMoves = rules
			.GetLegalMoves(namePiece, pieces[idxPiece].getPosition());
	
	return legalMoves.size() > 1;
}

bool CheckTakeMove(Sprite *piece, Vector2f newPosition, int idxPieceMove)
{
	for (int i = 0; i < TOTAL_PIECES; i++)
	{	
		if (piece[i].getPosition() == newPosition)
		{
			bool isBlack = IsBlack(idxPieceMove);
			bool color = IsBlack(i);
				
			if (isBlack ^ color)
			{
				piece[i].setPosition(-100, -100);
				return true;
			}
			else 
				return false;
		}
	}

	return true;
}

bool CheckValidMove(
			Sprite *pieces, 
			Vector2f newPosition,
			Vector2f oldPosition,
			int idxPiece
)
{
	bool valid = newPosition != oldPosition;
	
	if (!valid)
		return false;
	
	valid = LegalMove(pieces, newPosition, idxPiece);
	
	if (!valid)
		return false;

	valid = CheckTakeMove(pieces, newPosition, idxPiece);				
	
	return valid;
}

Vector2f CenterPosition(Sprite piece)
{
	Vector2f p = piece.getPosition() + Vector2f(SIZE_PIECE/2, SIZE_PIECE/2);
	Vector2f center = Vector2f( SIZE_PIECE * int(p.x/SIZE_PIECE),
								SIZE_PIECE * int(p.y/SIZE_PIECE));
	
	return center;
}

void CheckMoveBack(Event event, Sprite *pieces, string &notePosition)
{
	if (event.type == Event::KeyPressed)
		if (event.key.code == Keyboard::BackSpace)
		{
			if (notePosition.length() >= 5)
			{
				notePosition.erase(notePosition.length() - 5, 5);
				LoadPosition(pieces, notePosition);
			}
		}
}

int CheckDragAndDrop(Event event, Sprite *sprites, Vector2i position)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.key.code == Mouse::Left)
		{
			for (int i = 0; i < TOTAL_PIECES; i++)
			{
				if (sprites[i].getGlobalBounds()
					.contains(position.x, position.y)
				)  return i;
			}
		}
	}

	if (event.type == Event::MouseButtonReleased
		&& event.key.code == Mouse::Left)
		return TOTAL_PIECES;

	return -1;
}

void Draw(RenderWindow &window, const Sprite sprite, Sprite *pieces)
{
	window.clear();
	window.draw(sprite);
	for (int i = 0; i < TOTAL_PIECES; i++) 
		window.draw(pieces[i]);
	window.display();
}



int main()
{
	VideoMode videoMode(WIDTH, HEIGHT);
	string pathPieces = "images/pieces.png";
	string pathBoard = "images/board0.png";	

	Texture tPieces, tBoard;
	tPieces.loadFromFile(pathPieces);
	tBoard.loadFromFile(pathBoard);

	Sprite spritePieces(tPieces);
	Sprite spriteBoard(tBoard);
	
	Sprite pieces[TOTAL_PIECES];
	for (int i = 0; i < TOTAL_PIECES; i++) 
		pieces[i].setTexture(tPieces);	
	
	LoadPosition(pieces);
	
	RenderWindow window(videoMode, "The Chess!");
	
	bool isMove = false;
	float dx = 0, dy = 0;
	int idxPiece = 0;
	Vector2f oldPosition, newPosition;
	string chessNote, notesPosition = "";

	while(window.isOpen())
	{
		Vector2i position = Mouse::getPosition(window);

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
			CheckMoveBack(event, pieces, notesPosition);			

			int idx = CheckDragAndDrop(event, pieces, position);
			if (idx >= 0 && idx < TOTAL_PIECES)
			{
				isMove = true;
				idxPiece = idx;
				dx = position.x - pieces[idxPiece].getPosition().x;
				dy = position.y - pieces[idxPiece].getPosition().y;
				oldPosition = pieces[idxPiece].getPosition();
			}
			else if (idx == TOTAL_PIECES)
			{
				isMove = false;
				newPosition  = CenterPosition(pieces[idxPiece]);						
				bool valid = CheckValidMove(pieces, newPosition, oldPosition, idxPiece);
				if (valid)
				{
					chessNote = PositionToChessNote(oldPosition) 
						  	  + PositionToChessNote(newPosition);
					notesPosition += chessNote + " ";				
					
					pieces[idxPiece].setPosition(newPosition);
					cout << chessNote << endl;
				}
				else
					pieces[idxPiece].setPosition(oldPosition);
			}
		}
		
		if (isMove)
			pieces[idxPiece].setPosition(position.x - dx, position.y - dy);	
		
		Draw(window, spriteBoard, pieces);
	}

	return 0;
}
