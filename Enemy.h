#pragma once
#include "Hero.h"

class Enemy :
    public Tank // наследование от класса Tank
{
public:
    Enemy(String fileTank, int height, int width, int x, int y); // конструктор
    void directionOfTravel(Hero& hero); // направление движения
    void update(Map& map, Hero& hero, RenderWindow& window); // обновление состояния танка
    void interactionEnemyWithMap(Map& map); // взаимодействие танка с картой
    void movementToTheUp(void); // движение вверх
    void movementToTheDown(void); // движение вниз
    void movementToTheLeft(void); // движение влево
    void movementToTheRight(void); // движение вправо
};