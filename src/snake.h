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
    void eat(sf::Texture *);
    sf::Vector2f getPosition(int);
    int getLength();
  private:
    int length;
    std::vector<SnakeTile> snakeTiles;
};

class Food {
  public:
    Food(sf::Texture *, Snake *);
    sf::Vector2f getPosition();
    void changePosition(Snake *);
    sf::Sprite* getSprite();
  private:
    sf::Sprite sprite;
};