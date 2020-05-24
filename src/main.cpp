#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "snake.h"

int main() {
  srand(time(0));
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(960, 768), "SFML", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  sf::Texture tileTexture;
  if (!tileTexture.loadFromFile("content/tile.png")) {
    std::cerr << "Can't load ./content/tile.png" << std::endl;
  }

  Snake player(sf::Vector2f(rand() % 60 * 16, rand() % 48 * 16), rand() % 4, &tileTexture);
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
    if (clock.getElapsedTime().asMilliseconds() >= 350) {
      player.move(newDirection);
      newDirection = -1;
      clock.restart();
    }
    window.clear(sf::Color::Black);
    player.draw(&window);
    window.display();
  }
  return 0;
}