start: main.o Ship.o Board.o Player.o Game.o
	clang++ -std=c++11 -stdlib=libc++ main.o Ship.o Board.o Player.o Game.o -o start

main.o: main.cpp
	clang++ -std=c++11 -stdlib=libc++ -c main.cpp

Ship.o: Ship.cpp Ship.hpp
	clang++ -std=c++11 -stdlib=libc++ -c Ship.cpp

Board.o: Board.cpp Board.hpp
	clang++ -std=c++11 -stdlib=libc++ -c Board.cpp

Player.o: Player.cpp Player.hpp
	clang++ -std=c++11 -stdlib=libc++ -c Player.cpp

Game.o: Game.cpp Game.hpp
	clang++ -std=c++11 -stdlib=libc++ -c Game.cpp

clean:
	rm *.o start