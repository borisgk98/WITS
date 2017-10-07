#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

namespace WITS {
	const std::string
		towerTileTextureImgSource = "./src/img/towerTileTexture.png",
		fieldTileTextureImgSource = "./src/img/fieldTileTexture.png";

	class Clickable {
	protected:
		sf::Sprite sprite;
	public:
		bool isClicked(int x, int y);
	};

	class Player {
	protected:
		std::string name;
		sf::Color color;
	public:	
		Player();
		Player(std::string playerName, sf::Color playerColor);
		sf::Color getColor();
	};

	class Tile : public Clickable {
	protected:
		int id;
		//владелец клетки
		WITS::Player *tileOwner;
	public:
		sf::Sprite getTileSprite();
		void setSprite(sf::Sprite &newSprite);
		void setId(int ID);
		void changeOwner(Player *player);
	};

	//for cities or another industrial tiles
	class FieldTile : public Tile {};

	//for tower tiles
	class TowerTile : public Tile {};

	class Map {
	private:
		//grid -- сетка
		std::vector <std::vector <WITS::FieldTile> > fieldsGrid;
		std::vector <std::vector <WITS::TowerTile> > towersGrid;
		sf::Texture fieldTileTexture, towerTileTexture;
		sf::RenderWindow *gameWindow;
		int xSize, ySize, moveX, moveY;
	public:
		Map(int mapXSize, int mapYSize, sf::RenderWindow *window);
		void create(int xSize, int ySize);
		void drawToGameWindows(sf::RenderWindow& gameWindow);
		bool isClicked(int xPoz, int yPoz);
		bool changeTilePlayer(int x, int y, Player *player);
		Tile* getTile(int x, int y);
	};

	class Game {
	private:
		sf::RenderWindow gameWindow;
		const std::string gameName = "War Is The Simple";
		const int mapSizeY = 9,
			windowXSize = 1400, windowYSize = 1000;
	public:
		void start();
		void finish();
		void Game::showMessage(std::string messange);
	};
}