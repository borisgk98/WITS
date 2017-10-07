#include "WITS.h"

namespace WITS {
	bool Clickable::isClicked(int x, int y) {
		auto img = sprite.getTexture()->copyToImage();
		if (sprite.getPosition().x >= x ||
			sprite.getPosition().x + img.getSize().x <= x ||
			sprite.getPosition().y >= y ||
			sprite.getPosition().y + img.getSize().y <= y)
			return false;
		auto pixel = img.getPixel(x - sprite.getPosition().x, y - sprite.getPosition().y);
		return pixel != sf::Color::Transparent;
	}

	Map::Map(int mapXSize, int mapYSize, sf::RenderWindow *window): xSize(mapXSize), ySize(mapYSize) {
		gameWindow = window;
		create(xSize, ySize);
	}

	void Map::create(int xSize, int ySize) {
		fieldTileTexture.loadFromFile(fieldTileTextureImgSource);
		towerTileTexture.loadFromFile(towerTileTextureImgSource);
		fieldTileTexture.setSmooth(true);
		towerTileTexture.setSmooth(true);

		//TODO выравнивание по центру
		moveX = gameWindow->getSize().x / 2 - xSize * fieldTileTexture.getSize().x / 2, moveY = gameWindow->getSize().y / 2 - ySize * fieldTileTexture.getSize().y / 4;
		//grid[y][x]
		fieldsGrid.resize(ySize);
		//for id
		int iter = 0;
		for (int y = 0; y < fieldsGrid.size(); y++) {
			fieldsGrid[y].resize(xSize - y % 2);
			for (int x = 0; x < fieldsGrid[y].size(); x++) {
				sf::Sprite fieldTileSprite;
				fieldTileSprite.setTexture(fieldTileTexture);
				fieldTileSprite.setPosition((2 * x + y % 2) * fieldTileTexture.getSize().x / 2, 
					y  * fieldTileTexture.getSize().y / 2);
				fieldTileSprite.move(moveX, moveY);
				FieldTile fieldTile;
				fieldTile.setSprite(fieldTileSprite);
				fieldTile.setId(iter++);
				fieldsGrid[y][x] = fieldTile;
			}
		}

		towersGrid.resize(ySize - 2);
		for (int y = 0; y < towersGrid.size(); y++) {
			towersGrid[y].resize(xSize - 2 + y % 2);
			for (int x = 0; x < towersGrid[y].size(); x++) {
				sf::Sprite towerTileSprite;
				towerTileSprite.setTexture(towerTileTexture);
				towerTileSprite.setPosition((2 * (x + 1 - y % 2) + y % 2) * fieldTileTexture.getSize().x / 2, 
							(y + 2)  * fieldTileTexture.getSize().y / 2);
				towerTileSprite.move((fieldTileTexture.getSize().x - towerTileTexture.getSize().x) / 2,
					-(int)(towerTileTexture.getSize().y / 2));
				towerTileSprite.move(moveX, moveY);
				TowerTile towerTile;
				towerTile.setSprite(towerTileSprite);
				towerTile.setId(iter++);
				towersGrid[y][x] = towerTile;
			}
		}
	}

	void Map::drawToGameWindows(sf::RenderWindow& gameWindow) {
		for (int y = 0; y < fieldsGrid.size(); y++) {
			for (int x = 0; x < fieldsGrid[y].size(); x++) {
				gameWindow.draw(fieldsGrid[y][x].getTileSprite());
			}
		}
		for (int y = 0; y < towersGrid.size(); y++) {
			for (int x = 0; x < towersGrid[y].size(); x++) {
				gameWindow.draw(towersGrid[y][x].getTileSprite());
			}
		}
	}

	bool Map::isClicked(int xPoz, int yPoz) {
		int leftX = moveX,
			rightX = moveX + xSize * fieldTileTexture.getSize().x,
			botY = moveY,
			topY = moveY + ySize * fieldTileTexture.getSize().y;
		return xPoz <= rightX && xPoz >= leftX && yPoz <= topY && yPoz >= botY;
	}

	bool Map::changeTilePlayer(int x, int y, Player *player) {
		Tile* tile = getTile(x, y);
		if (tile == NULL)
			return false;
		tile->changeOwner(player);
	}

	Tile* Map::getTile(int X, int Y) {
		//if tower
		for (int y = 0; y < towersGrid.size(); y++) {
			for (int x = 0; x < towersGrid[y].size(); x++) {
				if (towersGrid[y][x].isClicked(X, Y))
					return &towersGrid[y][x];
			}
		}
		//if field
		for (int y = 0; y < fieldsGrid.size(); y++) {
			for (int x = 0; x < fieldsGrid[y].size(); x++) {
				if (fieldsGrid[y][x].isClicked(X, Y))
					return &fieldsGrid[y][x];
			}
		}
		return NULL;
	}
}
