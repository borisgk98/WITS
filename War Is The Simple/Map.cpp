#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.cpp"

namespace WITS {

	const std::string towerTileTextureImgSource = "./src/img/towerTileTexture.png",
		fieldTileTextureImgSource = "./src/img/fieldTileTexture.png";

	class Map {
	private:
		//grid -- сетка
		std::vector <std::vector <WITS::FieldTile> > fieldsGrid;
		std::vector <std::vector <WITS::TowerTile> > towersGrid;
		sf::Image fieldTileTextureImg, towerTileTextureImg;
		sf::Texture fieldTileTexture, towerTileTexture;
	public:
		Map(int xSize, int ySize) {
			create(xSize, ySize);
		}
		void create(int xSize, int ySize) {
			towerTileTextureImg.loadFromFile(towerTileTextureImgSource);
			fieldTileTextureImg.loadFromFile(fieldTileTextureImgSource);
			fieldTileTexture.loadFromImage(fieldTileTextureImg);
			towerTileTexture.loadFromImage(towerTileTextureImg);
			fieldTileTexture.setSmooth(true);
			towerTileTexture.setSmooth(true);

			//TODO выравнивание по центру
			int moveX = 100, moveY = 100;
			//grid[y][x]
			fieldsGrid.resize(ySize);
			//for id
			//int iter = 0;
			for (int y = 0; y < fieldsGrid.size(); y++) {
				fieldsGrid[y].resize(xSize - y % 2);
				for (int x = 0; x < fieldsGrid[y].size(); x++) {
					sf::Sprite fieldTileSprite;
					fieldTileSprite.setTexture(fieldTileTexture);
					fieldTileSprite.setPosition((2 * x + y % 2) * fieldTileTextureImg.getSize().x / 2, 
						y  * fieldTileTextureImg.getSize().y / 2);
					fieldTileSprite.move(moveX, moveY);
					//add to tiles
					FieldTile fieldTile;
					fieldTile.setSprite(fieldTileSprite);
					fieldsGrid[y][x] = fieldTile;
				}
			}

			towersGrid.resize(ySize - 2);
			for (int y = 0; y < towersGrid.size(); y++) {
				towersGrid[y].resize(xSize - 2 + y % 2);
				for (int x = 0; x < towersGrid[y].size(); x++) {
					sf::Sprite towerTileSprite;
					towerTileSprite.setTexture(towerTileTexture);
					towerTileSprite.setPosition((2 * (x + 1 - y % 2) + y % 2) * fieldTileTextureImg.getSize().x / 2, 
								(y + 2)  * fieldTileTextureImg.getSize().y / 2);
					towerTileSprite.move((fieldTileTextureImg.getSize().x - towerTileTextureImg.getSize().x) / 2,
						-(int)(towerTileTextureImg.getSize().y / 2));
					towerTileSprite.move(moveX, moveY);
					//add to tiles
					TowerTile towerTile;
					towerTile.setSprite(towerTileSprite);
					towersGrid[y][x] = towerTile;
				}
			}
		}
		void drawToGameWindows(sf::RenderWindow& gameWindow) {
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
	};
}
