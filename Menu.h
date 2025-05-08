#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"


using namespace sf;

class Menu
{
private:
    Font font;
    Texture backgroundTexture;
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

    int handleClick(Vector2i mousePos);

    void draw(GameState state);
};
