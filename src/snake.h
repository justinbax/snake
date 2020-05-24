#ifndef SNAKE_H
#define SNAKE_H
#endif

#include <vector>
#include <SFML/Graphics.hpp>

class SnakeTile {
  public:
    SnakeTile(sf::Vector2f, int, sf::Texture*);
    void move();
    void setDirection(int);
    int getDirection();
    sf::Sprite* getSprite();
  private:
    sf::Sprite sprite;
    int direction;
};

class Snake {
  public:
    Snake(sf::Vector2f, int, sf::Texture*);
    void move(int);
    void draw(sf::RenderWindow*);
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