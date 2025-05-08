#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class Menu
{
private:
    Font font;
    Texture backgroundTexture;
    Sprite backgroundSprite;


    Text titleText;
    Button playBtn, aboutBtn, exitBtn;

public:
    Menu();

    void startMenu();
    void navMenu();

    int handleClick(Vector2i mousePos);

    void draw(char menu_or_grid);
};
