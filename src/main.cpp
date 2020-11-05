#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "snake.h"

int main() {
  srand(time(0));
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(30 * 32, 24 * 32), "SFML", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  sf::Texture tileTexture;
  if (!tileTexture.loadFromFile("content/tile.png")) {
    std::cerr << "Can't load ./content/tile.png" << std::endl;
  }

  Snake player(sf::Vector2f((rand() % 20 + 5) * 32, (rand() % 18 + 3) * 32), rand() % 4, &tileTexture);
  int eating = 0;
  Food food(&tileTexture, &player);
  sf::Clock clock;
  int newDirection = -1;
  while (window.isOpen()) {
    sf::Event evnt;
    while (window.pollEvent(evnt)) {
      if (evnt.type == sf::Event::Closed) {
        window.close();
      } else if (evnt.type == sf::Event::KeyPressed) {
        if (evnt.key.code == sf::Keyboard::Escape) {
          window.close();
        } else if (evnt.key.code == sf::Keyboard::W) {
          newDirection = 0;
        } else if (evnt.key.code == sf::Keyboard::D) {
          newDirection = 1;
        } else if (evnt.key.code == sf::Keyboard::S) {
          newDirection = 2;
        } else if (evnt.key.code == sf::Keyboard::A) {
          newDirection = 3;
        }
      }
    }
    if (clock.getElapsedTime().asMilliseconds() >= 130) {
      player.move(newDirection);
      newDirection = -1;
      clock.restart();
      if (eating != 0) {
        player.eat(&tileTexture, &eating);
      }
    }
    if ((*food.getSprite()).getPosition() == player.getPosition(0)) {
      eating += 2;
      player.eat(&tileTexture, &eating);
      food.changePosition(&player);
    }
    sf::Vector2f plPos = player.getPosition(0);
    for (int i = 1; i < player.getLength(); i++) {
      if (plPos == player.getPosition(i) or plPos.x < 0 or plPos.x >= 960 or plPos.y < 0 or plPos.y >= 768) {
        window.close();
        std::cout << "Game over!" << std::endl;
      }
    }
    window.clear(sf::Color::Black);
    window.draw(*food.getSprite());
    player.draw(&window);
    window.display();
  }
  return 0;
}