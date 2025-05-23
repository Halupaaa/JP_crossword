#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"


using namespace sf;

class Menu
{
private:
    int currentFrame = 0;
    Clock animationClock;
    float frameDelay = 0.1f;

    Sprite backgroundSprite;

    Text titleText;
    Text mainText;
    Button firstBtn, secondBtn, thirdBtn, gameStyleBtn;

public:
    Menu();

    void updateAnimation();
    void GameStyleButton();
    void startMenu();
    void infoMenu();
    void categoryMenu();
    void navMenu();
    void winNavMenu();

    int handleClick(Vector2i& mousePos);

    void draw(GameState& state);
};
