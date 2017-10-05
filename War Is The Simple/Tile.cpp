#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.cpp"

namespace WITS {

	class Tile {
	private:
		//int id;
		//�������� ������
		WITS::Player *tileOwner;
		//������ ������
		sf::Sprite tileSprite;
		//�������� ������
		sf::Texture tileTexture;
	public:
		sf::Sprite getTileSprite() {
			return tileSprite;
		}
		void setSprite(sf::Sprite &sprite) {
			tileSprite = sprite;
		}
	};

	//for tower tiles
	class TowerTile : public Tile {
	};

	//for cities or another industrial tiles
	class FieldTile : public Tile {
	};
}