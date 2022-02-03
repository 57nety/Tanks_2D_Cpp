#include "Map.h"

// �����������
Enemy::Enemy(String fileTank, int height, int width, int x, int y) :Tank(fileTank, height, width, x, y) {

}

// ����������� ��������
void Enemy::directionOfTravel(Hero& hero) {
	if ((int)(hero.getX() - this->x) != 0) {
		// �������� �����
		if ((hero.getX() - this->x) < 0) {
			(*this).movementToTheLeft();
		}
		// �������� ������
		else if ((hero.getX() - this->x) > 0) {
			(*this).movementToTheRight();
		}
	}
	else {
		if ((int)(hero.getY() - this->y) != 0) {
			// �������� �����
			if ((hero.getY() - this->y) < 0) {
				(*this).movementToTheUp();
			}
			// �������� ����
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
			// ������������ �� �������
			if (map.tileMap[i][j] == 'w') {
				// �������� ����
				if (this->dy > 0) {
					this->y = i * 60 - this->height;
				}
				// �������� �����
				else if (this->dy < 0) {
					this->y = i * 60 + 60;
				}
				// �������� ������
				else if (this->dx > 0) {
					this->x = j * 60 - this->width;
				}
				// �������� �����
				else if (this->dx < 0) {
					this->x = j * 60 + 60;
				}
			}
		}
	}
}

// ���������� ��������� �����
void Enemy::update(Map& map, Hero& hero, RenderWindow& window) {
	if (this->live == true) {
		window.draw(this->sprite);
		(*this).directionOfTravel(hero);

		switch (this->direction)
		{
		case 1: // �������� �����
			this->dx = 0;
			this->dy = -this->speed;
			break;
		case 2: // �������� ����
			this->dx = 0;
			this->dy = this->speed;
			break;
		case 3: // �������� �����
			this->dx = -this->speed;
			this->dy = 0;
			break;
		case 4: // �������� ������
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

// �������� �����
void Enemy::movementToTheUp(void) {
	this->direction = 1;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(0, 0, 40, 40));
}

// �������� ����
void Enemy::movementToTheDown(void) {
	this->direction = 2;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(0, 40, 40, 40));
}

// �������� �����
void Enemy::movementToTheLeft(void) {
	this->direction = 3;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(40, 80, -40, 40));
}

// �������� ������
void Enemy::movementToTheRight(void) {
	this->direction = 4;
	this->speed = 0.03;
	this->sprite.setTextureRect(IntRect(0, 80, 40, 40));
}