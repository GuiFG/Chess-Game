#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include "rules.h"
#include "util.h"
#include "constants.h"
#include "board.h"
#include "game.h"

using namespace std;
using namespace sf;


int main()
{
	Game game;
	game.Initialize();

	RenderWindow window(game.GetVideoMode(), "The Chess!");

	while(window.isOpen())
	{
		game.HandleInput(window);
		game.Update();
		game.Draw(window);
	}

	return 0;
}
