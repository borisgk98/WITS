#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Map.cpp"

namespace WITS {
	class Game {
	private:
		sf::RenderWindow gameWindow;
		const std::string gameName = "War Is The Simple";
		const int mapSizeY = 9;
	public:
		void start() {
			//TODO make menu
			//TODO create player
			//gameWindow.create(sf::VideoMode(), gameName, sf::Style::Fullscreen);
			gameWindow.create(sf::VideoMode(1200, 800), gameName);
			WITS::Map gameMap(mapSizeY + 1, mapSizeY);

			while (gameWindow.isOpen()) {

				//event section
				sf::Event event;
				while (gameWindow.pollEvent(event)) {
					//
					if (event.type == sf::Event::Closed) {
						gameWindow.close();
					}
				}

				//section generating objects

				//draw section
				gameWindow.clear(sf::Color(100, 100, 100));
				gameMap.drawToGameWindows(gameWindow);

				gameWindow.display();
			}
			finish();
		}
		void finish() {
			gameWindow.close();
		}
	};
}