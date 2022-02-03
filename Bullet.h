#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Tank;

class Hero;

class Enemy;

class Map;

class Bullet
{
private:
	int height, width; // высота и ширина картинки
	String fileBullet; // имя файла с картинками танка
	Image image; // картинка
	Texture texture; // текстура
	Sprite sprite; // спрайт
	float x, y; // текущие координаты танка;
	float dx, dy; // dx - ускорение по x, dy - ускорение по y
	float speed; // скорость движения танка
	int direction; // направление движения танка (вверх, вниз, влево, вправо)
	int damage; // урон, который может нанести танк
	bool live; // жизнь
public:
	Bullet();// конструктор без параметров класса Bullet
	Bullet(String fileTank, int height, int width, int x, int y, int direction, int damage); // конструктор с параметрами класса Bullet
	FloatRect getRect(void); // получить прямоугольник пули
	void interactionBulletWithMap(Map& map); // взаимодействие пули с картой
	void update(float time, Map& map, RenderWindow& window, Tank& tank_1, Tank& tank_2); // обновление состояния пули
	Bullet& operator=(const Bullet& bullet); // перегрузка оператора присваивания для класса Bullet
	void setDirection(int direction); // изменить направление
	void setX(float x); // изменить X
	void setY(float y); // изменить Y
	void setLive(bool value); // изменить значение поля жизнь
	bool getLive(void); // получить состояние жизни пули
	void interactionBulletWithTank(Tank& tank); // взаимодействие пули с танком
};