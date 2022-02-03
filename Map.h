#pragma once
#include "Enemy.h"
#include <sstream>

class Map
{
	class Timer
	{
	private:
		bool activity; // активность таймера в данный момент времени
		int initValue; // начальное значение
		int presentValue; // текущее значение
		Clock clock; // часы
	public:
		Timer(); // конструктор без параметров
		Timer(int value); // конструктор с одним параметром
		Timer& operator=(const Timer& timer); // перегрузка оператора присваивания
		void startTimer(void); // запуск таймера
		void stopTimer(void); // остановка таймера
		int getPresentValue(void); // получить текущее значение таймера
		void setInitValue(int value); // задать начальное значение таймера
		bool getActivity(void); // активен ли в данный момент таймер
	};
private:
	Timer timerGame; // таймер всей игры
	Timer timerBonus; // таймер бонуса
	String fileMap; // название файла с картой
	Image image; // картинка
	Texture texture; // текстура
	Sprite sprite; // спрайт
	static const int height = 10; // высота карты
	static const int width = 14; // ширина краты
	String tileMap[height] = { // карта
		"wwwwwwwwwwwwww", // w - wall (стена)
		"w            w", // d - double damage (двойной урон)
		"w            w", // s - shield (щит)
		"w            w", // t - upTime (остановка таймера на 20 секунд)
		"w            w",
		"w            w",
		"w            w",
		"w            w",
		"w            w",
		"wwwwwwwwwwwwww",
	};
	bool bonusDoubleDamage; // переменая показывающая, активен ли в данный момент бонус "двойной урон"
	bool bonusShield; // переменая показывающая, активен ли в данный момент бонус "щит"
	bool bonusUpTime; // переменая показывающая, активен ли в данный момент бонус "остановка таймера на 20 секунд"
public:
	Map(String fileMap); // конструктор для класса Map
	void draw(RenderWindow& window); // нарисовать карту
	void drawTimer(RenderWindow& window); // отобразить таймер на карте
	friend void Hero::interactionHeroWithMap(Map& map); // взаимодействие танка с картой
	friend void Hero::checkActivityBonus(Map& map); // проверка активности бонуса в данный момент времени
	friend void Enemy::interactionEnemyWithMap(Map& map); // взаимодейтсвие пули с картой
	friend void Bullet::interactionBulletWithMap(Map& map); // взаимодействие пули с картой
	int getHeight(void); // получить высоту карты
	int getWidth(void); // получить ширину карты
	void randomMapGenerate(void); // рандомное расположение бонусов на карте
	void printAmountOfHealthHero(int amountOfHealth, RenderWindow& window); // печать количества жизней у героя
	void printAmountOfHealthEnemy(int amountOfHealth, RenderWindow& window); // печать количества жизней у врага
	int getPresentValueTimer(void); // получить текущее значение таймера
};