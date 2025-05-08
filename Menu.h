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
    void initialize();
    void draw();
};
