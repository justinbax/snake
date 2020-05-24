#ifndef SNAKE_H
#define SNAKE_H
#endif

#include <vector>
#include <SFML/Graphics.hpp>

class SnakeTile {
  public:
    SnakeTile(sf::Vector2f, int);
    void move();
    void setDirection(int);
    int getDirection();
  private:
    sf::Sprite sprite;
    int direction;
};

class Snake {
  public:
    Snake(sf::Vector2f, int);
    void move(int);
  private:
    int length;
    std::vector<SnakeTile> snakeTiles;
};

class Food {
  public:
    Food();
    sf::Vector2f getPosition();
    void changePosition();
  private:
    sf::Sprite sprite;
};