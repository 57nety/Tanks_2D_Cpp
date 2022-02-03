#pragma once
#include "Hero.h"

class Enemy :
    public Tank // ������������ �� ������ Tank
{
public:
    Enemy(String fileTank, int height, int width, int x, int y); // �����������
    void directionOfTravel(Hero& hero); // ����������� ��������
    void update(Map& map, Hero& hero, RenderWindow& window); // ���������� ��������� �����
    void interactionEnemyWithMap(Map& map); // �������������� ����� � ������
    void movementToTheUp(void); // �������� �����
    void movementToTheDown(void); // �������� ����
    void movementToTheLeft(void); // �������� �����
    void movementToTheRight(void); // �������� ������
};