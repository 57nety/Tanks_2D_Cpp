#pragma once
#include "Enemy.h"
#include <sstream>

class Map
{
	class Timer
	{
	private:
		bool activity; // ���������� ������� � ������ ������ �������
		int initValue; // ��������� ��������
		int presentValue; // ������� ��������
		Clock clock; // ����
	public:
		Timer(); // ����������� ��� ����������
		Timer(int value); // ����������� � ����� ����������
		Timer& operator=(const Timer& timer); // ���������� ��������� ������������
		void startTimer(void); // ������ �������
		void stopTimer(void); // ��������� �������
		int getPresentValue(void); // �������� ������� �������� �������
		void setInitValue(int value); // ������ ��������� �������� �������
		bool getActivity(void); // ������� �� � ������ ������ ������
	};
private:
	Timer timerGame; // ������ ���� ����
	Timer timerBonus; // ������ ������
	String fileMap; // �������� ����� � ������
	Image image; // ��������
	Texture texture; // ��������
	Sprite sprite; // ������
	static const int height = 10; // ������ �����
	static const int width = 14; // ������ �����
	String tileMap[height] = { // �����
		"wwwwwwwwwwwwww", // w - wall (�����)
		"w            w", // d - double damage (������� ����)
		"w            w", // s - shield (���)
		"w            w", // t - upTime (��������� ������� �� 20 ������)
		"w            w",
		"w            w",
		"w            w",
		"w            w",
		"w            w",
		"wwwwwwwwwwwwww",
	};
	bool bonusDoubleDamage; // ��������� ������������, ������� �� � ������ ������ ����� "������� ����"
	bool bonusShield; // ��������� ������������, ������� �� � ������ ������ ����� "���"
	bool bonusUpTime; // ��������� ������������, ������� �� � ������ ������ ����� "��������� ������� �� 20 ������"
public:
	Map(String fileMap); // ����������� ��� ������ Map
	void draw(RenderWindow& window); // ���������� �����
	void drawTimer(RenderWindow& window); // ���������� ������ �� �����
	friend void Hero::interactionHeroWithMap(Map& map); // �������������� ����� � ������
	friend void Hero::checkActivityBonus(Map& map); // �������� ���������� ������ � ������ ������ �������
	friend void Enemy::interactionEnemyWithMap(Map& map); // �������������� ���� � ������
	friend void Bullet::interactionBulletWithMap(Map& map); // �������������� ���� � ������
	int getHeight(void); // �������� ������ �����
	int getWidth(void); // �������� ������ �����
	void randomMapGenerate(void); // ��������� ������������ ������� �� �����
	void printAmountOfHealthHero(int amountOfHealth, RenderWindow& window); // ������ ���������� ������ � �����
	void printAmountOfHealthEnemy(int amountOfHealth, RenderWindow& window); // ������ ���������� ������ � �����
	int getPresentValueTimer(void); // �������� ������� �������� �������
};