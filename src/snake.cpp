#include "snake.h"

SnakeTile::SnakeTile(sf::Vector2f position, int direction, sf::Texture &tile) {
  this->sprite.setTexture(tile);
  this->sprite.setPosition(position);
  this->direction = direction;
}

void SnakeTile::move() {
  int deltaX = 0;
  int deltaY = 0;
  switch (this->direction) {
    case 0:
      deltaY += 32;
      break;
    case 1:
      deltaX += 32;
      break;
    case 2:
      deltaY += -32;
      break;
    case 3:
      deltaX += -32;
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

sf::Sprite &SnakeTile::getSprite() {
  return this->sprite;
}

Snake::Snake(sf::Vector2f startingPos, int direction, sf::Texture &tile) {
  for (int i = 0; i < 4; i++) {
    switch (direction) {
      case 0:
        startingPos.y += -32;
        break;
      case 1:
        startingPos.x += 32;
        break;
      case 2:
        startingPos.y += 32;
        break;
      case 3:
        startingPos.x += -32;
        break;
    }
    this->snakeTiles.insert(snakeTiles.begin(), SnakeTile(startingPos, direction, tile));
    this->snakeTiles[0].getSprite().setScale(sf::Vector2f(2, 2));
  }
  this->length = this->snakeTiles.size();
}

void Snake::move(int direction) {
  switch (direction) {
    case -1:
      break;
    case 0:
      if (this->snakeTiles[0].getDirection() != 2) {
        this->snakeTiles[0].setDirection(direction);
      }
      break;
    case 1:
      if (this->snakeTiles[0].getDirection() != 3) {
        this->snakeTiles[0].setDirection(direction);
      }
      break;
    case 2:
      if (this->snakeTiles[0].getDirection() != 0) {
        this->snakeTiles[0].setDirection(direction);
      }
      break;
    case 3:
      if (this->snakeTiles[0].getDirection() != 1) {
        this->snakeTiles[0].setDirection(direction);
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

void Snake::draw(sf::RenderWindow &window) {
  for (int i = 0; i < this->snakeTiles.size(); i++) {
    window.draw(this->snakeTiles[i].getSprite());
  }
}

void Snake::eat(sf::Texture &texture, int &eating) {
  sf::Vector2f newPos = this->snakeTiles.back().getSprite().getPosition();
  switch (this->snakeTiles.back().getDirection()) {
    case 0:
      newPos.y += 32;
      break;
    case 1:
      newPos.x += 32;
      break;
    case 2:
      newPos.y += -32;
      break;
    case 3:
      newPos.x += -32;
      break;
  }
  this->snakeTiles.push_back(SnakeTile(newPos, this->snakeTiles.back().getDirection(), texture));
  this->length++;
  eating--;
  this->snakeTiles.back().getSprite().setScale(sf::Vector2f(2, 2));
}

sf::Vector2f Snake::getPosition(int position) {
  return this->snakeTiles[position].getSprite().getPosition();
}

int Snake::getLength() {
  return this->length;
}

Food::Food(sf::Texture &texture, Snake &player) {
  this->sprite.setTexture(texture);
  this->sprite.setScale(sf::Vector2f(2, 2));
  this->changePosition(player);
}

sf::Vector2f Food::getPosition() {
  return this->sprite.getPosition();
}

void Food::changePosition(Snake &player) {
  srand(time(0));
  int x = rand() % 20;
  int y = rand() % 20;
  sf::Vector2f newPos = {float(x * 32), float(y * 32)};
  for (int i = 0; i < player.getLength(); i++) {
    while (newPos == player.getPosition(i)) {
      x = rand() % 20;
      y = rand() % 20;
      newPos = {float(x * 32), float(y * 32)};
      i = 0;
    }
  }
  this->sprite.setPosition(newPos);
}

sf::Sprite &Food::getSprite() {
  return this->sprite;
}