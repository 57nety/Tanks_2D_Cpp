#pragma once
#include "Tank.h"

class Hero :
    public Tank // наследование от класса Tank
{
private:
    int spriteColumnCoordinate; // координата столбца спрайта
public:
    Hero(String fileTank, int height, int width, int x, int y); // конструктор
    void directionOfTravel(void); // направление движения
    void update(Map& map, Enemy& enemy, RenderWindow& window); // обновление состояния танка
    void interactionHeroWithMap(Map& map); // взаимодействие танка с картой
    void checkActivityBonus(Map& map); // проверка активности бонуса в данный момент времени
    void setSpritePosition(void); // изменить позицию спрайта в зависимости от направления
};

