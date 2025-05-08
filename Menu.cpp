#include "Menu.h"

#include <iostream>
#include <stdexcept>

#include "Design.h"

Menu::Menu() {
    backgroundTexture.loadFromFile("pics/waves1.jpeg");
    backgroundTexture.setSmooth(true);

    font.loadFromFile("fonts/Masa_Groovy.ttf");
}

void Menu::startMenu()
{
    titleText.setFont(font);
    titleText.setString("jp crosswords");
    titleText.setCharacterSize(140);
    titleText.setFillColor(Design::MenuTextColor);


    FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titleText.setPosition(Design::Window->getSize().x / 2.f, 200);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        Design::Window->getSize().x / (float)backgroundTexture.getSize().x,
        Design::Window->getSize().y / (float)backgroundTexture.getSize().y
    );

    Vector2f buttonSize(400.f, 80.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);
    Font& f = font;

    playBtn = Button( "play", Design::Window->getSize().y / 2.f - 100, font, buttonSize);
    aboutBtn = Button( "about", Design::Window->getSize().y / 2.f, font, buttonSize);
    exitBtn = Button("exit", Design::Window->getSize().y / 2.f + 100, font, buttonSize);
}

void Menu::navMenu()
{
    titleText.setString("");

    Vector2f buttonSize(400.f, 80.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);
    Font& f = font;

    playBtn = Button("play", Design::Window->getSize().y / 2.f - 100, font, buttonSize);
    aboutBtn = Button("about", Design::Window->getSize().y / 2.f, font, buttonSize);
    exitBtn = Button("exit", Design::Window->getSize().y / 2.f + 100, font, buttonSize);
}

int Menu::handleClick(Vector2i mousePos)
{
    if (playBtn.isClicked(mousePos)) return 1;
    else if (aboutBtn.isClicked(mousePos)) return 2;
    else if (exitBtn.isClicked(mousePos)) return 3;
    else return 0;
}

void Menu::draw(char menu_or_grid)
{
	if (menu_or_grid == 's') startMenu();
	else if (menu_or_grid == 'n') navMenu();

    Design::Window->draw(backgroundSprite);
	Design::Window->draw(titleText);
    playBtn.draw();
    aboutBtn.draw();
    exitBtn.draw();
}