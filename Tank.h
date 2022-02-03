#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Map;

class Tank
{
protected:
	Bullet bullet; // ����
	bool isShoot; // ��������� �� ���
	Clock clock; // ����
	int height, width; // ������ � ������ ��������
	String fileTank; // ��� ����� � ���������� �����
	Image image; // ��������
	Texture texture; // ��������
	Sprite sprite; // ������
	float x, y; // ������� ���������� �����;
	float dx, dy; // dx - ��������� �� x, dy - ��������� �� y
	float speed; // �������� �������� �����
	int direction; // ����������� �������� ����� (�����, ����, �����, ������)
	int damage; // ����, ������� ����� ������� ����
	int protection; // ������, ������� �������� ����
	int amountOfHealth; // ���������� ��������
	bool live; // �����
public:
	Tank(String fileTank, int height, int width, int x, int y); // �����������
	void interactionOfClassmates(Tank& tank); // �������������� �������� ������ ������
	Sprite& getSprite(void); // �������� ������
	float getX(void); // �������� X
	float getY(void); // �������� Y
	FloatRect getRect(void); // �������� ������������� �������
	void shoot(void); // ��������
	void setIsShoot(bool value); // �������� �������� ���� ��������
	friend void Bullet::interactionBulletWithTank(Tank& tank); // �������������� ����� � �����
	int getAmountOfHealth(void); // �������� ���������� �������� � �����
};