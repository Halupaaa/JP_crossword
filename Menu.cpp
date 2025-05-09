#include "Menu.h"
#include "Design.h"
#include "Game.h"

Menu::Menu()
{
    backgroundTexture.loadFromFile("pics/waves1.jpeg");
    backgroundTexture.setSmooth(true);

    font.loadFromFile("fonts/Masa_Groovy.ttf");
}

void Menu::startMenu()
{
    titleText.setString("");

    mainText.setFont(font);
    mainText.setString("jp crosswords");
    mainText.setCharacterSize(140);
    mainText.setFillColor(Design::MenuTextColor);


    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 200);

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

    firstBtn = Button( "play", Design::Window->getSize().y / 2.f - 100, font, buttonSize);
    secondBtn = Button( "about", Design::Window->getSize().y / 2.f, font, buttonSize);
    thirdBtn = Button("exit", Design::Window->getSize().y / 2.f + 100, font, buttonSize);
}

void Menu::infoMenu()
{
	titleText.setFont(font);
	titleText.setString("How to Play Japanese Crosswords?");
	titleText.setCharacterSize(70);
	titleText.setFillColor(Design::MenuTextColor);
	FloatRect titleTextBounds = titleText.getLocalBounds();
	titleText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    titleText.setPosition(Design::Window->getSize().x / 2.f, 200);
    Design::Window->draw(titleText);

    mainText.setFont(font);
    mainText.setString("\nYour goal is to reveal a hidden picture by filling in \nthe correct squares - using logic, not luck.Numbers\n on the top and left show how many filled blocks\n are in each column or row.\nMultiple numbers mean separate groups, with at \nleast one empty square between them.Left click to \nfill a square.Right click to cross out a square.\nStart with rows or columns that have big or obvious \nclues.Look for overlaps - where filled blocks must go \nno matter what.\nTake your time.Stay sharp.And remember - it's not just \nabout solving it, it's about solving it right.Ready? Let's go!");
    mainText.setCharacterSize(35);
    mainText.setFillColor(Design::MenuTextColor);


    FloatRect mainBounds = mainText.getLocalBounds();
    mainText.setOrigin(mainBounds.width / 2.f, mainBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, Design::Window->getSize().y / 2.f);

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

    firstBtn = Button("back", Design::Window->getSize().y / 2.f + 300, font, buttonSize);
	secondBtn = Button("", -500, font, buttonSize);
	thirdBtn = Button("", -500, font, buttonSize);
}

void Menu::categoryMenu()
{
    titleText.setString("");

    mainText.setFont(font);
    mainText.setString("A random game will be picked \nfrom the category you chose");
    mainText.setCharacterSize(65);
    mainText.setFillColor(Design::MenuTextColor);

    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin((titleTextBounds.width / 2.f) - 20.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 250);

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

    firstBtn = Button("5 x 5", Design::Window->getSize().y / 2.f - 100, font, buttonSize);
    secondBtn = Button("10 x 10", Design::Window->getSize().y / 2.f, font, buttonSize);
    thirdBtn = Button("15 x 15", Design::Window->getSize().y / 2.f + 100, font, buttonSize);
}

void Menu::navMenu()
{
    titleText.setString("");

    mainText.setString("");

    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 200);

    Vector2f buttonSize(400.f, 80.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);
    Font& f = font;

    firstBtn = Button("continue", Design::Window->getSize().y / 2.f - 100, font, buttonSize);
    secondBtn = Button("new game", Design::Window->getSize().y / 2.f, font, buttonSize);
    thirdBtn = Button("start menu", Design::Window->getSize().y / 2.f + 100, font, buttonSize);
}
void Menu::winNavMenu()
{
    titleText.setString("");

    mainText.setFont(font);
    mainText.setString("NICEEEE ;))");
    mainText.setCharacterSize(140);
    mainText.setFillColor(Design::MenuTextColor);


    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 200);

    Vector2f buttonSize(400.f, 80.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);
    Font& f = font;

    firstBtn = Button("new game", Design::Window->getSize().y / 2.f - 100, font, buttonSize);
    secondBtn = Button("start menu", Design::Window->getSize().y / 2.f, font, buttonSize);
    thirdBtn = Button("exit", Design::Window->getSize().y / 2.f + 100, font, buttonSize);
}

int Menu::handleClick(Vector2i mousePos)
{
    if (firstBtn.isClicked(mousePos)) return 1;
    else if (secondBtn.isClicked(mousePos)) return 2;
    else if (thirdBtn.isClicked(mousePos)) return 3;
    else return 0;
}

void Menu::draw(GameState state)
{
    switch (state)
    {
	    case GameState::StartMenu: startMenu(); break;
		case GameState::InfoMenu: infoMenu(); break;
		case GameState::CategoryMenu: categoryMenu(); break;
		case GameState::NavigationMenu: navMenu(); break;
		case GameState::WinningNavigationMenu: winNavMenu(); break;
    }

    Design::Window->draw(backgroundSprite);
    Design::Window->draw(titleText);
	Design::Window->draw(mainText);
    firstBtn.draw();
    secondBtn.draw();
    thirdBtn.draw();
}