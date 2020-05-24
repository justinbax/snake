#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main() {
  std::cout << "henlo";
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);
  while (window.isOpen()) {
    sf::Event evnt;
    while (window.pollEvent(evnt)) {
      if (evnt.type == sf::Event::Closed) {
        window.close();
      } else if (evnt.type == sf::Event::KeyPressed) {
        if (evnt.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
    }
  }
  return 0;
}