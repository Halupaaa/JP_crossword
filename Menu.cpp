#include "Menu.h"

#include <iostream>
#include <stdexcept>

#include "Design.h"

Menu::Menu() {
    backgroundTexture.loadFromFile("pics/waves1.jpeg");
    backgroundTexture.setSmooth(true);

    font.loadFromFile("fonts/Masa_Groovy.ttf");
}

void Menu::initialize()
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

void Menu::draw()
{
    initialize();

    Design::Window->draw(backgroundSprite);
	Design::Window->draw(titleText);
    playBtn.draw();
    aboutBtn.draw();
    exitBtn.draw();

}