#include "Map.h"

// конструктор
Enemy::Enemy(String fileTank, int height, int width, int x, int y) :Tank(fileTank, height, width, x, y) {

}

// направление движения
void Enemy::directionOfTravel(Hero& hero) {
	if ((int)(hero.getX() - this->x) != 0) {
		// движение влево
		if ((hero.getX() - this->x) < 0) {
			(*this).movementToTheLeft();
		}
		// движение вправо
		else if ((hero.getX() - this->x) > 0) {
			(*this).movementToTheRight();
		}
	}
	else {
		if ((int)(hero.getY() - this->y) != 0) {
			// движение вверх
			if ((hero.getY() - this->y) < 0) {
				(*this).movementToTheUp();
			}
			// движение вниз
			else if ((hero.getY() - this->y) > 0) {
				(*this).movementToTheDown();
			}
		}
		else {
			this->speed = 0;
		}
	}
}

void Enemy::interactionEnemyWithMap(Map& map) {
	for (int i = this->y / 60; i < (this->y + this->height) / 60; i++) {
		for (int j = this->x / 60; j < (this->x + this->width) / 60; j++) {
			// столкновение со стенкой
			if (map.tileMap[i][j] == 'w') {
				// движение вниз
				if (this->dy > 0) {
					this->y = i * 60 - this->height;
				}
				// движение вверх
				else if (this->dy < 0) {
					this->y = i * 60 + 60;
				}
				// движение вправо
				else if (this->dx > 0) {
					this->x = j * 60 - this->width;
				}
				// движение влево
				else if (this->dx < 0) {
					this->x = j * 60 + 60;
				}
			}
		}
	}
}

// обновление состояния танка
void Enemy::update(Map& map, Hero& hero, RenderWindow& window) {
	if (this->live == true) {
		window.draw(this->sprite);
		(*this).directionOfTravel(hero);

		switch (this->direction)
		{
		case 1: // движение вверх
			this->dx = 0;
			this->dy = -this->speed;
			break;
		case 2: // движение вниз
			this->dx = 0;
			this->dy = this->speed;
			break;
		case 3: // движение влево
			this->dx = -this->speed;
			this->dy = 0;
			break;
		case 4: // движение вправо
			this->dx = this->speed;
			this->dy = 0;
			break;
		}

		float time = this->clock.getElapsedTime().asMicroseconds();
		this->clock.restart();
		time = time / 800;

		this->x = this->x + this->dx * time;
		this->y = this->y + this->dy * time;

		this->sprite.setPosition(x, y);

		(*this).interactionOfClassmates(hero);
		map.printAmountOfHealthEnemy(this->amountOfHealth, window);
		(*this).interactionEnemyWithMap(map);

		if (this->isShoot == false) {
			(*this).shoot();
		}
		if(this->isShoot == true){
			this->bullet.update(time, map, window, (*this), hero);
		}
	}
}

// движение вверх
void Enemy::movementToTheUp(void) {
	this->direction = 1;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(0, 0, 40, 40));
}

// движение вниз
void Enemy::movementToTheDown(void) {
	this->direction = 2;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(0, 40, 40, 40));
}

// движение влево
void Enemy::movementToTheLeft(void) {
	this->direction = 3;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(40, 80, -40, 40));
}

// движение вправо
void Enemy::movementToTheRight(void) {
	this->direction = 4;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(0, 80, 40, 40));
}