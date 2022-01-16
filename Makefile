output: game.o piecerules.o
	g++ game.o piecerules.o -o game -lsfml-graphics -lsfml-window -lsfml-system

game.o: game.cpp
	g++ -c game.cpp

piecerules.o: piecerules.cpp
	g++ -c piecerules.cpp

clean:
	rm *.o game
