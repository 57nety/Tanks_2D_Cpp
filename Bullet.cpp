#include "Bullet.h"
#include "Map.h"

// конструктор без параметров класса Bullet
Bullet::Bullet() {
	this->height = 0;
	this->width = 0;
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->speed = 0;
	this->direction = 0;
	this->damage = 0;
	this->live = false;
	this->fileBullet = "";
}

// конструктор с параметрами класса Bullet
Bullet::Bullet(String fileBullet, int height, int width, int x, int y, int direction, int damage) {
	this->height = height;
	this->width = width;
	this->x = x;
	this->y = y;
	this->dx = 0;
	this->dy = 0;
	this->speed = 0.3;
	this->direction = direction;
	this->damage = damage;
	this->live = true;
	this->fileBullet = fileBullet;
	this->image.loadFromFile("images/" + this->fileBullet);
	this->image.createMaskFromColor(Color(255, 255, 255));
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(IntRect(0, 0, this->width, this->height));
	this->sprite.setColor(Color::Black);
}

// перегрузка оператора присваивания для класса Bullet
Bullet& Bullet::operator=(const Bullet& bullet) {
	this->height = bullet.height;
	this->width = bullet.width;
	this->fileBullet = bullet.fileBullet;
	this->image = bullet.image;
	this->texture = bullet.texture;
	this->sprite = bullet.sprite;
	this->x = bullet.x;
	this->y = bullet.y;
	this->dx = bullet.dx;
	this->dy = bullet.dy;
	this->speed = bullet.speed;
	this->direction = bullet.direction;
	this->damage = bullet.damage;
	this->live = bullet.live;
	return *this;
}

// взаимодействие пули с картой
void Bullet::interactionBulletWithMap(Map& map) {
	for (int i = this->y / 60; i < (this->y + this->height) / 60; i++) {
		for (int j = this->x / 60; j < (this->x + this->width) / 60; j++) {
			// столкновение со стенкой
			if (map.tileMap[i][j] == 'w') {
				this->live = false;
			}
		}
	}
}

// обновление состояноия пули
void Bullet::update(float time, Map& map, RenderWindow& window, Tank& tank_1, Tank& tank_2) {
	if (this->live == true) {
		window.draw(this->sprite);
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

		this->x = this->x + this->dx * time;
		this->y = this->y + this->dy * time;

		sprite.setPosition(this->x + 15, this->y + 15);

		(*this).interactionBulletWithMap(map);
		(*this).interactionBulletWithTank(tank_2);
	}
	else {
		tank_1.setIsShoot(false);
	}
}

// взаимодействие пули с танком
void Bullet::interactionBulletWithTank(Tank& tank) {
	if ((*this).getRect().intersects(tank.getRect())) {
		this->live = false;
		tank.amountOfHealth = tank.amountOfHealth - this->damage + tank.protection;
		if (tank.amountOfHealth <= 0) {
			tank.live = false;
		}
	}
}

// получить прямоугольник пули
FloatRect Bullet::getRect(void) {
	return FloatRect(this->x, this->y, this->width, this->height);
}

// изменить направление
void Bullet::setDirection(int direction) {
	this->direction = direction;
}

// изменить X
void Bullet::setX(float x) {
	this->x = x;
}

// изменить Y
void Bullet::setY(float y) {
	this->y = y;
}

// изменить значение поля жизнь
void Bullet::setLive(bool value) {
	this->live = value;
}

// получить состояние жизни пули
bool Bullet::getLive(void) {
	return this->live;
}