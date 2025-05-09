#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"


using namespace sf;

class Menu
{
private:
    
    Sprite backgroundSprite;

    Text titleText;
    Text mainText;
    Button firstBtn, secondBtn, thirdBtn;

public:
    Menu();

    void startMenu();
    void infoMenu();
    void categoryMenu();
    void navMenu();
    void winNavMenu();

    int handleClick(Vector2i mousePos);

    void draw(GameState state);
};
