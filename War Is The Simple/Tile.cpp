#include "WITS.h"

namespace WITS {
	sf::Sprite Tile::getTileSprite() {
		return sprite;
	}
	void Tile::setSprite(sf::Sprite &newSprite) {
		sprite = newSprite;
	}
	void Tile::changeOwner(Player *player) {
		tileOwner = player;
		sprite.setColor(player->getColor());
	}

	void Tile::setId(int ID) {
		id = ID;
	}
}