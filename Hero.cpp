#include "Map.h"

// конструктор
Hero::Hero(String fileTank, int height, int width, int x, int y) :Tank(fileTank, height, width, x, y) {
	this->spriteColumnCoordinate = 0;
}

// направление движения
void Hero::directionOfTravel(void) {
	// движение вверх
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
		this->direction = 1;
		this->speed = 0.1;
	}
	// движение вниз
	else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
		this->direction = 2;
		this->speed = 0.1;
	}
	// движение влево
	else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
		this->direction = 3;
		this->speed = 0.1;
	}
	// движение вправо
	else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
		this->direction = 4;
		this->speed = 0.1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (this->isShoot == false) {
			(*this).shoot();
		}
	}
	(*this).setSpritePosition();
}

// изменить позицию спрайта в зависимости от направления
void Hero::setSpritePosition(void) {
	if (this->direction == 1) {
		this->sprite.setTextureRect(IntRect(this->spriteColumnCoordinate, 0, 40, 40));
	}
	else if (this->direction == 2) {
		this->sprite.setTextureRect(IntRect(this->spriteColumnCoordinate, 40, 40, 40));
	}
	else if (this->direction == 3) {
		this->sprite.setTextureRect(IntRect(this->spriteColumnCoordinate + 40, 80, -40, 40));
	}
	else if (this->direction == 4) {
		this->sprite.setTextureRect(IntRect(this->spriteColumnCoordinate, 80, 40, 40));
	}
}

// взаимодействие танка с картой
void Hero::interactionHeroWithMap(Map& map) {
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
			// проверка того, что в данный момент все бонусы не активны
			if (map.bonusDoubleDamage == false && map.bonusShield == false && map.bonusUpTime == false) {
				// столкновение с бонусом "щит"
				if (map.tileMap[i][j] == 's') {
					map.tileMap[i][j] = ' ';
					this->spriteColumnCoordinate = 40;
					this->protection = this->protection * 2;
					map.bonusShield = true;
					map.timerBonus.setInitValue(20);
				}
				// столкновение с бонусом "двойной урон"
				else if (map.tileMap[i][j] == 'd') {
					map.tileMap[i][j] = ' ';
					this->spriteColumnCoordinate = 80;
					this->damage = this->damage * 2;
					map.bonusDoubleDamage = true;
					map.timerBonus.setInitValue(20);
				}
				// столкновение с бонусом "остановка таймера на 20 секунд"
				else if (map.tileMap[i][j] == 't') {
					map.tileMap[i][j] = ' ';
					map.bonusUpTime = true;
					map.timerBonus.setInitValue(20);
				}
			}
		}
	}
	(*this).checkActivityBonus(map);
}

// проверка активности бонуса в данный момент времени
void Hero::checkActivityBonus(Map& map) {
	if (map.bonusShield == true) {
		map.timerBonus.startTimer();
		if (map.timerBonus.getActivity() != true) {
			this->spriteColumnCoordinate = 0;
			this->protection = this->protection / 2;
			map.bonusShield = false;
		}
	}
	else if (map.bonusDoubleDamage == true) {
		map.timerBonus.startTimer();
		if (map.timerBonus.getActivity() != true) {
			this->spriteColumnCoordinate = 0;
			this->damage = this->damage / 2;
			map.bonusDoubleDamage = false;
		}
	}
	else if (map.bonusUpTime == true) {
		map.timerGame.stopTimer();
		map.timerBonus.startTimer();
		if (map.timerBonus.getActivity() != true) {
			map.timerGame.startTimer();
			map.bonusUpTime = false;
		}
	}
}

// обновление состояния танка
void Hero::update(Map& map, Enemy& enemy, RenderWindow& window) {
	if (this->live == true) {
		window.draw(this->sprite);

		(*this).directionOfTravel();

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

		this->speed = 0;

		float time = this->clock.getElapsedTime().asMicroseconds();
		this->clock.restart();
		time = time / 800;

		this->x = this->x + this->dx * time;
		this->y = this->y + this->dy * time;

		this->sprite.setPosition(x, y);

		(*this).interactionHeroWithMap(map);
		map.printAmountOfHealthHero(this->amountOfHealth, window);
		(*this).interactionOfClassmates(enemy);

		if (this->isShoot == true) {
			this->bullet.update(time, map, window, (*this), enemy);
		}
	}
}