#pragma once
#include "Tank.h"

class Hero :
    public Tank // ������������ �� ������ Tank
{
private:
    int spriteColumnCoordinate; // ���������� ������� �������
public:
    Hero(String fileTank, int height, int width, int x, int y); // �����������
    void directionOfTravel(void); // ����������� ��������
    void update(Map& map, Enemy& enemy, RenderWindow& window); // ���������� ��������� �����
    void interactionHeroWithMap(Map& map); // �������������� ����� � ������
    void checkActivityBonus(Map& map); // �������� ���������� ������ � ������ ������ �������
    void setSpritePosition(void); // �������� ������� ������� � ����������� �� �����������
};

