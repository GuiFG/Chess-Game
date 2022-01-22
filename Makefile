output: chess.o game.o rules.o board.o util.o
	g++ obj/*.o -o chess -lsfml-graphics -lsfml-window -lsfml-system

chess.o: chess.cpp
	g++ -c chess.cpp -o obj/chess.o

game.o: game.cpp 
	g++ -c game.cpp -o obj/game.o

rules.o: rules.cpp
	g++ -c rules.cpp -o obj/rules.o

board.o: board.cpp 
	g++ -c board.cpp -o obj/board.o

util.o: util.cpp 
	g++ -c util.cpp -o obj/util.o

clean:
	rm obj/*.o
