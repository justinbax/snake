#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "snake.h"
#include "tile.h"

int main() {
  constexpr int TILEDIMENSIONS = 32;
  constexpr int MAPHEIGHT = 24;
  constexpr int MAPWIDTH = 30;

  constexpr int UP = 0;
  constexpr int LEFT = 1;
  constexpr int DOWN = 2;
  constexpr int RIGHT = 3;

  // test
  std::vector<SnakeTile> path;
  // end test

  srand(time(0));
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(MAPWIDTH * TILEDIMENSIONS, MAPHEIGHT * TILEDIMENSIONS), "SFML", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  sf::Texture tileTexture;
  if (!tileTexture.loadFromFile("content/tile.png")) {
    std::cerr << "Can't load ./content/tile.png" << std::endl;
  }

  Snake player(sf::Vector2f((rand() % 20 + 5) * TILEDIMENSIONS, (rand() % 18 + 3) * TILEDIMENSIONS), rand() % 4, tileTexture);
  int eating = 0;
  Food food(tileTexture, player);
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
        }
      }
    }
    if (clock.getElapsedTime().asMilliseconds() >= 700) {
      Node nodes[MAPHEIGHT * MAPWIDTH];
      for (int i = 0; i < MAPHEIGHT; i++) {
        for (int j = 0; j < MAPWIDTH; j++) {
          // sets coordinates & neighbours
          nodes[i * MAPHEIGHT + j].setPosition(Coordinates({(float)j, (float)i}));
          if (i > 0) nodes[i * MAPHEIGHT + j].addNeighbour(&nodes[(i - 1) * MAPHEIGHT + j]);
          if (i < MAPHEIGHT - 1) nodes[i * MAPHEIGHT + j].addNeighbour(&nodes[(i + 1) * MAPHEIGHT + j]);
          if (j > 0) nodes[i * MAPHEIGHT + j].addNeighbour(&nodes[i * MAPHEIGHT + j - 1]);
          if (j < MAPWIDTH - 1) nodes[i * MAPHEIGHT + j].addNeighbour(&nodes[i * MAPHEIGHT + j + 1]);
        }
      }
      int index = player.getPosition(0).y * MAPHEIGHT / TILEDIMENSIONS + player.getPosition(0).x / TILEDIMENSIONS;
      Node *start = &nodes[index - 1];
      index = food.getPosition().y * MAPHEIGHT / TILEDIMENSIONS + food.getPosition().x / TILEDIMENSIONS;
      Node *end = &nodes[index];
      std::cout << "end : " << end->getPosition().x << " " << end->getPosition().y << std::endl;
      start->setStart(end);
      std::vector<Node *> toVisit;
      toVisit.push_back(start);
      for (int i = 0; i < player.getLength(); i++) {
        index = player.getPosition(i).y / TILEDIMENSIONS * MAPHEIGHT + player.getPosition(i).x / TILEDIMENSIONS;
        nodes[index].setPassThrough(false);
      }
      while (!toVisit.empty()) {
        quickSortNodes(toVisit, 0, toVisit.size());
        if (toVisit.front() == end) {
          toVisit.erase(toVisit.begin());
          if (toVisit.empty()) {
            break;
          }
        }
        toVisit.front()->visit(end, &toVisit);
      }
      if (end->getParent() != nullptr) {
        Node *current = end->getParent();
        path.clear();
        while (current != nullptr) {
          path.push_back(SnakeTile(sf::Vector2f(current->getPosition().x * TILEDIMENSIONS, current->getPosition().y * TILEDIMENSIONS), 0, tileTexture));
          path.back().getSprite().setColor(sf::Color(0xff, 0x00, 0x00, 0x70));
          path.back().getSprite().setScale(2, 2);
          current = current->getParent();
        }
        if (end->getParent()->getPosition().x - end->getPosition().x > 0) newDirection = RIGHT;
        else if (end->getParent()->getPosition().x - end->getPosition().x < 0) newDirection = LEFT;
        else if (end->getParent()->getPosition().y - end->getPosition().y > 0) newDirection = DOWN;
        else if (end->getParent()->getPosition().y - end->getPosition().y < 0) newDirection = UP;
      } else {
        std::cout << "no path found" << std::endl;
      }
      player.move(newDirection);
      newDirection = -1;
      clock.restart();
      if (eating != 0) {
        player.eat(tileTexture, eating);
      }
    }
    if (food.getSprite().getPosition() == player.getPosition(0)) {
      eating += 2;
      player.eat(tileTexture, eating);
      food.changePosition(player);
    }
    sf::Vector2f plPos = player.getPosition(0);
    for (int i = 1; i < player.getLength(); i++) {
      if (plPos == player.getPosition(i) || plPos.x < 0 || plPos.x >= MAPWIDTH * TILEDIMENSIONS || plPos.y < 0 || plPos.y >= MAPHEIGHT * TILEDIMENSIONS) {
        window.close();
        std::cout << "Game over!" << std::endl;
      }
    }
    window.clear(sf::Color::Black);
    window.draw(food.getSprite());
    player.draw(window);
    for (int i = 0; i < path.size(); i++) {
      window.draw(path[i].getSprite());
    }
    window.display();
  }
  return 0;
}