#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.cpp"

namespace WITS {

	const std::string towerTileTextureImgSource = "./src/img/towerTileTexture.png",
					fieldTileTextureImgSource = "./src/img/fieldTileTexture.png";

	class Map {
	private:
		std::vector<WITS::Tile> tiles;
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
			
			//xSize * ySize  - fieldTiles
			//xSize * ySize + xSize  - towerTiles
			tiles.resize(xSize * ySize + (ySize - 2) * (xSize - 1));

			//TODO выравниваие по центру
			const int test = 100;
			//for fields
			int iter = 0;
			for (int y = 0; y < ySize; y++) {
				for (int x = 0; x < xSize - y % 2; x++) {
					sf::Sprite fieldTileSprite;
					fieldTileSprite.setTexture(fieldTileTexture);
					fieldTileSprite.setPosition((2 * x + y % 2) * fieldTileTextureImg.getSize().x / 2 + test, y  * fieldTileTextureImg.getSize().y / 2 + test);
					//add to tiles
					tiles[iter] = (WITS::Tile(fieldTileSprite, iter++));
				}
			}

			//for towers
			for (int y = 2; y < ySize; y++) {
				for (int x = (y + 1) % 2; x < xSize - 1; x++) {
					sf::Sprite towerTileSprite;
					towerTileSprite.setTexture(towerTileTexture);
					towerTileSprite.setPosition((2 * x + y % 2) * fieldTileTextureImg.getSize().x / 2 + test, y  * fieldTileTextureImg.getSize().y / 2 + test);
					towerTileSprite.move((fieldTileTextureImg.getSize().x - towerTileTextureImg.getSize().x) / 2, -(int)(towerTileTextureImg.getSize().y / 2));
					//add to tiles
					tiles[iter] = (WITS::Tile(towerTileSprite, iter++));
				}
			}
		}
		void drawToGameWindows(sf::RenderWindow& gameWindow) {
			for (int i = 0; i < tiles.size(); i++) {
				gameWindow.draw((tiles[i]).getTileSprite());
			}
		}
	};
}