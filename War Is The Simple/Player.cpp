#include "WITS.h"

namespace WITS {
	Player::Player() {}
	Player::Player(std::string playerName, sf::Color playerColor) {
		name = playerName;
		color = playerColor;
	}
	sf::Color Player::getColor() {
		return color;
	}
}