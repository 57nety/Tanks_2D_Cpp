#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Map;

class Tank
{
protected:
	Bullet bullet; // пуля
	bool isShoot; // стрельнул ли уже
	Clock clock; // часы
	int height, width; // высота и ширина картинки
	String fileTank; // имя файла с картинками танка
	Image image; // картинка
	Texture texture; // текстура
	Sprite sprite; // спрайт
	float x, y; // текущие координаты танка;
	float dx, dy; // dx - ускорение по x, dy - ускорение по y
	float speed; // скорость движения танка
	int direction; // направление движения танка (вверх, вниз, влево, вправо)
	int damage; // урон, который может нанести танк
	int protection; // защита, которой обладает танк
	int amountOfHealth; // количество здоровья
	bool live; // жизнь
public:
	Tank(String fileTank, int height, int width, int x, int y); // конструктор
	void interactionOfClassmates(Tank& tank); // взаимодействие объектов одного класса
	Sprite& getSprite(void); // получить спрайт
	float getX(void); // получить X
	float getY(void); // получить Y
	FloatRect getRect(void); // получить прямоугольник объекта
	void shoot(void); // стрелять
	void setIsShoot(bool value); // изменить значение поля стрелять
	friend void Bullet::interactionBulletWithTank(Tank& tank); // взаимодействие танка с пулей
	int getAmountOfHealth(void); // получить количество здоровья у танка
};