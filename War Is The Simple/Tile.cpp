#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.cpp"

namespace WITS {
	class Tile {
	private:
		int id;
		//владелец клетки
		WITS::Player *tileOwner;
		//спрайт клетки
		sf::Sprite tileSprite;
	public:
		Tile(sf::Sprite sprite, int tileID) {
			tileSprite = sprite;
			//TODO genrate id
			id = tileID;
			tileOwner = NULL;
		}
		Tile() {}
		sf::Sprite getTileSprite() {
			return tileSprite;
		}
	};

	//for tower tiles
	class TowerTile : Tile {

	};

	//for cities or another industrial tiles
	class FieldTile : Tile {

	};
}