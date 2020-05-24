#include "snake.h"
#include <vector>

SnakeTile::SnakeTile(sf::Vector2f position, int direction, sf::Texture *tile) {
  this->sprite.setTexture(*tile);
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

sf::Sprite* SnakeTile::getSprite() {
  return &this->sprite;
}

Snake::Snake(sf::Vector2f startingPos, int direction, sf::Texture *tile) {
  sf::Vector2f position = {startingPos.x, startingPos.y};
  for (int i = 0; i < 4; i++) {
    switch (direction) {
      case 0:
        position.y += -16;
        break;
      case 1:
        position.x += 16;
        break;
      case 2:
        position.y += 16;
        break;
      case 3:
        position.x += -16;
        break;
    }
    SnakeTile *ptr = new SnakeTile(position, direction, tile);
    std::vector<SnakeTile>::iterator it;
    it = this->snakeTiles.begin();
    it = this->snakeTiles.insert(it, *ptr);
    delete ptr;
  }
  this->length = this->snakeTiles.size();
}

void Snake::move(int direction) {
  SnakeTile *firstSnakeTile = &this->snakeTiles[0];
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
  for (int i = 0; i < this->snakeTiles.size(); i++) {
    this->snakeTiles[i].move();
  }
  for (int i = this->snakeTiles.size() - 1; i > 0; i--) {
    this->snakeTiles[i].setDirection(this->snakeTiles[i - 1].getDirection());
  }
}

void Snake::draw(sf::RenderWindow *window) {
  for (int i = 0; i < this->snakeTiles.size(); i++) {
    (*window).draw(*(this->snakeTiles[i].getSprite()));
  }
}

void Snake::eat(sf::Texture *texture) {
  sf::Vector2f newPos = this->getPosition(this->getLength() - 1);
  switch (this->snakeTiles[this->getLength() - 1].getDirection()) {
    case 0:
      newPos.y += 16;
      break;
    case 1:
      newPos.x += -16;
      break;
    case 2:
      newPos.y += -16;
      break;
    case 3:
      newPos.x += 16;
      break;
  }
  SnakeTile *ptr = new SnakeTile(newPos, this->snakeTiles[this->getLength() - 1].getDirection(), texture);
  std::vector<SnakeTile>::iterator it;
  it = this->snakeTiles.end();
  it = this->snakeTiles.insert(it, *ptr);
  delete ptr;
}

sf::Vector2f Snake::getPosition(int position) {
  return (*this->snakeTiles[position].getSprite()).getPosition();
}

int Snake::getLength() {
  return this->length;
}

Food::Food(sf::Texture *texture, Snake *player) {
  this->sprite.setTexture(*texture);
  this->changePosition(player);
}

sf::Vector2f Food::getPosition() {
  return this->sprite.getPosition();
}

void Food::changePosition(Snake *player) {
  srand(time(0));
  int x = rand() % 60;
  int y = rand() % 48;
  sf::Vector2f newPos = {float(x * 16), float(y * 16)};
  for (int i = 0; i < (*player).getLength(); i++) {
    while (newPos == (*player).getPosition(i)) {
      x = rand() % 60;
      y = rand() % 48;
      newPos = {float(x * 16), float(y * 16)};
      i = 0;
    }
  }
  this->sprite.setPosition(newPos);
}

sf::Sprite* Food::getSprite() {
  return &this->sprite;
}