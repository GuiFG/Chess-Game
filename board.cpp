#include "board.h"
#include "util.h"
#include "constants.h"


void Board::LoadPosition(Sprite *pieces, string position = "")
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
		Util::Move(pieces, position.substr(i, 4));
	}
}
