#include "snake.h"
#include <vector>

SnakeTile::SnakeTile(sf::Vector2f position, int direction) {
  this->sprite.setPosition(position);
  this->direction = direction;
}

void SnakeTile::move() {
  int deltaX = 0;
  int deltaY = 0;
  switch (this->direction) {
    case 0:
      deltaY += -16;
      break;
    case 1:
      deltaX += 16;
      break;
    case 2:
      deltaY += 16;
      break;
    case 3:
      deltaX += -16;
      break;
  }
  this->sprite.move(sf::Vector2f(deltaX, deltaY));
}

void SnakeTile::setDirection(int direction) {
  this->direction = direction;
}

int SnakeTile::getDirection() {
  return this->direction;
}

Snake::Snake(sf::Vector2f startingPos, int direction) {
  sf::Vector2f position = {startingPos.x, startingPos.y};
  for (int i = 0; i < 4; i++) {
    switch (direction) {
      case 0:
        position.y += -16 * i;
        break;
      case 1:
        position.x += 16 * i;
      case 2:
        position.y += 16 * i;
      case 3:
        position.x += -16 * i;
    }
    SnakeTile *ptr = new SnakeTile(position, direction);
    std::vector<SnakeTile>::iterator it;
    it = this->snakeTiles.begin();
    it = this->snakeTiles.insert(it, *ptr);
    delete ptr;
  }
  this->length = this->snakeTiles.size();
}

void Snake::move(int direction) {
  SnakeTile *firstSnakeTile = &this->snakeTiles[this->snakeTiles.size() - 1];
  switch (direction) {
    case -1:
      break;
    case 0:
      if ((*firstSnakeTile).getDirection() != 2) {
        (*firstSnakeTile).setDirection(direction);
      }
      break;
    case 1:
      if ((*firstSnakeTile).getDirection() != 3) {
        (*firstSnakeTile).setDirection(direction);
      }
      break;
    case 2:
      if ((*firstSnakeTile).getDirection() != 0) {
        (*firstSnakeTile).setDirection(direction);
      }
      break;
    case 3:
      if ((*firstSnakeTile).getDirection() != 1) {
        (*firstSnakeTile).setDirection(direction);
      }
      break;
  }
  for (int i = 0; i < this->snakeTiles.size() - 1; i++) {
    this->snakeTiles[i].move();
  }
}

Food::Food() {
  this->changePosition();
}

sf::Vector2f Food::getPosition() {
  return this->sprite.getPosition();
}

void Food::changePosition() {
  srand(time(0));
  int x = rand() % 60;
  int y = rand() % 48;
  this->sprite.setPosition(sf::Vector2f(x * 16, y * 16));
}