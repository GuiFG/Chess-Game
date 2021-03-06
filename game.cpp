#include "game.h"

Game::Game()
{
    isMove = false;
    updatePosition = false;
    dx = 0;
    dy = 0;
    idxPiece = 0;
    idxDragDrop = -1;
    idxTaked = -1;
    chessNote = ""; 
    notesPosition = "";
    newPosition.x = -1; newPosition.y = -1;
}

void Game::Initialize()
{
    videoMode.width = WIDTH;
    videoMode.height = HEIGHT;

    pathPieces = "images/pieces.png";
	pathBoard = "images/board0.png";	
	tPieces.loadFromFile(pathPieces);
	tBoard.loadFromFile(pathBoard);

	spritePieces.setTexture(tPieces);
	spriteBoard.setTexture(tBoard);

    for (int i = 0; i < TOTAL_PIECES; i++) 
        pieces[i].setTexture(tPieces);	
	
	Board::LoadPosition(pieces, "");
}

void Game::HandleInput(RenderWindow &window)
{
    Event event;
    positionMouse = Mouse::getPosition(window);

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        
        CheckMoveBack(event, pieces, notesPosition);

        idxDragDrop = CheckDragAndDrop(event, pieces, positionMouse);
    }
    
}

void Game::Update()
{
    if (idxDragDrop >= 0 && idxDragDrop < TOTAL_PIECES)
    {
        isMove = true;
        idxPiece = idxDragDrop;
        dx = positionMouse.x - pieces[idxPiece].getPosition().x;
        dy = positionMouse.y - pieces[idxPiece].getPosition().y;
        oldPosition = pieces[idxPiece].getPosition();
    }
    else if (idxDragDrop == TOTAL_PIECES)
    {
        isMove = false;
        newPosition = Util::CenterPosition(pieces[idxPiece]);	
        cout << "Update new position " << newPosition.x << " " << newPosition.y << endl;					
        updatePosition = Rules::CheckValidMove(pieces, newPosition, oldPosition, idxPiece);

        // cout << (updatePosition ? "update position" : "not updated") << endl;

        if (updatePosition)
        {
            chessNote = Util::PositionToChessNote(oldPosition) 
                      + Util::PositionToChessNote(newPosition);
            notesPosition += chessNote + " ";				
            
            pieces[idxPiece].setPosition(newPosition);
            
            // cout << chessNote << endl;
            cout << notesPosition << endl;
        }
        else
        {
            pieces[idxPiece].setPosition(oldPosition);
            // cout << "set old position" << endl;
        }

        idxDragDrop = -1;
    }
    
    if (isMove)
        pieces[idxPiece].setPosition(positionMouse.x - dx, positionMouse.y - dy);	
}

void Game::CheckMoveBack(Event event, Sprite *pieces, string &notePosition)
{
	if (event.type == Event::KeyPressed)
		if (event.key.code == Keyboard::BackSpace)
		{
			if (notePosition.length() >= 5)
			{
				notePosition.erase(notePosition.length() - 5, 5);
				Board::LoadPosition(pieces, notePosition);
			}
		}
}

int Game::CheckDragAndDrop(Event event, Sprite *sprites, Vector2i position)
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

void Game::Draw(RenderWindow &window)
{
	window.clear();
	window.draw(spriteBoard);
	for (int i = 0; i < TOTAL_PIECES; i++) 
		window.draw(pieces[i]);

	window.display();
}

VideoMode Game::GetVideoMode()
{
    return videoMode;
}