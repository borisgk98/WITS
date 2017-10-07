#include "WITS.h"

namespace WITS {
	void Game::start() {
		//TODO make menu
		//TODO create player
		WITS::Player playerRed("player1", sf::Color::Red);
		WITS::Player playerBlue("player2", sf::Color::Blue);

		//gameWindow.create(sf::VideoMode(), gameName, sf::Style::Fullscreen);
		gameWindow.create(sf::VideoMode(windowXSize, windowYSize), gameName);
		WITS::Map gameMap(mapSizeY + 1, mapSizeY, &gameWindow);

		while (gameWindow.isOpen()) {

			//event section
			sf::Event event;
			if (gameWindow.pollEvent(event)) {
				//close window
				if (event.type == sf::Event::Closed) {
					gameWindow.close();
				}
				//TODO пофиксить растяжение окна и тестур
				//if window resized
				if (event.type == sf::Event::Resized) {

				}
				//обработка клика
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					//возвращает координаты считая от верхнего левого угла окна игры
					auto x = event.mouseButton.x, y = event.mouseButton.y;
					//кликнули по карте
					if (gameMap.isClicked(x, y)) {
						gameMap.changeTilePlayer(x, y, &playerRed);
					}
				}
			}

			//section generating objects

			//draw section		
			gameWindow.clear(sf::Color(100, 100, 100));
			showMessage("Message");
			gameMap.drawToGameWindows(gameWindow);

			gameWindow.display();
		}
		finish();
	}

	void Game::finish() {
		gameWindow.close();
	}

	void Game::showMessage(std::string message) {
		//TODO красивое отображение и выненести константы
		sf::Text text;
		sf::Font font;
		font.loadFromFile("./src/fonts/arial.ttf");
		text.setString(message);
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Green);
		text.setStyle(sf::Text::Bold);
		text.setPosition(20, 20);
		gameWindow.draw(text);
	}
}