#include "Tank.h"

// �����������
Tank::Tank(String fileTank, int height, int width, int x, int y) {
	this->height = height;
	this->width = width;
	this->x = x;
	this->y = y;
	this->dx = 0;
	this->dy = 0;
	this->speed = 0;
	this->direction = 1;
	this->damage = 27;
	this->protection = 5;
	this->amountOfHealth = 100;
	this->live = true;
	this->fileTank = fileTank;
	this->image.loadFromFile("images/" + this->fileTank);
	this->image.createMaskFromColor(Color(255, 255, 255));
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(IntRect(0, 0, this->width, this->height));
	Bullet bullet("bullet.png", 10, 10, this->x, this->y, this->direction, this->damage);
	this->bullet = bullet;
	this->isShoot = false;
}

// �������� ������������� �������
FloatRect Tank::getRect(void) {
	return FloatRect(this->x, this->y, this->width + 20, this->height + 20);
}

// �������������� ��������������
void Tank::interactionOfClassmates(Tank& tank) {
	if ((*this).getRect().intersects(tank.getRect())) {
		if (this->dx > 0) {
			this->x -= 1;
		}
		else if (this->dx < 0) {
			this->x += 1;
		}
		else if (this->dy > 0) {
			this->y -= 1;
		}
		else if (this->dy < 0) {
			this->y += 1;
		}
	}
}

// �������� ������
Sprite& Tank::getSprite(void) {
	return this->sprite;
}

// �������� X
float Tank::getX(void) {
	return this->x;
}

// �������� Y
float Tank::getY(void) {
	return this->y;
}

// �������� �������� ���� ��������
void Tank::setIsShoot(bool value) {
	this->isShoot = value;
}

// ��������
void Tank::shoot(void) {
	this->isShoot = true;
	this->bullet.setLive(true);
	this->bullet.setDirection(this->direction);
	this->bullet.setX(this->x);
	this->bullet.setY(this->y);
}

// �������� ���������� �������� � �����
int Tank::getAmountOfHealth(void) {
	return this->amountOfHealth;
}