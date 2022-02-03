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
	int height, width; // ������ � ������ ��������
	String fileBullet; // ��� ����� � ���������� �����
	Image image; // ��������
	Texture texture; // ��������
	Sprite sprite; // ������
	float x, y; // ������� ���������� �����;
	float dx, dy; // dx - ��������� �� x, dy - ��������� �� y
	float speed; // �������� �������� �����
	int direction; // ����������� �������� ����� (�����, ����, �����, ������)
	int damage; // ����, ������� ����� ������� ����
	bool live; // �����
public:
	Bullet();// ����������� ��� ���������� ������ Bullet
	Bullet(String fileTank, int height, int width, int x, int y, int direction, int damage); // ����������� � ����������� ������ Bullet
	FloatRect getRect(void); // �������� ������������� ����
	void interactionBulletWithMap(Map& map); // �������������� ���� � ������
	void update(float time, Map& map, RenderWindow& window, Tank& tank_1, Tank& tank_2); // ���������� ��������� ����
	Bullet& operator=(const Bullet& bullet); // ���������� ��������� ������������ ��� ������ Bullet
	void setDirection(int direction); // �������� �����������
	void setX(float x); // �������� X
	void setY(float y); // �������� Y
	void setLive(bool value); // �������� �������� ���� �����
	bool getLive(void); // �������� ��������� ����� ����
	void interactionBulletWithTank(Tank& tank); // �������������� ���� � ������
};