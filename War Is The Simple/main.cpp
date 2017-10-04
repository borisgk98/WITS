//War Is The Simple game

//TODO class Tile

//TODO class Unit

#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.cpp"

inline int f(int a, int b) {
	return a + b;
}

int main() {

	WITS::Game game;
	game.start();

	int c = 3, d = 5;
	int p = f(c, d);
	int a = c, b = d;
	p = a + b;
	return 0;
}